#ifndef SOCKIT_FIX
#define SOCKIT_FIX

#define fopen	si_fopen
#define freopen	si_freopen
#define open	si_open
#define remove	si_remove

#define read	si_read
#define write	si_write
#define fclose	si_fclose
#define close	si_close
#define ioctl	si_ioctl
#define dup	si_dup
#define dup2	si_dup2
#define fdopen	si_fdopen
#define fprintf	si_fprintf
#define fgets	si_fgets
#define fputc	si_fputc
#define fputs	si_fputs
#define rewind	si_rewind
#define fflush	si_fflush
#define fcntl	si_fcntl
#define malloc	si_malloc
#define calloc	si_calloc
#define realloc	si_realloc
#define free	si_free
#define cfree	si_cfree
#define opendir	si_opendir
#define getuid	si_getuid
#define geteuid	si_geteuid

#define gmtime	localtime /*better than NULL!*/
#endif
