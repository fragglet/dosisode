/****************************************************************/
/* Wclrtoeol() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Max limits off by 1. Fixed thanks to S. Creps:	880210	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_clrtoeol_rcsid[] = "@(#)clrtoeol.c v1.3 - 881005";

/****************************************************************/
/* Wclrtoeol() fills the half of the cursor line to the right	*/
/* of the cursor in window 'win' with blanks.			*/
/****************************************************************/

int	wclrtoeol(win)
   WINDOW	*win;
  {
  int		*maxx;
  int		*ptr;
  int		*end;
  static int	 y;
  static int	 x;
  static int	 minx;
  static int 	 blank;
  
  y = win->_cury;
  x = win->_curx;
  blank = ' ' | (win->_attrs & ATR_MSK);

  end = &win->_line[y][win->_maxx - 1];
  minx = _NO_CHANGE;
  maxx = &win->_line[y][x];
  for (ptr = maxx; ptr <= end; ptr++)
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
    if (win->_minchng[y] > minx || win->_minchng[y] == _NO_CHANGE)
      win->_minchng[y] = minx;
    if (win->_maxchng[y] < maxx - win->_line[y])
      win->_maxchng[y] = maxx - win->_line[y];
    } /* if */
  return(OK);
  } /* wclrtoeol */

/****************************************************************/
/* Clrtoeol() fills the half of the cursor line to the right	*/
/* of the cursor in stdscr with blanks.				*/
/****************************************************************/

int clrtoeol()
  {
  return(wclrtoeol(stdscr));
  } /* clrtoeol */

/****************************************************************/
/* Mvclrtoeol() moves the cursor to a new position in stdscr	*/
/* and fills the right half of the cursor line with blanks.	*/
/****************************************************************/

int mvcltoreol(y,x)
  int y;
  int x;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return(wclrtoeol(stdscr));
  } /* mvclrtoeol */

/****************************************************************/
/* Mvwclrtoeol() moves the cursor to a new position in window	*/
/* 'win', and fills the right half of the cursor line with	*/
/* blanks.							*/
/****************************************************************/

int mvwclrtoeol(win,y,x)
  WINDOW *win;
  int y;
  int x;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return(wclrtoeol(win));
  } /* mvwclrtoeol */
