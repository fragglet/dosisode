#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

FILE *change_file;

main(int argc, char **argv)
{
  int i;
  read_convert(); /*pkay mod*/
  for (i=1; i < argc; i++)
    tarread(argv[i]);
  change_file = fopen("/tarchange.lst", "w");
  dump_changes();
  fclose(change_file);
}

/*------------------------------------------------------------------------*/

typedef struct CHANGE {
  struct CHANGE *next;
  char *old;
  char *new;
  int isdir; /* 0=file, 1=dir, 2=skip */
} CHANGE;

CHANGE *change_root = 0;

dump_changes()
{
  CHANGE *c;
  for (c=change_root; c; c=c->next)
    fprintf(change_file, "%s -> %s\n", c->old, c->new);
}

int change(char *fname, char *problem, int isadir)
{
  CHANGE *ch;
  char new[200];
  char *pos;

  for (ch=change_root; ch; ch = ch->next)
    if ((strncmp(fname, ch->old, strlen(ch->old)) == 0) && ch->isdir)
    {
      if (ch->isdir == 2)
      {
        printf("  [ skipping %s ]\n", fname);
        return 0;
      }
/*      printf("  [ changing %s to ", fname); */
      sprintf(new, "%s%s", ch->new, fname+strlen(ch->old));
      strcpy(fname, new);
/*      printf("%s ]\n", fname); */
      return 1;
    }
  printf("  %s %s\n  new name : ", problem, fname);
  gets(new);
  if ((strcmp(new, "") == 0) && (isadir == 2))
    return 0;
  if (isadir) isadir=1;
  ch = (CHANGE *)malloc(sizeof(CHANGE));
  ch->next = change_root;
  change_root = ch;
  ch->old = strdup(fname);
  pos = strrchr(fname, '/');
  if (pos && (strchr(new, '/') == 0))
  {
    ch->new = (char *)malloc(strlen(new) + (pos-fname) + 2);
    *pos = 0;
    sprintf(ch->new, "%s/%s", fname, new);
  }
  else
    ch->new = strdup(new);
  ch->isdir = isadir;
  strcpy(fname, ch->new);
  if (new[0] == 0)
  {
    ch->isdir = 2;
    return 0;
  }
  return 1;
}

/*------------------------------------------------------------------------*/

typedef struct {
  char name[100];
  char operm[8];
  char ouid[8];
  char ogid[8];
/*  char osize[11];*/
  char osize[12];
  char otime[12];
  char ocsum[8];
  char flags[1];
  char linkname[100];
  char filler[255];
} TARREC;

char buf[512];

tarread(char *fname)
{
  TARREC header;
  int f, r;
  long perm, uid, gid, size, time, csum;
  int dsize;
  f = open(fname, O_RDONLY|O_BINARY);

  while (1)
  {
    if (read(f, &header, 512) < sizeof(header))
      break;
    if (header.name[0] == 0)
      break;
    sscanf(header.operm, "%lo", &perm);
    sscanf(header.ouid, "%lo", &uid);
    sscanf(header.ogid, "%lo", &gid);
    sscanf(header.osize, "%lo", &size);
    sscanf(header.otime, "%lo", &time);
    printf("%6lo %02x %12ld %s\n", perm, header.flags[0], size, header.name);
    if (header.flags[0] != 0) {
	printf("Linked file skipped\n");
	continue;
    }
    if (header.name[strlen(header.name)-1] == '/')
    {
      header.name[strlen(header.name)-1] = 0;
      do {
        printf("Making directory %s\n", header.name);
        convert_file(header.name);
        r = mkdir(header.name,0);
	break; /* we don't want to know about any errors!*/
        if (r && (errno==EACCES))
        {
          change(header.name, "Duplicate directory name", 2);
          break;
        }
        if (r)
          r = change(header.name, "Unable to create directory", 1);
      } while (r);
    }
    else
    {
    open_file:
      convert_file(header.name);
      r = open(header.name, O_WRONLY|O_BINARY|O_CREAT|O_EXCL, S_IWRITE|S_IREAD);
      if (r < 0)
/*        if (change(header.name, "Cannot exclusively open file", 0))
          goto open_file;
        else  - we don't want to know about any errors! - ignore them*/
        {
          lseek(f, (size+511) & ~511, 1);
        }
      else
      {
        while (size)
        {
          if (size < 512)
            dsize = size;
          else
            dsize = 512;
          read(f, buf, 512);
          if (write(r, buf, dsize) < dsize)
          {
            printf("Out of disk space\n");
            exit(1);
          }
          size -= dsize;
        }
        close(r);
      }
    }
  }
  close(f);
}
char *of[500], *nf[500];
int fl = 0;
read_convert()
{
  FILE *inp;
  char buffer[1024], *p, *q;
  bzero(buffer,1024);
  p = getenv("ISODEI");
  if (p) strcpy(buffer, p);
  strcat(buffer,"/utils/convert.lst");
  if ((inp = fopen(buffer,"r")) == NULL) return;
  while (fgets(buffer, 1024, inp) != NULL) {
    p = strtok(buffer,"\t");
    if (p == NULL) break;
    of[fl] = malloc(strlen(p)+1);
    strcpy(of[fl], p);
    p = strtok(NULL, "\t\n");
    if (p == NULL) {
      of[fl] = NULL;
      break;
    }
    nf[fl] = malloc(strlen(p)+strlen(of[fl]));
    strcpy(nf[fl], of[fl]);
    q = strrchr(nf[fl],'/');
    *(q+1) = '\0';
    strcat(nf[fl],p);
    fl++;
  }
  fclose(inp);
}
convert_file(s)
char *s;
{
  int i;
  char *p;

  p = s;
  while ((p = strchr(p, '=')) != NULL) *p = '_';
  p = s;
  while ((p = strchr(p, ' ')) != NULL) *p = '_';
  for (i=0; i<fl; i++) {
    if (strcmp(s, of[i]) == 0) {
      printf("%s converted to %s\n",s,nf[i]);
      strcpy(s, nf[i]);
      return;
    }
  }
}
