/****************************************************************/
/* Wsetscrreg() routine of the PCcurses package			*/
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

char _curses_scrreg_rcsid[] = "@(#)scrreg.c v1.3 - 881005";

/****************************************************************/
/* Wsetscrreg() set the scrolling region of window 'win' to in-	*/
/* clude all lines between 'top' and 'bottom'.			*/
/****************************************************************/

int wsetscrreg(win, top, bottom)
  WINDOW	*win;
  int		 top;
  int		 bottom;
  {
  if (  (0 <= top)
	&&
	(top <= win->_cury)
	&&
	(win->_cury <= bottom)
	&&
	(bottom < win->_maxy)
     )
    {
    win->_regtop = top;
    win->_regbottom = bottom;
    return(OK);
    } /* if */
  else
    return(ERR);
  } /* wsetscrreg */

/****************************************************************/
/* Setscrreg() set the scrolling region of stdscr to include	*/
/* all lines between 'top' and 'bottom'.			*/
/****************************************************************/

int setscrreg(top, bottom)
  int top;
  int bottom;
  {
  return(wsetscrreg(stdscr,top,bottom));
  } /* setscrreg */
