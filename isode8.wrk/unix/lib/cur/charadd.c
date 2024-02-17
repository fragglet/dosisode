/****************************************************************/
/* Addch() routines of the PCcurses package			*/
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

char _curses_charadd_rcsid[] = "@(#)charadd.c v1.3 - 881005";

/****************************************************************/
/* Newline() does line advance and returns the new cursor line.	*/
/* If error, return -1.						*/
/****************************************************************/

static	short	newline(win, lin)
  WINDOW	*win;
  short 	 lin;
  {
  if (++lin > win->_regbottom)
    {
    lin--;
    if (win->_scroll)
      scroll(win);
    else
      return(-1);
    } /* if */
  return(lin);
  } /* newline */

/****************************************************************/
/* _Chadd() inserts character 'c' at the current cursor posi-	*/
/* tion in window 'win'. If xlat is TRUE, _chadd() will handle	*/
/* things like tab, newline, cr etc.; otherwise the character	*/
/* is simply output.						*/
/****************************************************************/

int _chadd(win, c, xlat)
  register WINDOW	*win;
  char			 c;
  bool			 xlat;
  {
  short	x = win->_curx;
  short	y = win->_cury;
  short	newx;
  int	ch = c;
  int  	ts = win->_tabsize;

  ch &= 0xff;			/* kill any sing-extend */
  if (y >= win->_maxy  ||  x >= win->_maxx  ||  y < 0  ||  x < 0)
    return(ERR);

  if (xlat)
    {
    switch (ch)
      {
      case '\t':  for (newx = ((x/ts) + 1) * ts; x < newx; x++)
		    {
		    if (waddch(win, ' ') == ERR)
		      return(ERR);
		    if (win->_curx == 0)	/* if tab to next line */
		      return(OK);		/* exit the loop */
		    } /* for */
		  return(OK);
      case '\n':  if (_cursvar.autocr && !(_cursvar.raw)) /* if lf -> crlf */
		    x = 0;
		  if ((y = newline(win, y)) < 0)
		    return(ERR);
		  win->_cury = y;
		  win->_curx = x;
		  return(OK);
      case '\r':  x = 0;
		  win->_curx = x;
		  return(OK);
      case '\b':  if (--x < 0)			/* no back over left margin */
		    x = 0;
		  win->_curx = x;
		  return(OK);
      case 0x7f:  if (waddch(win,'^') == ERR)
		    return(ERR);
		  return(waddch(win,'?'));
      default:	  break;
      } /* switch */
    if (ch < ' ')			/* handle control chars */
      {
      if (waddch(win,'^') == ERR)
	return(ERR);
      return(waddch(win,c + '@'));
      } /* if */
    } /* if xlat*/

  ch |= (win->_attrs & ATR_MSK);
  if (win->_line[y][x] != ch)		/* only if data change */
    {
    if (win->_minchng[y] == _NO_CHANGE)
      win->_minchng[y] = win->_maxchng[y] = x;
    else
      {
      if (x < win->_minchng[y])
	win->_minchng[y] = x;
      else
	{
	if (x > win->_maxchng[y])
	  win->_maxchng[y] = x;
	} /* else */
      } /* else */
    } /* if */
  win->_line[y][x++] = ch;
  if (x >= win->_maxx)			/* wrap around test */
    {
    x = 0;
    if ((y = newline(win, y)) < 0)
      return(ERR);
    } /* if */
  win->_curx = x;
  win->_cury = y;
  return(OK);
  } /* _chadd */

/****************************************************************/
/* Addch() inserts character 'c' at the current cursor posi-	*/
/* tion in stdscr, and takes any actions as dictated by the	*/
/* character.							*/
/****************************************************************/

int addch(c)
  char	 c;
  {
  return (_chadd(stdscr,c,TRUE));
  } /* addch */

/****************************************************************/
/* Waddch() inserts character 'c' at the current cursor posi-	*/
/* tion in window 'win', and takes any actions as dictated by	*/
/* the character.						*/
/****************************************************************/

int waddch(win,c)
  WINDOW *win;
  char	 c;
  {
  return (_chadd(win,c,TRUE));
  } /* waddch */

/****************************************************************/
/* Mvaddch() moves to position in stdscr, then inserts charac-	*/
/* ter 'c' at that point, and takes any actions as dictated by	*/
/* the character.						*/
/****************************************************************/

int mvaddch(y,x,c)
  int	 x;
  int	 y;
  char	 c;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return (_chadd(stdscr,c,TRUE));
  } /* mvaddch */

/****************************************************************/
/* Mvwaddch() moves to position in window 'win', then inserts	*/
/* character 'c' at that point in the window, and takes any	*/
/* actions as dictated by the character.			*/
/****************************************************************/

int mvwaddch(win,y,x,c)
  WINDOW *win;
  int	  x;
  int	  y;
  char	  c;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return (_chadd(win,c,TRUE));
  } /* mvwaddch */

/****************************************************************/
/* Addrawch() inserts character 'c' at the current cursor	*/
/* position in stdscr, disregarding any traditional interpre-	*/
/* tation of the character.					*/
/****************************************************************/

int addrawch(c)
  char	 c;
  {
  return (_chadd(stdscr,c,FALSE));
  } /* addrawch */

/****************************************************************/
/* Waddrawch() inserts character 'c' at the current cursor	*/
/* position in window 'win', disregarding any traditional in-	*/
/* terpretation of the character.				*/
/****************************************************************/

int waddrawch(win,c)
  WINDOW *win;
  char	 c;
  {
  return (_chadd(win,c,FALSE));
  } /* waddrawch */

/****************************************************************/
/* Mvaddrawch() moves to position in stdscr, then inserts cha-	*/
/* racter 'c' at that point, disregarding any traditional in-	*/
/* terpretation of the character.				*/
/****************************************************************/

int mvaddrawch(y,x,c)
  int	 x;
  int	 y;
  char	 c;
  {
  if (wmove(stdscr,y,x) == ERR)
    return(ERR);
  return (_chadd(stdscr,c,FALSE));
  } /* mvaddrawch */

/****************************************************************/
/* Mvwaddrawch() moves to position in window 'win', then in-	*/
/* serts character 'c' at that point in the window, disregar-	*/
/* ding any traditional interpretation of the character.	*/
/****************************************************************/

int mvwaddrawch(win,y,x,c)
  WINDOW *win;
  int	  x;
  int	  y;
  char	  c;
  {
  if (wmove(win,y,x) == ERR)
    return(ERR);
  return (_chadd(win,c,FALSE));
  } /* mvwaddrawch */
