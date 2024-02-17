/****************************************************************/
/* Longname() routine of the PCcurses package			*/
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

char _curses_longname_rcsid[] = "@(#)longname.c v1.3 - 881005";

/****************************************************************/
/* Longname() returns a pointer to a string describing the	*/
/* user terminal.						*/
/****************************************************************/

char *longname()
  {
  return("IBM PC BIOS");
  }/* longname */
