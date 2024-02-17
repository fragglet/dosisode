/****************************************************************/
/* Raw(), noraw(), echo(), noecho(), nl(), nonl(),  cbreak(),	*/
/* nocbreak(), crmode(), nocrmode() and refrbrk() routines of	*/
/* the PCcurses package.					*/
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

char _curses_setterm_rcsid[] = "@(#)setterm.c v1.3 - 881005";

/****************************************************************/
/* Raw() and noraw() sets or clears raw mode.			*/
/****************************************************************/

void  raw()
  {
  _cursvar.raw = TRUE;
  _cursesscb(FALSE);			/* disallow ^BREAK on disk I/O */
  flushinp();
  } /* raw */

void  noraw()
  {
  _cursvar.raw = FALSE;
  _cursesscb(_cursvar.orgcbr);		/* restore original ^BREAK status */
  } /* noraw */

/****************************************************************/
/* Echo() and noecho() sets or clears echo mode.		*/
/****************************************************************/

void  echo()
  {
  _cursvar.echo = TRUE;
  } /* echo */

void  noecho()
  {
  _cursvar.echo = FALSE;
  } /* noecho */

/****************************************************************/
/* Nl() and nonl() sets or clears autocr mapping mode.		*/
/****************************************************************/

void  nl()
  {
  _cursvar.autocr = TRUE;
  } /* nl */

void  nonl()
  {
  _cursvar.autocr = FALSE;
  } /* nonl */

/****************************************************************/
/* Cbreak(), nocbreak(), crmode() amd nocrmode()  sets or	*/
/* clears cbreak mode.						*/
/****************************************************************/

void  cbreak()
  {
  _cursvar.cbreak = TRUE;
  } /* cbreak */

void  nocbreak()
  {
  _cursvar.cbreak = FALSE;
  } /* nocbreak */

void  crmode()
  {
  _cursvar.cbreak = TRUE;
  } /* crmode */

void  nocrmode()
  {
  _cursvar.cbreak = FALSE;
  } /* nocrmode */

/****************************************************************/
/* Refrbrk() sets or unsets the screen refresh break flag. If	*/
/* this flag is set, and there is any input available, any	*/
/* screen refresh will be prematurely terminated, anticipating	*/
/* more screen updates. This flag is FALSE by default.		*/
/****************************************************************/

void	refrbrk(bf)
  bool	bf;
  {
  _cursvar.refrbrk = bf;
  } /* refrbrk */
