#include <stdio.h>
#include <stddef.h>
#include <strings.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/stat.h>

char *unix2dos();
static int debug = 0;
extern int si_xlate[];

FILE *si_fopen(filename, mode)
char *filename, *mode;
{
	FILE *fp;
if (debug) fprintf(stderr,"si_fopen filename=%s _fmode=%x\n",filename,_fmode);
	fp = fopen(unix2dos(filename), mode);
	return(fp);
}

FILE *si_freopen(filename, mode, stream)
char *filename, *mode;
FILE *stream;
{
	return(freopen(unix2dos(filename), mode, stream));
}

int si_open(filename, mode, x)
char *filename;
int mode, x;
{
	int i;
if (debug) fprintf(stderr,"si_open filename=%s _fmode=%x\n",filename,_fmode);
	i = open(unix2dos(filename), mode);
	if (i != -1) si_xlate[i] = i;
	return(i);
}

int si_remove(filename)
char *filename;
{
	return(remove(unix2dos(filename)));
}

int si_dup(s)
int s;
{
	int i;
	i = dup(s);
	if (i != -1) si_xlate[i] = s;
	return(i);
}

int si_dup2(s,t)
int s,t;
{
	int i;
	i = dup2(s,t);
	if (i != -1) si_xlate[i] = s;
	return(i);
}

openlog(ident, logopt, facility)
char *ident;
int logopt, facility;
{
	printf("openlog called\n");
}

syslog(priority, message)
int priority;
char *message;
{
	printf("syslog called\n");
}

closelog()
{
	printf("closelog called\n");
}
