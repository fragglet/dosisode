/****************************************************************/
/* Idlok(), clearok(), leaveok(), scrollok(), nodelay(), key-	*/
/* pad(), meta(), cursoff() and curson() routines of the	*/
/* PCcurses package.						*/
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

char _curses_options_rcsid[] = "@(#)option.c v1.3 - 881005";

static bool	hasold = FALSE;		/* for remembering old cursor type */
static int	oldmode;

/****************************************************************/
/* Idlok() is used to set  flag for using the terminal insert/	*/
/* delete line capabilities. This is not relevant for the PC	*/
/* version of curses, and thus nothing is done.			*/
/****************************************************************/

void idlok()
  {
  } /* idlok */

/****************************************************************/
/* Clearok() marks window 'win' to cause screen clearing and	*/
/* redraw the next time a refresh is done.			*/
/****************************************************************/

void clearok(win, flag)
  WINDOW	*win;
  bool		 flag;
  {
  if (win == curscr)
    _cursvar.tmpwin->_clear = flag;
  else
    win->_clear = flag;
  } /* clearok */

/****************************************************************/
/* Leaveok() marks window 'win' to allow the update routines	*/
/* to leave the hardware cursor where it happens to be at the	*/
/* end of update. Usually used in combination with cursoff().	*/
/****************************************************************/

void leaveok(win, flag)
  WINDOW	*win;
  bool		 flag;
  {
  win->_leave = flag;
  } /* leaveok */

/****************************************************************/
/* Scrollok() marks window 'win' to allow the scrolling region	*/
/* of it to actually scroll.					*/
/****************************************************************/

void scrollok(win, flag)
  WINDOW	*win;
  bool		 flag;
  {
  win->_scroll = flag;
  } /* scrollok */

/****************************************************************/
/* Nodelay() marks the window to make character input non-	*/
/* waiting, i.e. if there is no character to get, -1 will be	*/
/* returned.							*/
/****************************************************************/

void nodelay(win, flag)
  WINDOW	*win;
  bool		 flag;
  {
  win->_nodelay = flag;
  } /* nodelay */

/****************************************************************/
/* Keypad() marks window 'win' to use the special keypad mode.	*/
/****************************************************************/

void keypad(win, flag)
  WINDOW	*win;
  bool		 flag;
  {
  win->_keypad = flag;
  } /* keypad */

/****************************************************************/
/* Meta() allows use of any alternate character set allowed by	*/
/* the terminal. We always allow this on the PC, so this one	*/
/* does nothing.						*/
/****************************************************************/

void meta()
  {
  } /* meta */

/****************************************************************/
/* Cursoff() turns off the hardware cursor.			*/
/****************************************************************/

void cursoff()
  {
  if (!hasold)
    {
    oldmode = _cursesgcmode();		/* get old cursor type */
    hasold = TRUE;
    }
  _cursescmode(31,30);			/* turn it off */
  } /* cursoff */

/****************************************************************/
/* Curson() turns on the hardware cursor.			*/
/****************************************************************/

void curson()
  {
  if (hasold)
    {
    _cursescmode(oldmode >> 8,oldmode);
    hasold = FALSE;
    }
  } /* curson */
