/****************************************************************/
/* Unctrl() routines of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/*		     IMPLEMENTATION NOTE			*/
/* The conversion from a control character to a two-character	*/
/* sequence is done by the unctrl() function. In the BSD ver-	*/
/* sion of curses it is done by a macro, which uses a publi-	*/
/* cally available translation table. Some ill-behaved appli-	*/
/* cation programs use the table directly, and since it does	*/
/* not exist in this curses version such application will link	*/
/* with an error message complainting about undefined symbols.	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Rcsid[] string for maintenance:			881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

static char	strbuf[3] = {0,0,0};

char _curses_unctrl_rcsid[] = "@(#)unctrl.c v1.3 - 881005";

/****************************************************************/
/* Unctrl() returns a char pointer to a string corresponding to	*/
/* argument character 'c'.					*/
/****************************************************************/

char *unctrl(c)
  char c;
  {
  int ic = c;
  ic &= 0xff;
  
  if ((ic >= ' ') && (ic != 0x7f))		/* normal characters */
    {
    strbuf[0] = (char) ic;
    strbuf[1] = '\0';
    return(strbuf);
    } /* if */
  strbuf[0] = '^';				/* '^' prefix */
  if (c == 0x7f)				/* DEL */
    strbuf[1] = '?';
  else						/* other control */
    strbuf[1] = ((char) ic) + '@';
  return(strbuf);
  } /* unctrl */
