/****************************************************************/
/* Wdelch() routine of the PCcurses package			*/
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

char _curses_chardel_rcsid[] = "@(#)chardel.c v1.3 - 881005";

/****************************************************************/
/* Wdelch() deletes the character at the window cursor, and the	*/
/* characters to the right of it are shifted left, inserting a	*/
/* space at the last position of the line.			*/
/****************************************************************/

int	wdelch(win)
  WINDOW	*win;
  {
  int		*temp1;
  int		*temp2;
  int		*end;
  short	 y = win->_cury;
  short	 x = win->_curx;
  short	 maxx = win->_maxx - 1;

  end = &win->_line[y][maxx];
  temp1 = &win->_line[y][x];
  temp2 = temp1 + 1;
  while (temp1 < end)
    *temp1++ = *temp2++;
  *temp1 = ' ' | (win->_attrs & ATR_MSK);
  win->_maxchng[y] = maxx;
  if (win->_minchng[y] == _NO_CHANGE || win->_minchng[y] > x)
    win->_minchng[y] = x;
  return(OK);
  } /* wdelch */

/****************************************************************/
/* Delch() deletes the character at the stdscr cursor, and the	*/
/* characters to the right of it are shifted left, inserting a	*/
/* space at the last position of the line.			*/
/****************************************************************/

int delch()
  {
  return(wdelch(stdscr));
  } /* delch */

/****************************************************************/
/* Mvdelch() moves the stdscr cursor to a new position, then	*/
/* deletes the character at the stdscr cursor, and the charac-	*/
/* ters to the right of it are shifted left, inserting a space	*/
/* at the last position of the line.				*/
/****************************************************************/

int mvdelch(y,x)
  int y;
  int x;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return(wdelch(stdscr));
  } /* mvdelch */

/****************************************************************/
/* Mvwdelch() moves the cursor of window 'win' to a new posi-	*/
/* tion, then deletes the character at the stdscr cursor, and	*/
/* the characters to the right of it are shifted left, inser-	*/
/* ting a space at the last position of the line.		*/
/****************************************************************/

int mvwdelch(win,y,x)
  WINDOW *win;
  int y;
  int x;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return(wdelch(win));
  } /* mvwdelch */
