/****************************************************************/
/* Winsertln() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.1:	Mvinsertln() and friends were misrenamed:	880305	*/
/* 1.2:	Max limits off by 1. Fixed thanks to S. Creps:	881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_lineins_rcsid[] = "@(#)lineins.c v1.3 - 881005";

/****************************************************************/
/* Winsertln() inserts a blank line instead of the cursor line	*/
/* in window 'win' and pushes other lines down.			*/
/****************************************************************/

int	winsertln(win)
  WINDOW	*win;
  {
  int		*temp;
  int		*end;
  short	 y;
  static   int	 blank;
  
  blank = ' ' | (win->_attrs & ATR_MSK);
  temp = win->_line[win->_regbottom];
  for (y = win->_regbottom;  y > win->_cury;  y--)
    {
    win->_line[y] = win->_line[y-1];
    win->_minchng[y] = 0;
    win->_maxchng[y] = win->_maxx - 1;
    } /* for */
  win->_line[win->_cury] = temp;
  for (end = &temp[win->_maxx -1];  temp <= end;  temp++)
    *temp = blank;
  win->_minchng[win->_cury] = 0;
  win->_maxchng[win->_cury] = win->_maxx - 1;
  return(OK);
  } /* winsertln */

/****************************************************************/
/* Insertln() inserts a blank line instead of the cursor line	*/
/* in stdscr and pushes other lines down.			*/
/****************************************************************/

int insertln()
  {
  return(winsertln(stdscr));
  } /* insertln */

/****************************************************************/
/* Mvinsertln() moves the stdscr cursor to a new positions, in-	*/
/* serts a blank line instead of the cursor line and pushes	*/
/* other lines down.						*/
/****************************************************************/

int mvinsertln(y,x)
  int y;
  int x;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return(winsertln(stdscr));
  } /* mvinsertln */

/****************************************************************/
/* Mvwinsertln() moves the cursor in window 'win' to a new po-	*/
/* si tions, inserts a blank line instead of the cursor line	*/
/* and pushes other lines down.					*/
/****************************************************************/

int mvwinsertln(win,y,x)
  WINDOW *win;
  int y;
  int x;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return(winsertln(win));
  } /* mvwinsertln */
