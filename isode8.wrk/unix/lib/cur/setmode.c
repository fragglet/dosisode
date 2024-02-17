/****************************************************************/
/* Terminal mode routines of the PCcurses package.		*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* BUT: this particular module was written by			*/
/*	N. Dean Pentcheff  (dean@violet.berkeley.edu)		*/
/* It provides PC Curses versions of:				*/
/*	reset_prog_mode();					*/
/*	reset_shell_mode();					*/
/*	set_prog_mode();					*/
/*	set_shell_mode();					*/
/*								*/
/* B. Larsson took the liberty to modify its style slightly	*/
/* when incorporating it into PCcurses v.1.2. The routines in	*/
/* this module do a similar thing to savetty() and resetty().	*/
/****************************************************************/
/* 1.2:	Style clean-up, rcsid[] string for maintenance:	881002	*/
/* 1.3:	MSC -W3, Turbo'C' -w -w-pro checkes:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

struct cttyset
  {
  bool	been_set;
  bool	oautocr;
  bool	ocbreak;
  bool	oecho;
  bool	oraw;
  };
	
char _curses_setmode_rcsid[] = "@(#)setmode.c v1.3 - 881005";

static	struct cttyset sh_tty = {FALSE};/* tty modes for shell_mode */
static	struct cttyset pr_tty = {FALSE};/* tty modes for prog_mode  */

/****************************************************************/
/* Def_prog_mode() saves the current tty status, to be recalled	*/
/* later by reset_prog_mode.					*/
/****************************************************************/

void def_prog_mode()
  {
  pr_tty.been_set = TRUE;
  pr_tty.oautocr = _cursvar.autocr;
  pr_tty.ocbreak = _cursvar.cbreak;
  pr_tty.oecho	= _cursvar.echo;
  pr_tty.oraw	= _cursvar.raw;
  } /* def_prog_mode */

/****************************************************************/
/* Reset_prog_mode() resets tty modes to the values saved in a	*/
/* call to def_prog_mode.					*/
/****************************************************************/

void reset_prog_mode()
  {
  if (pr_tty.been_set == TRUE)
    {
    _cursvar.autocr	= pr_tty.oautocr;
    _cursvar.cbreak	= pr_tty.ocbreak;
    _cursvar.echo	= pr_tty.oecho;
    _cursvar.raw	= pr_tty.oraw;
    } /* if */
  } /* reset_prog_mode */

/****************************************************************/
/* Def_shell_mode() saves the tty status, to be recalled by	*/
/* reset_shell_mode. A noop in PCcurses.			*/
/****************************************************************/

void def_shell_mode()
  {
  } /* def_shell_mode */

/****************************************************************/
/* Reset_shell_mode() resets the tty status to the status it	*/
/* had before curses began.					*/
/****************************************************************/

void reset_shell_mode()
  {
  _cursvar.autocr	= TRUE;
  _cursvar.cbreak	= FALSE;
  _cursvar.echo	= TRUE;
  _cursvar.raw	= FALSE;
  } /* reset_shell_mode */
