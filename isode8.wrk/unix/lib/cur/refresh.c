/****************************************************************/
/* Wrefresh() and wnoutrefresh() routines of the PCcurses	*/
/* package							*/
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

char _curses_refresh_rcsid[] = "@(#)refresh.c v1.3 - 881005";

/****************************************************************/
/* Wrefresh() updates window win's area of the physical screen.	*/
/****************************************************************/

void wrefresh(win)
  WINDOW	*win;
  {
  if (win == curscr)
    curscr->_clear = TRUE;
  else
    wnoutrefresh(win);
  doupdate();
  } /* wrefresh */

/****************************************************************/
/* Wnoutrefresh() updates the image of the desired screen,	*/
/* without doing physical update (copies window win's image to	*/
/* the _cursvar.tmpwin window, which is hidden from the user).	*/
/****************************************************************/

void wnoutrefresh(win)
  register WINDOW	*win;
  {
  register int	  *dst;			/* start destination in temp window */
  register int    *end;			/* end destination in temp window */
  register int    *src;			/* source in user window */
  register int     first;		/* first changed char on line */
  register int     last;		/* last changed char on line */
  static   WINDOW *nscr;
  static   int	   begy;		/* window's place on screen */
  static   int	   begx;
  static   int	   i;
  static   int	   j;

  nscr = _cursvar.tmpwin;
  begy = win->_begy;
  begx = win->_begx;

  for (i=0, j=begy; i < win->_maxy; i++, j++)
    {
    if (win->_minchng[i] != _NO_CHANGE)
      {
      first = win->_minchng[i];
      last  = win->_maxchng[i];
      dst   = &(nscr->_line[j][begx + first]);
      end   = &(nscr->_line[j][begx + last]);
      src   = &(win->_line[i][first]);

      while (dst <= end) 		/* copy user line to temp window */
	*dst++ = *src++;

      first += begx;			/* nscr's min/max change positions */
      last  += begx;

      if ((nscr->_minchng[j] == _NO_CHANGE)||(nscr->_minchng[j] > first))
	nscr->_minchng[j] = first;
      if (last > nscr->_maxchng[j])
	nscr->_maxchng[j] = last;
      
      win->_minchng[i] = _NO_CHANGE;	/* updated now */
      } /* if */
    win->_maxchng[i] = _NO_CHANGE;	/* updated now */
    } /* for */

  if (win->_clear)
    {
    win->_clear = FALSE;
    nscr->_clear = TRUE;
    } /* if */

  if (!win->_leave)
    {
    nscr->_cury = win->_cury + begy;
    nscr->_curx = win->_curx + begx;
    } /* if */
  } /* wnoutrefresh */

/****************************************************************/
/* Refresh() updates stdscr's area of the physical screen.	*/
/****************************************************************/

void refresh()
  {
  wrefresh(stdscr);
  } /* refresh */
