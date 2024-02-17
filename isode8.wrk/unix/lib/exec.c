#include <stdio.h>

int exec(char *, ...);
static int debug = 0;
int exec(filename)
char *filename;
{
if (debug) fprintf(stderr,"exec called\n");
	return(0);
}
int execv(filename,x)
const char *filename;
const char **x;
{
if (debug) fprintf(stderr,"execv called\n");
	return(0);
}
