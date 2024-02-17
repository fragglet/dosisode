#ifndef __SIGNAL__
#define __SIGNAL__

#ifndef	NSIG
#define NSIG	32		/* number of signals */

#define	SIGHUP	1		/* hangup */
#define	SIGINT	2		/* interrupt */
#define	SIGQUIT	3		/* quit */
#define	SIGILL	4		/* illegal instruction (not reset when caught) */
#define	SIGTRAP	5		/* trace trap (not reset when caught) */
#define	SIGIOT	6		/* IOT instruction */
#define	SIGEMT	7		/* EMT instruction */
#define	SIGFPE	8		/* floating point exception */
#define	SIGKILL	9		/* kill (cannot be caught or ignored) */
#define	SIGBUS	10		/* bus error */
#define	SIGSEGV	11		/* segmentation violation */
#define SIGSYS	12		/* bad argument to system call */
#define SIGPIPE	13		/* write to a pipe with no one to read it */
#define SIGALRM	14		/* alarm clock */
#define SIGTERM	15		/* software termination signal from kill */

#define SIGURG	16
#define SIGTSTP	18
#define SIGCHLD	20
#define SIGIO	23


struct	sigvec
{
	int	(*sv_handler)();	/* handler address */
	int	sv_mask;		/* mask of signals to be blocked */
	int	sv_onstack;		/* flag to indicate signal stack */
};

struct	sigcontext
{
	int	sc_onstack;		/* signal stack flag to restore */
	int	sc_mask;		/* signal mask to restore */
	int	sc_sp;			/* stack pointerto restore */
	int	sc_pc;			/* pc to return to */
	int	sc_ps;			/* psl to restore */
};

struct	sigstack
{
	char	*ss_sp;			/* signal stack pointer */
	int	ss_onstack;		/* current status */
};

#define	BADSIG	(int (*)())-1
#define SIG_DFL ((void (*)(int)) 1)
#define SIG_ERR ((void (*)(int)) -1)
#define SIG_IGN (0)
#define SIG_HOLD ((void (*)(int)) 3)
#define SIG_RELEASE ((void (*)(int)) 5)

void (*signal (int sig, void (*func) (int))) (int);
int raise (int sig);
#endif	NSIG
#endif __SIGNAL__