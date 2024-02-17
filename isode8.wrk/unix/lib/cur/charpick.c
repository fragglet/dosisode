/****************************************************************/
/* Winch() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Rcsid[] string for maintenance:			881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_charpick_rcsid[] = "@(#)charpick.c v1.3 - 881005";

/****************************************************************/
/* Winch(win) returns the character at the current position in	*/
/* window 'win'.						*/
/****************************************************************/

int	winch(win)
  WINDOW	*win;
  {
  return((win->_line[win->_cury][win->_curx]) & 0xff);
  } /* winch */

/****************************************************************/
/* Inch() returns the character at the current cursor position	*/
/* in stdscr.							*/
/****************************************************************/

int inch()
  {
  return((stdscr->_line[stdscr->_cury][stdscr->_curx]) & 0xff);
  } /* inch */

/****************************************************************/
/* Mvinch() moves the stdscr cursor to a new position, then	*/
/* returns the character at that position.			*/
/****************************************************************/

int mvinch(y,x)
  int  y;
  int  x;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return((stdscr->_line[stdscr->_cury][stdscr->_curx]) & 0xff);
  } /* mvinch */

/****************************************************************/
/* Mvwinch() moves the cursor of window 'win' to a new posi-	*/
/* tion, then returns the character at that position.		*/
/****************************************************************/

int mvwinch(win,y,x)
  WINDOW *win;
  int  y;
  int  x;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return((win->_line[win->_cury][win->_curx]) & 0xff);
  } /* mvwinch */
