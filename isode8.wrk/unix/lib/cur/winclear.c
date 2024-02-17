/****************************************************************/
/* Clear() routines of the PCcurses package			*/
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

char _curses_winclear_rcsid[] = "@(#)winclear.c v1.3 - 881005";

/****************************************************************/
/* Wclear() fills all lines of window 'win' with blanks, and	*/
/* marks the window to be cleared at next refresh operation.	*/
/****************************************************************/

void	wclear(win)
  WINDOW	*win;
  {
  werase(win);
  win->_clear = TRUE;
  } /* wclear */

/****************************************************************/
/* Clear() fills all lines of stdscr with blanks, and marks	*/
/* marks sdtscr to be cleared at next refresh operation.	*/
/****************************************************************/

void clear()
  {
  werase(stdscr);
  stdscr->_clear = TRUE;
  } /* clear */
