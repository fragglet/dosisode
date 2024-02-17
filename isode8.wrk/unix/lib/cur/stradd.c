/****************************************************************/
/* Addstr() routines of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Rcsid[] string for maintenance:			881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_stradd_rcsid[] = "@(#)stradd.c v1.3 - 881005";

/****************************************************************/
/* Waddstr() inserts string 'str' at the current cursor posi-	*/
/* tion in window 'win', and takes any actions as dictated by	*/
/* the characters.						*/
/****************************************************************/

int	waddstr(win, str)
  WINDOW	*win; 
  char		*str;
  {
  while (*str)
    {
    if (waddch(win, *str++) == ERR)
      return(ERR);
    }
  return(OK);
  } /* waddstr */

/****************************************************************/
/* Addstr() inserts string 'str' at the current cursor posi-	*/
/* tion in stdscr, and takes any actions as dictated by the	*/
/* characters.							*/
/****************************************************************/

int addstr(str)
  char	 *str;
  {
  return (waddstr(stdscr,str));
  } /* addstr */

/****************************************************************/
/* Mvaddstr() move to a new position in stdscr, then inserts	*/
/* string 'str' at the new position, taking any actions as dic-	*/
/* tated by the characters.					*/
/****************************************************************/

int mvaddstr(y,x,str)
  int	 y;
  int	 x;
  char	*str;
  {
  if (wmove(stdscr,y,x) == ERR)
    return (ERR);
  return (waddstr(stdscr,str));
  } /* mvaddstr */

/****************************************************************/
/* Mvwaddstr() move to a new position in window 'win', then	*/
/* inserts string 'str' at the new position, taking any actions	*/
/* as dictated by the characters.				*/
/****************************************************************/

int mvwaddstr(win,y,x,str)
  WINDOW *win;
  int	  y;
  int	  x;
  char   *str;
  {
  if (wmove(win,y,x) == ERR)
    return (ERR);
  return (waddstr(win,str));
  } /* mvwaddstr */
