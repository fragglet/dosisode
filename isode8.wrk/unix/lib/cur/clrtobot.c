/****************************************************************/
/* Wclrtobot() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.1:	Renamed clrbot() to clrtobot(). Reported by		*/
/*	Eric Rosco:					870907	*/
/* 1.2:	Max limits off by 1. Fixed thanks to S. Creps:	881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_clrtobot_rcsid[] = "@(#)clrtobot.c v1.3 - 881005";

/****************************************************************/
/* Wclrtobot() fills the right half of the cursor line of	*/
/* window 'win', and all lines below it with blanks.		*/
/****************************************************************/

int	wclrtobot(win)
  WINDOW	*win;
  {
  int	 y;
  int   minx;
  static int	 startx;
  static int	*ptr;
  static int    *end;
  static int    *maxx;
  static int     blank;

  blank = ' ' | (win->_attrs & ATR_MSK);
  startx = win->_curx;
  for (y = win->_cury; y <= win->_regbottom; y++)
    {
    minx = _NO_CHANGE;
    end = &win->_line[y][win->_maxx - 1];
    for (ptr = &win->_line[y][startx]; ptr <= end; ptr++)
      {
      if (*ptr != blank)
	{
	maxx = ptr;
	if (minx == _NO_CHANGE)
	  minx = ptr - win->_line[y];
	*ptr = blank;
	} /* if */
      } /* for */
    if (minx != _NO_CHANGE)
      {
      if ((win->_minchng[y] > minx) ||  (win->_minchng[y] == _NO_CHANGE))
	win->_minchng[y] = minx;
      if (win->_maxchng[y] < maxx - win->_line[y])
	win->_maxchng[y] = maxx - win->_line[y];
      } /* if */
    startx = 0;
    } /* for */
  return(OK);
  } /* wclrtobot */

/****************************************************************/
/* Clrtobot() fills the right half of the cursor line of	*/
/* stdscr, and all lines below it with blanks.			*/
/****************************************************************/

int clrtobot()
  {
  return(wclrtobot(stdscr));
  } /* clrtobot */

/****************************************************************/
/* Mvclrtobot() moves the cursor to a new position in stdscr	*/
/* and fills the right half of the cursor line, and all lines	*/
/* below it with blanks.					*/
/****************************************************************/

int mvclrtobot(y,x)
  int y;
  int x;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return(wclrtobot(stdscr));
  } /* mvclrtobot */

/****************************************************************/
/* Mvwclrtobot() moves the cursor to a new position in window	*/
/* 'win', and fills the right half of the cursor line, and all	*/
/* lines below it with blanks.					*/
/****************************************************************/

int mvwclrtobot(win,y,x)
  WINDOW *win;
  int y;
  int x;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return(wclrtobot(win));
  } /* mvwclrtobot */
