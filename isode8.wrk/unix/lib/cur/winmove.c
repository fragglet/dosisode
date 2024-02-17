/****************************************************************/
/* Mvwin() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Max limits off by 1. Fixed thanks to S. Creps:	881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_winmove_rcsid[] = "@(#)winmove.c v1.3 - 881005";

/****************************************************************/
/* Mvwin() moves window 'win' to position (begx, begy) on the	*/
/* screen.							*/
/****************************************************************/

int	mvwin(win, begy, begx)
  WINDOW	*win;
  int		 begy, begx;
  {
  if ((begy + win->_maxy) >= (LINES-1) || (begx + win->_maxx) > (COLS-1))
    return(ERR);
  win->_begy = begy;
  win->_begx = begx;
  touchwin(win);
  return(OK);
  } /* mvwin */
