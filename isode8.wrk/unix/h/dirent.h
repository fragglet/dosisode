#ifndef __PKDIR
#define __PKDIR
#include "sys\types.h"
#define MAXNAMLEN 14
struct dirent {
 u_short d_namlen;
 char d_name[MAXNAMLEN + 1];
 off_t d_off;
 u_long d_fileno;
 u_short d_reclen;
};
#define d_ino d_fileno
typedef struct _dirdesc {
  int num_read;
  char *name;
  char ff_reserved[21];
  char ff_attrib;
  short ff_ftime;
  short ff_fdate;
  short ff_filler;
  long dd_size;
  char ff_name[16];
  struct dirent ioDirent;
 int dd_fd;
 long dd_loc;
 long dd_bbase;
 long dd_entno;
 long dd_bsize;
 char *dd_buf;
 long ioDirID;
 int  ioFDirIndex;
} DIR;
extern DIR *opendir(char *);
extern struct dirent *readdir(DIR *);
extern long telldir(DIR *);
extern seekdir(DIR *, long);
#define rewinddir(dirp) seekdir((dirp), (long)0)
extern closedir(DIR *);
#endif

