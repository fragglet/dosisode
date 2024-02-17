#include <stdio.h>
#include <dos.h>
int get1c()
{
	union REGS regs;
	fflush(stdout);fflush(stderr);

	regs.x.ax = 0x0700;
	int86(0x21,&regs,&regs);
	if (regs.h.al == 0x0d) regs.h.al = 0x0a;
	return(regs.h.al);
}

tgetent(bp, name)
char *bp, *name;
{
/*fprintf(stderr,"tgetent called\n");*/
   return(1);
}

tgetnum(id)
char *id;
{
/*fprintf(stderr,"tgetnum called\n");*/
   return(0);
}

tgetflag(id)
char *id;
{
/*fprintf(stderr,"tgetflag called\n");*/
   return(0);
}

char *tgetstr(id, area)
char *id, **area;
{
/*fprintf(stderr,"tgetstr called\n");*/
   return("");
}

char *tgoto(cm, destcol, destline)
char *cm;
int destcol, destline;
{
/*fprintf(stderr,"tgoto called\n");*/
}

tputs(cp, affcnt, outc)
char *cp;
int affcnt;
int (*outc)();
{
/*fprintf(stderr,"tputs called\n");*/
}
