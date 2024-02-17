/****************************************************************/
/* Wmove() routine of the PCcurses package			*/
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

char _curses_move_rcsid[] = "@(#)move.c v1.3 - 881005";

/****************************************************************/
/* Wmove() moves the cursor in window 'win' to position (x,y).	*/
/****************************************************************/

int	wmove(win,y,x)
  WINDOW	*win;
  int		 y;
  int		 x;
  {
  if ((x < 0)||(x >= win->_maxx)||(y < win->_regtop)||(y > win->_regbottom))
    return(ERR);
  win->_curx = x;
  win->_cury = y;
  return(OK);
  } /* wmove */

/****************************************************************/
/* Move() moves the cursor in stdscr to position (x,y).		*/
/****************************************************************/

int move(y,x)
  int y;
  int x;
  {
  return(wmove(stdscr,y,x));
  } /* move */
