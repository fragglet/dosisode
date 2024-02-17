/****************************************************************/
/* Tabsize() routines of the PCcurses package			*/
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

char _curses_tabsize_rcsid[] = "@(#)tabsize.c v1.3 - 881005";

/****************************************************************/
/* Wtabsize(win,ts) sets the tabsize of window 'win' to 'ts',	*/
/* and returns the original value.				*/
/****************************************************************/

int	wtabsize(win,ts)
  WINDOW	*win;
  int		 ts;
  {
  int		 origval;

  origval = win->_tabsize;
  win->_tabsize = ts;
  return(origval);
  } /* wtabsize*/

/****************************************************************/
/* Tabsize(ts) sets the tabsize of stdscr to 'ts', and returns	*/
/* the original value.						*/
/****************************************************************/

int	tabsize(ts)
  int		 ts;
  {
  int		 origval;

  origval = stdscr->_tabsize;
  stdscr->_tabsize = ts;
  return(origval);
  } /* tabsize */
