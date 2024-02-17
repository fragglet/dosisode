/****************************************************************/
/* Winsch() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.1:	Added 'raw' output routines (allows PC charac-		*/
/*	ters < 0x20 to be displayed:			880306	*/
/* 1.2:	Max limits off by 1. Fixed thanks to S. Creps:	881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_charins_rcsid[] = "@(#)charins.c v1.3 - 881005";

/****************************************************************/
/* _Chins() inserts character 'c' at the cursor position in	*/
/* window 'win'. If xlat is true, normal character translation	*/
/* is performed; If xlat is false, the character is output 'as	*/
/* is'.								*/
/****************************************************************/

static	int	_chins(win,c,xlat)
  WINDOW	*win;
  char		 c;
  bool		 xlat;
  {
  int		*temp1;
  int		*temp2;
  int		*end;
  int		 x = win->_curx;
  int		 y = win->_cury;
  int		 maxx = win->_maxx - 1;

  if((c < ' ') && (c == '\n' || c == '\r' || c == '\t' || c == '\b'))
    return(_chadd(win,c,xlat));
  end = &win->_line[y][x];
  temp1 = &win->_line[y][maxx];
  temp2 = temp1 - 1;
  if((c < ' ') && xlat)			/* if CTRL-char make space for 2 */
    temp2--;
  while (temp1 > end)
    *temp1-- = *temp2--;
  win->_maxchng[y] = maxx;
  if ((win->_minchng[y] == _NO_CHANGE) || (win->_minchng[y] > x))
    win->_minchng[y] = x;
  return(_chadd(win,c,xlat));		/* fixes CTRL-chars too */
  } /* _chins */

/****************************************************************/
/* Insch() inserts character 'c' at the cursor position in	*/
/* stdscr. The cursor is advanced.				*/
/****************************************************************/

int insch(c)
  char c;
  {
  return(_chins(stdscr,c,TRUE));
  } /* insch */

/****************************************************************/
/* Winsch() inserts character 'c' at the cursor position in	*/
/* window 'win'. The cursor is advanced.			*/
/****************************************************************/

int winsch(win,c)
  WINDOW *win;
  char c;
  {
  return(_chins(win,c,TRUE));
  } /* winsch */

/****************************************************************/
/* Mvinsch() moves the stdscr cursor to a new position, then	*/
/* inserts character 'c' at the cursor position in stdscr. The	*/
/* cursor is advanced.						*/
/****************************************************************/

int mvinsch(y,x,c)
  int  y;
  int  x;
  char c;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return(_chins(stdscr,c,TRUE));
  } /* mvinsch */

/****************************************************************/
/* Mvwinsch() moves the cursor of window 'win' to a new posi-	*/
/* tion, then inserts character 'c' at the cursor position in	*/
/* window 'win'. The cursor is advanced.			*/
/****************************************************************/

int mvwinsch(win,y,x,c)
  WINDOW *win;
  int  y;
  int  x;
  char c;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return(_chins(win,c,TRUE));
  } /* mvwinsch */

/****************************************************************/
/* Insrawch() inserts character 'c' at the cursor position in	*/
/* stdscr. Control characters are not interpreted, and the	*/
/* cursor is advanced.						*/
/****************************************************************/

int insrawch(c)
  char c;
  {
  return(_chins(stdscr,c,FALSE));
  } /* insrawch */

/****************************************************************/
/* Winsrawch() inserts character 'c' at the cursor position in	*/
/* window 'win'. Control characters are not interpreted, and	*/
/* the cursor is advanced.					*/
/****************************************************************/

int winsrawch(win,c)
  WINDOW *win;
  char c;
  {
  return(_chins(win,c,FALSE));
  } /* winsrawch */

/****************************************************************/
/* Mvinsrawch() moves the stdscr cursor to a new position, then	*/
/* inserts character 'c' at the cursor position in stdscr.	*/
/* Control characters are not interpreted, and	the cursor is	*/
/* advanced.							*/
/****************************************************************/

int mvinsrawch(y,x,c)
  int  y;
  int  x;
  char c;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return(_chins(stdscr,c,FALSE));
  } /* mvinsrawch */

/****************************************************************/
/* Mvwinsrawch() moves the cursor of window 'win' to a new	*/
/* position, then inserts character 'c' at the cursor position	*/
/* in window 'win'. Control characters are not interpreted, and	*/
/* the cursor is advanced.					*/
/****************************************************************/

int mvwinsrawch(win,y,x,c)
  WINDOW *win;
  int  y;
  int  x;
  char c;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return(_chins(win,c,FALSE));
  } /* mvwinsrawch */
