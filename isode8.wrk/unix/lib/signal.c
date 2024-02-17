int sigsetmask(mask)
int mask;
{
/*	printf("sigsetmask called\n");*/
}

int sigblock(mask)
int mask;
{
/*	printf("sigblock called\n");*/
}

int sigmask(signum)
int signum;
{
/*	printf("sigmask called\n");*/
}

int kill(pid, sig)
int pid;
int sig;
{
	printf("kill called\n");
}

