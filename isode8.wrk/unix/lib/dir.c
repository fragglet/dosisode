#include <string.h>
#include <dir.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

DIR *opendir(char *name)
{
  DIR *dir;
  struct stat *s;
  int i;

  i = stat(name,s);
  if (i == -1) return(NULL);
  dir = (DIR *)malloc(sizeof(DIR));
  dir->num_read = 0;
  dir->name = (char *)malloc(strlen(name)+5);
  strcpy(dir->name, name);
  strcat(dir->name, "/*.*");
  return dir;
}

struct dirent *readdir(DIR *dir)
{
  int done;
  if (dir->num_read)
    done = findnext(&dir->ff);
  else
    done = findfirst(dir->name, &dir->ff, FA_ARCH|FA_RDONLY|FA_DIREC);
  if (done)
    return 0;
  dir->num_read ++;
  dir->de.d_namlen = strlen(dir->ff.ff_name);
  strcpy(dir->de.d_name,dir->ff.ff_name);
  strlwr(dir->de.d_name);
  return &dir->de;
}

long telldir(DIR *dir)
{
  return dir->num_read;
}

void seekdir(DIR *dir, long loc)
{
  int i;
  rewinddir(dir);
  for (i=0; i<loc; i++)
    readdir(dir);
}

void rewinddir(DIR *dir)
{
  dir->num_read = 0;
}

int closedir(DIR *dir)
{
  free(dir->name);
  free(dir);
}

