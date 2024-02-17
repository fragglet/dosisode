/****************************************************************/
/*								*/
/* Erase() routines of the PCcurses package			*/
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

char _curses_winerase_rcsid[] = "@(#)winerase.c v1.3 - 881005";

/****************************************************************/
/* Werase() fills all lines of window 'win' with blanks and po-	*/
/* sitions the cursor at home in the scroll region.		*/
/****************************************************************/

void	werase(win)
  WINDOW	*win;
  {
  int		*end;
  int		*start;
  short		 y;
  static   int	 blank;
  
  blank = ' ' | (win->_attrs & ATR_MSK);

  for (y = win->_regtop; y <= win->_regbottom; y++)	/* clear all lines */
    {
    start = win->_line[y];
    end = &start[win->_maxx - 1];
    while (start <= end)				/* clear all line */
      *start++ = blank;
    win->_minchng[y] = 0;
    win->_maxchng[y] = win->_maxx - 1;
    }
  win->_cury = win->_regtop;				/* cursor home */
  win->_curx = 0;
  } /* werase */

/****************************************************************/
/* Erase() fills all lines of stdscr with blanks and positions	*/
/* the cursor at home in the scroll region.			*/
/****************************************************************/

void erase()
  {
  werase(stdscr);
  } /* erase */
