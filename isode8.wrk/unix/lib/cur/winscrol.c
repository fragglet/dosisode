/****************************************************************/
/* Scroll() routine of the PCcurses package			*/
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

char _curses_winscrol_rcsid[] = "@(#)winscrol.c v1.3 - 881005";

/****************************************************************/
/* Scroll() scrolls the scrolling region of 'win', but only if	*/
/* scrolling is allowed and if the cursor is inside the scrol-	*/
/* ling region.							*/
/****************************************************************/

void	scroll(win)
  WINDOW	*win;
  {
  int		 i;
  int		*ptr;
  int		*temp;
  static   int	 blank;

  blank = ' ' | (win->_attrs & ATR_MSK);
  if  (	   (!win->_scroll)			/* check if window scrolls */
	|| (win->_cury < win->_regtop)		/* and cursor in region */
        || (win->_cury > win->_regbottom)
      )
    return;

  temp = win->_line[win->_regtop];
  for (i = win->_regtop; i < win->_regbottom; i++)
    {
    win->_line[i] = win->_line[i+1];		/* re-arrange line pointers */
    win->_minchng[i] = 0;
    win->_maxchng[i] = win->_maxx - 1;
    }
  for (ptr = temp; ptr - temp < win->_maxx; ptr++)
    *ptr = blank;				/* make a blank line */
  win->_line[win->_regbottom] = temp;
  if (win->_cury > win->_regtop)		/* if not on top line */
    win->_cury--;				/* cursor scrolls too */
  win->_minchng[win->_regbottom] = 0;
  win->_maxchng[win->_regbottom] = win->_maxx - 1;
  } /* scroll */
