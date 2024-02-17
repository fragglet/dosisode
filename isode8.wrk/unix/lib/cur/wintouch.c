/****************************************************************/
/* Touchwin() routine of the PCcurses package			*/
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

char _curses_wintouch_rcsid[] = "@(#)wintouch.c v1.3 - 881005";

/****************************************************************/
/* Touchwin() marks all lines of window 'win' as changed, from	*/
/* the first to the last character on the line.			*/
/****************************************************************/

void touchwin(win)
  WINDOW	*win;
  {
  int	y;
  int  maxy;
  int  maxx;

  maxy = win->_maxy - 1;
  maxx = win->_maxx - 1;

  for (y = 0; y <= maxy; y++)
    {
    win->_minchng[y] = 0;
    win->_maxchng[y] = maxx;
    } /* for */
  } /* touchwin */
