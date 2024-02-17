/****************************************************************/
/* Delwin() routine of the PCcurses package.			*/
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

char _curses_windel_rcsid[] = "@(#)windel.c v1.3 - 881005";

/****************************************************************/
/* Delwin() deallocates all data allocated by 'win'. If 'win'	*/
/* is a subwindow, it uses the original window's lines for sto-	*/
/* rage, and thus the line arrays are not deallocated.		*/
/****************************************************************/

void delwin(win)
  WINDOW	*win;
  {
  int		 i;

  if (! (win->_flags & _SUBWIN))	/* subwindow uses 'parent's' lines */
    {
    for (i = 0; i < win->_maxy && win->_line[i]; i++)
      free(win->_line[i]);
    }
  free(win->_minchng);
  free(win->_maxchng);
  free(win->_line);
  free(win);
  } /* delwin */
