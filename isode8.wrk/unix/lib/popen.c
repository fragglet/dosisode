#include <stdio.h>

FILE *popen(command,type)
const char *command,*type;
{
	printf("popen called\n");
}

int pclose(stream)
FILE *stream;
{
	printf("pclose called\n");
}

int sys(cmd,sysinput,sysoutput)
char *cmd,*sysinput,*sysoutput;
{
	printf("sys called\n");
}

syscall(number,arg1,arg2,arg3)
int number;
char *arg1, *arg2, *arg3;
{
	printf("syscall called\n");
}
