/****************************************************************/
/* Doupdate() routine of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Changed call sequence to cursesio.[c,asm], Thanks	*/
/*	to S. Creps. Rcsid[] string for maintenance:	881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

static void clrupdate();		/* fwd declaration */
static bool transformline();
static void clearscreen();
static void gotoxy();
static void Putchar();

char _curses_update_rcsid[] = "@(#)update.c v1.3 - 881005";

static WINDOW	*twin;			/* used by many routines */

static	char	 atrtab[64] =		/* attribute encoding table. */
  {					/* feel free to edit if your */
  (char)7,	/* NORMAL (0) */	/* display board supports all */
  (char)0x87,	/* BLINK */		/* possible combinations */
  (char)0,	/* BLANK */
  (char)0,	/* BLINK & BLANK */
  (char)0xf,	/* BOLD */
  (char)0x8f,	/* BOLD & BLINK */
  (char)0,	/* BOLD & BLANK */
  (char)0,	/* BOLD & BLINK & BLANK */
  (char)0x70,	/* REVERSE (8) */
  (char)0xf0,	/* REVERSE & BLINK */
  (char)0,	/* REVERSE & BLANK */
  (char)0,	/* REVERSE & BLINK & BLANK */
  (char)0x78,	/* REVERSE & BOLD */
  (char)0xf8,	/* REVERSE & BOLD & BLINK */
  (char)0,	/* REVERSE & BOLD & BLANK */
  (char)0,	/* REVERSE & BOLD & BLINK & BLANK */
  (char)0xf,	/* STANDOUT (10) */
  (char)0x8f,	/* STANDOUT & BLINK */
  (char)0,	/* STANDOUT & BLANK */
  (char)0,	/* STANDOUT & BLINK & BLANK */
  (char)0xf,	/* STANDOUT & BOLD */
  (char)0x8f,	/* STANDOUT & BOLD & BLINK */
  (char)0,	/* STANDOUT & BOLD & BLANK */
  (char)0,	/* STANDOUT & BOLD & BLINK & BLANK */
  (char)0x70,	/* STANDOUT & REVERSE (18) */
  (char)0xf0,	/* STANDOUT & REVERSE & BLINK */
  (char)0,	/* STANDOUT & REVERSE & BLANK */
  (char)0,	/* STANDOUT & REVERSE & BLINK & BLANK */
  (char)0x70,	/* STANDOUT & REVERSE & BOLD */
  (char)0xf0,	/* STANDOUT & REVERSE & BOLD & BLINK */
  (char)0,	/* STANDOUT & REVERSE & BOLD & BLANK */
  (char)0,	/* STANDOUT & REVERSE & BOLD & BLINK & BLANK */
  (char)1,	/* UNDERLINE (20) */
  (char)0x81,	/* UNDERLINE & BLINK */
  (char)0,	/* UNDERLINE & BLANK */
  (char)0,	/* UNDERLINE & BLINK & BLANK */
  (char)9,	/* UNDERLINE & BOLD */
  (char)0x89,	/* UNDERLINE & BOLD & BLINK */
  (char)0,	/* UNDERLINE & BOLD & BLANK */
  (char)0,	/* UNDERLINE & BOLD & BLINK & BLANK */
  (char)0x70,	/* UNDERLINE & REVERSE (28) */
  (char)0xf0,	/* UNDERLINE & REVERSE & BLINK */
  (char)0,	/* UNDERLINE & REVERSE & BLANK */
  (char)0,	/* UNDERLINE & REVERSE & BLINK & BLANK */
  (char)0x79,	/* UNDERLINE & REVERSE & BOLD */
  (char)0xf9,	/* UNDERLINE & REVERSE & BOLD & BLINK */
  (char)0,	/* UNDERLINE & REVERSE & BOLD & BLANK */
  (char)0,	/* UNDERLINE & REVERSE & BOLD & BLINK & BLANK */
  (char)9,	/* UNDERLINE & STANDOUT (30) */
  (char)0x89,	/* UNDERLINE & STANDOUT & BLINK */
  (char)0,	/* UNDERLINE & STANDOUT & BLANK */
  (char)0,	/* UNDERLINE & STANDOUT & BLINK & BLANK */
  (char)9,	/* UNDERLINE & STANDOUT & BOLD */
  (char)0x89,	/* UNDERLINE & STANDOUT & BOLD & BLINK */
  (char)0,	/* UNDERLINE & STANDOUT & BOLD & BLANK */
  (char)0,	/* UNDERLINE & STANDOUT & BOLD & BLINK & BLANK */
  (char)0x70,	/* UNDERLINE & STANDOUT & REVERSE (38) */
  (char)0xf0,	/* UNDERLINE & STANDOUT & REVERSE & BLINK */
  (char)0,	/* UNDERLINE & STANDOUT & REVERSE & BLANK */
  (char)0,	/* UNDERLINE & STANDOUT & REVERSE & BLINK & BLANK */
  (char)0x70,	/* UNDERLINE & STANDOUT & REVERSE & BOLD */
  (char)0xf0,	/* UNDERLINE & STANDOUT & REVERSE & BOLD & BLINK */
  (char)0,	/* UNDERLINE & STANDOUT & REVERSE & BOLD & BLANK */
  (char)0,	/* UNDERLINE & STANDOUT & REVERSE & BOLD & BLINK & BLANK */
  };

