#include <stdio.h>
#include <ctype.h>

static char *verify();

main(argc, argv)
int argc;
char *argv[];
{
  int i;
  char olds[256], news[256], *t, *strcat();
  FILE *fopen(), *infile, *outfile;
  char line[256], temp[256], filename[128], newfile[128];

  if (argc < 3) {
     printf("Usage:String_replace filename newfile oldstring newstring \n");
     exit();
  }

  strcpy(filename,argv[1]);
  strcpy(newfile,argv[2]);
  strcpy(olds,argv[3]); i = strlen(olds);
  strcpy(news,argv[4]);

  if ( (infile = fopen(filename,"r")) == NULL) {
     printf("%s does not exist\n",argv[1]);
     exit();
  }
  if ( (outfile = fopen(newfile,"w")) == NULL) {
     printf("Cannot open output file\n");
     exit();
  }
   while (fgets(line,256,infile) != NULL) {
      while ( (t = verify(line,olds)) ) {
         *t = '\0';
         strcpy(temp,t+i);
         strcat(line,news);
         strcat(line,temp);
      }
      fprintf(outfile,"%s",line);
   }
   fclose(outfile);
   fclose(infile);
   exit(0);
}

static char *verify(s,t)
char *s, *t;
{
   int i;
   i = strlen(t);
   while (*s != NULL) {
      if (strncmp(s,t,i) == 0) return(s);
      s++;
   }
   return(NULL);
 }
