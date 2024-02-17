/****************************************************************/
/* Character attribute routines of the PCcurses package		*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Rcsid[] string for maintenance:			881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_attrib_rcsid[] = "@(#)attrib.c v1.3 - 881005";

/****************************************************************/
/* Wattrset() sets the attributes as specified in window 'win'.	*/
/****************************************************************/

void wattrset(win,attrs)
  WINDOW	*win;
  int		 attrs;
  {
  win->_attrs = attrs & ATR_MSK;
  } /* wattrset */

/****************************************************************/
/* Wattron() sets the specified attribute(s) in window 'win'.	*/
/****************************************************************/

void	wattron(win,attrs)
  WINDOW	*win;
  int		 attrs;
  {
  win->_attrs |= (attrs & ATR_MSK);
  } /* wattron */

/****************************************************************/
/* Wattroff() clears the specified attribute(s) in window	*/
/* 'win'.							*/
/****************************************************************/

void	wattroff(win,attrs)
  WINDOW	*win;
  int		 attrs;
  {
  win->_attrs &= (~attrs & ATR_MSK);
  } /* wattroff */

/****************************************************************/
/* Wstandout() starts standout mode in window 'win'.		*/
/****************************************************************/

void	wstandout(win)
  WINDOW	*win;
  {
  win->_attrs = A_STANDOUT;
  } /* wstandout */

/****************************************************************/
/* Wstandend() clears all special attributes in window 'win'.	*/
/****************************************************************/

void	wstandend(win)
  WINDOW	*win;
  {
  win->_attrs = ATR_NRM;
  } /* wstandend */

/****************************************************************/
/* Attrset() sets the attributes as specified in stdscr.	*/
/****************************************************************/

void	attrset(attrs)
  int attrs;
  {
  stdscr->_attrs = attrs & ATR_MSK;
  } /* attrset */

/****************************************************************/
/* Attron() sets the specified attribute(s) in stdscr.		*/
/****************************************************************/

void	attron(attrs)
  int		 attrs;
  {
  stdscr->_attrs |= (attrs & ATR_MSK);
  } /* attron */

/****************************************************************/
/* Attroff() clears the specified attribute(s) in stdscr.	*/
/****************************************************************/

void	attroff(attrs)
  int		 attrs;
  {
  stdscr->_attrs &= (~attrs & ATR_MSK);
  } /* attroff */

/****************************************************************/
/* Standout() starts standout mode in stdscr.			*/
/****************************************************************/

void	standout()
  {
  stdscr->_attrs = A_STANDOUT;
  } /* standout */

/****************************************************************/
/* Standend() clears all special attributes in stdscr.		*/
/****************************************************************/

void	standend()
  {
  stdscr->_attrs = ATR_NRM;
  } /* standend */
