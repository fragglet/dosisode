/****************************************************************/
/* Miscellaneous Terminal routines of the PCcurses package	*/
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

/* static variables or saving terminal modes */

char _curses_termmisc_rcsid[] = "@(#)termmisc.c v1.3 - 881005";

static bool savedacr;
static bool savedcbr;
static bool savedecho;
static bool savedraw;

/****************************************************************/
/* Fixterm(), resetterm(), saveoldterm, saveterm() gettmode(),	*/
/* setterm() and baudrate() function dummies for compatibility.	*/
/****************************************************************/

int fixterm()
  {
  return(OK);
  } /* fixterm */

int resetterm()
  {
  return(OK);
  }

int saveoldterm()
  {
  return(OK);
  } /* saveoldterm */

int saveterm()
  {
  return(OK);
  } /* saveterm */

int gettmode()
  {
  return(OK);
  } /* gettmode */

int setterm()
  {
  return(OK);
  } /* setterm */

int baudrate()
  {
  return(19200);
  } /* baudrate */

/****************************************************************/
/* Erasechar(), killchar() returns std MSDOS erase chars.	*/
/****************************************************************/

int erasechar()
  {
  return(_DCCHAR);		/* character delete char */
  } /* erasechar */

int killchar()
  {
  return(_DLCHAR);		/* line delete char */
  } /* killchar */

/****************************************************************/
/* Savetty() and resetty() saves and restores the terminal I/O	*/
/* settings.							*/
/****************************************************************/

int savetty()
  {
  savedacr  = _cursvar.autocr;
  savedcbr  = _cursvar.cbreak;
  savedecho = _cursvar.echo;
  savedraw  = _cursvar.raw;
  return(OK);
  } /* savetty */

int resetty()
  {
  _cursvar.autocr = savedacr;
  _cursvar.cbreak = savedcbr;
  _cursvar.echo   = savedecho;
  _cursvar.raw    = savedraw;
  return(OK);
  } /* resetty */

/****************************************************************/
/* Setupterm() sets up the terminal. On a PC, it is always suc-	*/
/* cessful, and returns 1.					*/
/****************************************************************/

int setupterm()
  {
  return(1);
  } /* setupterm */
