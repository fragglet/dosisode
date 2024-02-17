/****************************************************************/
/* Initscr() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.1:	Revision string in the code:			880306	*/
/* 1.2:	Rcsid[] string for maintenance:			881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_initscr_rcsid[] = "@(#)initscr.c v1.3 - 881005";
char _curses_revcod[] =  CURSES_RCS_ID;
char _curses_cpyrgt[] = "Author B. Larsson - Public Domain";

extern	void	exit();		/* to avoid warings */

WINDOW *curscr;			/* the current screen image */
WINDOW *stdscr;			/* the default screen window */
cursv   _cursvar;		/* curses variables */
int	LINES;			/* terminal height */
int	COLS;			/* terminal width */

/****************************************************************/
/* Initscr() does necessary initializations for the PCcurses	*/
/* package. It MUST be called before any other curses routines.	*/
/****************************************************************/

int initscr()
  {
  _cursvar.cursrow   = -1;		/* Initial cursor unknown */
  _cursvar.curscol   = -1;
  _cursvar.autocr    = TRUE;		/* lf -> crlf by default */
  _cursvar.raw       = FALSE;		/* tty I/O modes */
  _cursvar.cbreak    = FALSE;
  _cursvar.echo      = TRUE;
  _cursvar.refrbrk   = FALSE;		/* no premature end of refresh */
  _cursvar.orgcbr    = (bool)_cursesgcb();/* original ^BREAK setting */

  LINES              = 25;		/* @@@@ this must be fixed */
  COLS               = _cursesgcols();

  if ((_cursvar.tmpwin = newwin(LINES,COLS,0,0)) == (WINDOW *)ERR)
    exit(1);
  if ((curscr = newwin(LINES,COLS,0,0)) == (WINDOW *)ERR)
    exit(1);
  if ((stdscr = newwin(LINES,COLS,0,0)) == (WINDOW *)ERR)
    exit(1);
  curscr->_clear = FALSE;
  return(OK);
  } /* initscr */
