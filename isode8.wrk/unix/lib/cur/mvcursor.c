/****************************************************************/
/* Mvcur() routine of the PCcurses package			*/
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

char _curses_mvcursor_rcsid[] = "@(#)mvcursor.c v1.3 - 881005";

/****************************************************************/
/* Mvcur(oldy,oldx,newy,newx) the display cursor to <newy,newx>	*/
/****************************************************************/

int	mvcur(oldy,oldx,newy,newx)
  int oldy;
  int oldx;
  int newy;
  int newx;
  {
  if ((newy >= LINES) || (newx >= COLS) || (newy < 0) || (newx < 0))
    return(ERR);
  _cursescursor(newy,newx);
  _cursvar.cursrow = newy;
  _cursvar.curscol = newx;
  return(OK);
  } /* mvcur */
