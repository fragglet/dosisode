/****************************************************************/
/* Wdeleteln() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	max limits off by 1. Fixed thanks to S. Creps:	881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_linedel_rcsid[] = "@(#)linedel.c v1.3 - 881005";

/****************************************************************/
/* Wdeleteln() deletes the line at the window cursor, and the	*/
/* lines below it are shifted up, inserting a blank line at	*/
/* the bottom of the window.					*/
/****************************************************************/

int	wdeleteln(win)
  WINDOW	*win;
  {
  int		*end;
  int		*temp;
  short	 y;
  static   int	 blank;
  
  blank = ' ' | (win->_attrs & ATR_MSK);

  temp = win->_line[win->_cury];
  for (y = win->_cury; y < win->_regbottom; y++)
    {
    win->_line[y] = win->_line[y+1];
    win->_minchng[y] = 0;
    win->_maxchng[y] = win->_maxx - 1;
    }
  win->_minchng[y] = 0;
  win->_maxchng[y] = win->_maxx - 1;
  win->_line[win->_regbottom] = temp;
  for (end = &(temp[win->_maxx -1]); temp <= end;)
    *temp++ = blank;
  return(OK);
  } /* wdeleteln */

/****************************************************************/
/* Deleteln() deletes the line at the stdscr cursor, and the	*/
/* lines below it are shifted up, inserting a blank line at	*/
/* the bottom of stdscr.					*/
/****************************************************************/

int deleteln()
  {
  return(wdeleteln(stdscr));
  } /* deleteln */

/****************************************************************/
/* Mvdeleteln() moves the cursor to a new position in stdscr,	*/
/* then deletes the line at the window cursor, and the lines	*/
/* below it are shifted up, inserting a blank line at the bot-	*/
/* tom of stdscr.						*/
/****************************************************************/

int mvdeleteln(y,x)
  int y;
  int x;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return(wdeleteln(stdscr));
  } /* mvdeleteln */

/****************************************************************/
/* Mvwdeleteln() moves the cursor to a new position in a win-	*/
/* dow, then deletes the line at the window cursor, and the	*/
/* lines below it are shifted up, inserting a blank line at	*/
/* the bottom of the window.					*/
/****************************************************************/

int mvwdeleteln(win,y,x)
  WINDOW *win;
  int y;
  int x;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return(wdeleteln(win));
  } /* mvwdeleteln */
