/****************************************************************/
/* Newwin(), subwin() routines of the PCcurses package		*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.1:	Fix in subwin: '+/-1' error when checking that		*/
/*	subwindow fits in parent window:		880305	*/
/* 1.2:	Other max limits off by 1. Fixed thanks to		*/
/*	S. Creps:					881002	*/
/* 1.3:	MSC '-W3', Turbo'C' '-w -w-pro' checks. Support		*/
/*	for border(), wborder() functions:		881005	*/
/****************************************************************/

#include <stdio.h>
#include <curses.h>
#include <curspriv.h>

char _curses_newwin_rcsid[] = "@(#)newwin.c v1.3 - 881005";

/****************************************************************/
/* Makenew() allocates all data for a new window except the	*/
/* actual lines themselves.					*/
/****************************************************************/

static WINDOW *makenew(num_lines, num_columns, begy, begx)
  int	num_lines, num_columns, begy, begx;
  {
  int		 i;
  WINDOW	*win;

  /* allocate the window structure itself */

  if ((win = (WINDOW *) malloc(sizeof(WINDOW))) == NULL)
    return ((WINDOW *) ERR);

  /* allocate the line pointer array */

  if ((win->_line = (int **) calloc(num_lines, sizeof (int *))) == NULL)
    {
    free(win);
    return((WINDOW *) ERR);
    }

  /* allocate the minchng and maxchng arrays */

  if ((win->_minchng = (int *) calloc(num_lines, sizeof(int))) == NULL)
    {
    free(win);
    free(win->_line);
    return((WINDOW *) ERR);
    }
  if ((win->_maxchng = (int *) calloc(num_lines, sizeof(int))) == NULL)
    {
    free(win);
    free(win->_line);
    free(win->_minchng);
    return((WINDOW *) ERR);
    }

  /* initialize window variables */

  win->_curx      = 0;
  win->_cury      = 0;
  win->_maxy      = num_lines;
  win->_maxx      = num_columns;
  win->_begy      = begy;
  win->_begx      = begx;
  win->_flags     = 0;
  win->_attrs     = ATR_NRM;
  win->_tabsize   = 8;
  win->_clear     = (bool) ((num_lines == LINES) && (num_columns == COLS));
  win->_leave     = FALSE;
  win->_scroll    = FALSE;
  win->_nodelay   = FALSE;
  win->_keypad    = FALSE;
  win->_regtop    = 0;
  win->_regbottom = num_lines - 1;

  for (i = 0; i < 8; i++)
    win->_borderchars[i] = '\0';

  /* init to say window unchanged */

  for (i = 0; i < num_lines; i++)
    {
    win->_minchng[i] = 0;
    win->_maxchng[i] = num_columns-1;
    }

  /* set flags for window properties */

  if ((begy + num_lines) == LINES)
    {
    win->_flags |= _ENDLINE;
    if ((begx == 0) && (num_columns == COLS) && (begy == 0))
      win->_flags |= _FULLWIN;
    } /* if */

  if (((begy + num_lines) == LINES)
        &&
      ((begx + num_columns) == COLS))
    win->_flags |= _SCROLLWIN;
  return(win);
  } /* makenew */

/****************************************************************/
/* Newwin() creates a new window with size num_lines * num_co-	*/
/* lumns, and origin begx,begy relative to the SCREEN. Special	*/
/* case: if num_lines and/or num_columns is 0, the remainder of	*/
/* the screen is used.						*/
/****************************************************************/

WINDOW *newwin(num_lines, num_columns, begy, begx)
  int	num_lines, num_columns, begy, begx;
  {
  WINDOW	*win;
  int		*ptr;
  int		 i, j;

  if (num_lines == 0)
    num_lines = LINES - begy;
  if (num_columns == 0)
    num_columns = COLS - begx;
  if ((win = makenew(num_lines, num_columns, begy, begx)) == (WINDOW *) ERR)
    return((WINDOW *) ERR);
  for (i = 0; i < num_lines; i++)	/* make and clear the lines */
    {
    if((win->_line[i] = (int *) calloc(num_columns,sizeof(int))) == NULL)
      {
      for (j = 0; j < i; j++)		/* if error, free all the data */
	free(win->_line[j]);
      free(win->_minchng);
      free(win->_maxchng);
      free(win->_line);
      free(win);
      return((WINDOW *) ERR);
      } /* if */
    else
      for (ptr = win->_line[i]; ptr < win->_line[i] + num_columns;)
	*ptr++ = ' ' | ATR_NRM;
    } /* for */
  return(win);
  } /* newwin */

/****************************************************************/
/* Subwin() creates a sub-window in the 'orig' window, with	*/
/* size num_lines * num_columns, and with origin begx, begy	*/
/* relative to the SCREEN. Special case: if num_lines and/or	*/
/* num_columns is 0, the remainder of the original window is	*/
/* used. The subwindow uses the original window's line buffers	*/
/* to store its own lines.					*/
/****************************************************************/

WINDOW *subwin(orig, num_lines, num_columns, begy, begx)
  WINDOW	*orig;
  int		 num_lines, num_columns, begy, begx;
  {
  WINDOW	*win;
  int		 i, j, k;

  /* make sure window fits inside the original one */

  if (
      begy < orig->_begy || 
      begx < orig->_begx ||
      (begy + num_lines) >= (orig->_begy + orig->_maxy) ||
      (begx + num_columns) >= (orig->_begx + orig->_maxx)
     )
    return((WINDOW *) ERR);

  if (num_lines == 0)
    num_lines = orig->_maxy - 1 - (begy - orig->_begy);
  if (num_columns == 0)
    num_columns = orig->_maxx - 1 - (begx - orig->_begx);
  if ((win = makenew(num_lines, num_columns, begy, begx)) == (WINDOW *) ERR)
    return((WINDOW *) ERR);

  /* set line pointers the same as in the original window */

  j = begy - orig->_begy;
  k = begx - orig->_begx;
  for (i = 0; i < num_lines; i++)
    win->_line[i] = (orig->_line[j++]) + k;
  win->_flags |= _SUBWIN;
  return(win);
  } /* subwin */
