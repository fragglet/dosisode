#include <stdio.h>
#include <stddef.h>
#include <varargs.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <dir.h>
#include <dirent.h>
#include <sys/stat.h>
#include "si_header.h"

static int debug = 0;
int si_xlate[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31};

DIR *si_opendir(name)
char *name;
{
	struct stat s;
	char buffer[128];
	int i;

if (debug) fprintf(stderr,"opendir trapped %s",name);
	strcpy(buffer,name);
	if (buffer[strlen(buffer)-1] == '/') buffer[strlen(buffer)-1] = '\0';
	i = stat(buffer,&s);
if (debug) fprintf(stderr," stat returns %d\n",i);
	if (i == -1) return(NULL);
	return(opendir(buffer));
}

int si_read(s, buf, nbytes)
int s;
char *buf;
int nbytes;
{
	int i;

if (debug) fprintf(stderr,"si_read called s = %d\n",s);
	if (__sock[si_x(s)].bit.in_use) return(recvfrom(si_x(s), buf, nbytes, 0, 0, 0));
	else {
		i = read(si_x(s), buf, nbytes);
if (debug) fprintf(stderr,"read s=%d si_xlate=%d nbytes = %d i=%d",s,si_x(s),nbytes,i);
		return(i);
	}
}

int si_write(s, buf, nbytes)
int s;
char *buf;
int nbytes;
{
if (debug) fprintf(stderr,"si_write called s=%d si_xlate=%d\n",s,si_x(s));
	if (__sock[si_x(s)].bit.in_use) return(sendto(si_x(s), buf, nbytes, 0, 0, 0));
	else return(write(si_x(s), buf, nbytes));
}

si_fclose(fp)
FILE *fp;
{
	if (__sock[fileno(fp)].bit.in_use) return(si_close(fileno(fp)));
	else return(fclose(fp));
}

FILE *si_fdopen(s, type)
int s;
char *type;
{
	FILE *fp;
	if (__sock[si_x(s)].bit.in_use) return((FILE *)&_iob[si_x(s)]);
	else {
if (debug) fprintf(stderr,"fdopen called s=%d si_xlate=%d\n",s,si_x(s));
		fp = fdopen(si_x(s), type);
		return(fp);
	}
}

si_fprintf(va_alist)
va_dcl
{
	va_list ap;
	char *fmt;
	FILE *fp;
	int cnt, s;
	char buf[1024];

	va_start(ap);
	fp = va_arg(ap, FILE *);
	fmt = va_arg(ap, char *);
	s = fileno(fp);

	if (__sock[s].bit.in_use) {
		vsprintf(buf, fmt, ap);
		cnt = sendto(s, buf, strlen(buf), 0, 0, 0);
	}
	else cnt = vfprintf(fp, fmt, ap);

	va_end(ap);
	return(cnt);
}

char *si_fgets(buf, n, fp)
char *buf;
int n;
FILE *fp;
{
	int s, i;
	char b[1];

/* we need to read a character string from the socket which is */
/* terminated by a nl. Do this the hard way by reading 1 char  */
/* at a time and testing it */
	s = fileno(fp);
	if (__sock[s].bit.in_use) {
		for (i=1; i<n; i++) {
			if (recvfrom(s, b, 1, 0, 0) == 0)  return(0);
			*buf++ = b[0];
			if (b[0] == '\n') break;
		}
		*buf = '\0';
		return(buf);
	}
	else return(fgets(buf, n, fp));
}

si_fgetc(fp)
FILE *fp;
{
	char buf[1];
	int s;

	s = fileno(fp);
	if (__sock[s].bit.in_use) {
		if (recvfrom(s, buf, 1, 0, 0) == 0) return(EOF);
		return(buf[0]);
	}
	else return(fgetc(fp));
}

si_fputc(c, fp)
char c;
FILE *fp;
{
	int s;

	s = fileno(fp);
	if (__sock[s].bit.in_use) return(sendto(s, &c, 1, 0, 0, 0));
	else return(fputc(c, fp));
}

int si_fputs(buf, fp)
char *buf;
FILE *fp;
{
	int s;

	s = fileno(fp);
	if (__sock[s].bit.in_use) return(sendto(s, buf, strlen(buf), 0, 0, 0));
	else return(fputs(buf, fp));
}

si_rewind(fp)
FILE *fp;
{
	int s;

	s = fileno(fp);
	if (__sock[s].bit.in_use) return;
	rewind(fp);
	return;
}

si_fflush(fp)
FILE *fp;
{
	int s;

	s = fileno(fp);
	if (__sock[s].bit.in_use) return(0);
	return(fflush(fp));
}

int si_fcntl(s,cmd,arg)
int s, arg;
unsigned int cmd;
{
	int flags;

	if (__sock[s].bit.in_use) {
		if (cmd == F_SETFL) {
			__sock[s].bit.non_block  = ((arg & FNDELAY) == FNDELAY);
			if (__sock[s].bit.non_block) si_ioctl(s,FIONBIO,NULL);
			__sock[s].bit.sigio  = ((arg & FASYNC) == FASYNC);
			return(0);
		}
		if (cmd == F_GETFL) {
			flags = 0;
			if (__sock[s].bit.non_block == 1) flags |= FNDELAY;
			if (__sock[s].bit.sigio == 1) flags |= FASYNC;
			return(flags);
		}
		printf("Unexpected cmd to fcntl - %d\n",cmd);
		return(-1);
	}
	return(0); /*fcntl(s, cmd, arg));*/
}

void *si_malloc(size)
size_t size;
{
	void *p;
	p = (void *)malloc(size);
	if (p == NULL) {printf("malloc failed size=%d\n",size);getchar();}
	return(p);
}

void *si_calloc(number, size)
size_t number, size;
{
	void *p;
	p = (void *)calloc(number, size);
	if (p == NULL) {printf("calloc failed number=%d size=%d\n",number,size);getchar();}
	return(p);
}

void *si_realloc(ptr, size)
void *ptr;
size_t size;
{
	void *p;
	p = (void *)realloc(ptr, size);
	if (p == NULL) {printf("realloc failed size=%d\n",size);getchar();}
	return(p);
}

void si_free(ptr)
void *ptr;
{
	if (ptr) free(ptr);
	ptr = NULL;
}

void si_cfree(ptr)
void *ptr;
{
	if (ptr) free(ptr);
	ptr = NULL;
}

int si_x(s)
int s;
{
	if (s>=0 && s<32) return(si_xlate[s]);
	else return(-1);
}