/****************************************************************/
/* Doupdate() updates the physical screen to look like _curs-   */
/* var.tmpwin if curscr is not 'Clear-marked'. Otherwise it	*/
/* updates the screen to look like curscr.			*/
/****************************************************************/

void doupdate()
  {
  register int		 i;

  twin   = _cursvar.tmpwin;
  if (curscr->_clear)
    clrupdate(curscr);
  else
    {
    if (twin->_clear)
      clrupdate(twin);
    else
      {
      for (i=0; i < LINES; i++)
	if (twin->_minchng[i] != _NO_CHANGE)
	  if (transformline(i))
	    break;
      } /* else */
    } /* else */
  curscr->_curx = twin->_curx;
  curscr->_cury = twin->_cury;
  gotoxy(curscr->_cury, curscr->_curx);
  } /* doupdate */

/****************************************************************/
/* Clrupdate(scr) updates the screen by clearing it and then	*/
/* redraw it in its entirety. If _cursvar.refrbrk is TRUE, and	*/
/* there is pending input characters, the update will be pre-	*/
/* maturely terminated.						*/
/****************************************************************/

static void clrupdate(scr)
  WINDOW	*scr;
  {
  register int		*src;
  register int		*dst;
  register int		 i;
  register int		 j;
  static   WINDOW	*w;

  w = curscr;
  
  if (scr != w)				/* copy scr to curscr */
    {
    for (i=0; i < LINES; i++)
      {
      src = scr->_line[i];
      dst = w->_line[i];
      for (j=0; j < COLS; j++)
	*dst++ = *src++;
      } /* for */
    } /* if */
  clearscreen();			/* clear physical screen */
  scr->_clear = FALSE;
  for (i=0; i < LINES; i++)		/* update physical screen */
    {
    src = w->_line[i];
    for(j=0; j < COLS; j++)
      {
      if (*src != (' ' | ATR_NRM))
	{
	gotoxy(i,j);
	Putchar(*src);
	} /* if */
      src++;
      } /* for */
    if(_cursvar.refrbrk && _cursespendch())
      return;
    } /* for */
  } /* clrupdate */

/****************************************************************/
/* Transformline() updates the given physical line to look	*/
/* like the corresponding line in _cursvar.tmpwin. Transform-	*/
/* returns 1 if premature refresh end is allowed, and there is	*/
/* an input character pending.					*/
/****************************************************************/

static bool transformline(lineno)
  register int	lineno;
  {
  register int		*dstp;
  register int		*srcp;
  static   int		 x;
  static   int		 endx;

  x    = twin->_minchng[lineno];
  endx = twin->_maxchng[lineno];
  dstp = curscr->_line[lineno] + x;
  srcp = twin->_line[lineno] + x;
  
  for( ; x <= endx; x++)
    {
    if(*dstp != *srcp)
      {
      gotoxy(lineno,x);
      Putchar(*srcp);
      } /* if */
    *dstp++ = *srcp++;
    } /* for */
  twin->_minchng[lineno] = _NO_CHANGE;
  twin->_maxchng[lineno] = _NO_CHANGE;
  return ((bool)(_cursvar.refrbrk && _cursespendch()));
  } /* transformline */

/****************************************************************/
/* Clearscreen() clears the physical screen and puts the cursor	*/
/* in the home position.					*/
/****************************************************************/

static void clearscreen()
  {
  _cursesscroll(0,0,LINES-1,COLS-1,0,atrtab[0]);
  gotoxy(0,0);
  } /* clearscreen */

/****************************************************************/
/* Gotoxy() moves the physical cursor to the desired address on	*/
/* the screen. We don't optimize here - on a PC, it takes more	*/
/* time to optimize than to do things directly.			*/
/****************************************************************/

static void gotoxy(row,col)
  int row, col;
  {
  if((_cursvar.cursrow == row) && (_cursvar.curscol == col))
    return;
  _cursescursor(row,col);
  _cursvar.cursrow = row;
  _cursvar.curscol = col;
  } /* gotoxy */

/****************************************************************/
/* Putchar() writes a character, with attributes, to the physi-	*/
/* cal screen, but avoids writing to the lower right screen	*/
/* position.							*/
/****************************************************************/

static void Putchar(ch)
  int ch;
  {
  if ((_cursvar.cursrow < LINES) || (_cursvar.curscol < COLS))
    _cursescattr(ch,atrtab[(ch >> 8) & 0x3f],1);
  } /* Putchar */
