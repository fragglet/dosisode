/****************************************************************/
/* Endwin() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Changed call sequence to cursesio.[c,asm], Thanks	*/
/*	to S. Creps. Rcsid[] string for maintenance:	881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_endwin_rcsid[] = "@(#)endwin.c v1.3 - 881005";

/****************************************************************/
/* Endwin() does necessary clean-up after using the PCcurses	*/
/* package. It should be called before exiting the user's pro-	*/
/* gram.							*/
/****************************************************************/

int endwin()
  {
  delwin(stdscr);
  delwin(curscr);
  delwin(_cursvar.tmpwin);
  curson();				/* turn on cursor if off */
  _cursescursor(LINES-1, 0);		/* put at lower left */
  _cursesscb(_cursvar.orgcbr);		/* restore original ^BREAK setting */
  return(OK);
  } /* endwin */
