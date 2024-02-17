/****************************************************************/
/* Box border control routines of the PCcurses package.		*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.3:	Released:					881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_border_rcsid[] = "@(#)border.c v1.3 - 881005";

/****************************************************************/
/* Wborder() sets the border characters in window win.		*/ 
/****************************************************************/

void wborder(win, l, r, t, b, tl, tr, bl, br)
  WINDOW	*win;
  int		 l;
  int		 r;
  int		 t;
  int		 b;
  int		 tl;
  int		 tr;
  int		 bl;
  int		 br;
  {
  win->_borderchars[0] = (char) l;
  win->_borderchars[1] = (char) r;
  win->_borderchars[2] = (char) t;
  win->_borderchars[3] = (char) b;
  win->_borderchars[4] = (char) tl;
  win->_borderchars[5] = (char) tr;
  win->_borderchars[6] = (char) bl;
  win->_borderchars[7] = (char) br;
  } /* wborder */

/****************************************************************/
/* Border() sets the border characters in the stdscr window.	*/ 
/* Don't make this a call to wborder() - it would require soo	*/
/* much stack for parameters...					*/
/****************************************************************/

void border(l, r, t, b, tl, tr, bl, br)
  int		 l;
  int		 r;
  int		 t;
  int		 b;
  int		 tl;
  int		 tr;
  int		 bl;
  int		 br;
  {
  stdscr->_borderchars[0] = (char) l;
  stdscr->_borderchars[1] = (char) r;
  stdscr->_borderchars[2] = (char) t;
  stdscr->_borderchars[3] = (char) b;
  stdscr->_borderchars[4] = (char) tl;
  stdscr->_borderchars[5] = (char) tr;
  stdscr->_borderchars[6] = (char) bl;
  stdscr->_borderchars[7] = (char) br;
  } /* border */
