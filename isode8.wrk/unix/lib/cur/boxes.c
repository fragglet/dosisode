/****************************************************************/
/* Box() routines of the PCcurses package			*/
/*								*/
/****************************************************************/
/* This version of curses is based on ncurses, a curses version	*/
/* originally written by Pavel Curtis at Cornell University.	*/
/* I have made substantial changes to make it run on IBM PC's,	*/
/* and therefore consider myself free to make it public domain.	*/
/*		Bjorn Larsson (...mcvax!enea!infovax!bl)	*/
/****************************************************************/
/* 1.0:	Release:					870515	*/
/* 1.2:	Max limits off by 1. Fixed thanks to S. Creps:	881002	*/
/* 1.3:	MSC '-W3', Turbo'C' '-w -w-pro' checks. Support		*/
/*	for border(), wborder() functions:		881005	*/
/****************************************************************/

#include <curses.h>
#include <curspriv.h>

char _curses_boxes_rcsid[] = "@(#)boxes.c v1.3 - 881005";

/****************************************************************/
/* wbox(win,ymin,xmin,ymax,xmax,v,h) draws a box in window	*/
/* 'win', enclosing the area xmin-xmax and ymin-xmax. If	*/
/* xmax and/or ymax is 0, the window max value is used. 'v' and	*/
/* 'h' are the vertical and horizontal characters to use. If	*/
/* 'v' and 'h' are PC grapics lines, wbox will make the corners	*/
/* in a pretty way.						*/
/****************************************************************/

int	wbox(win,ymin,xmin,ymax,xmax,v,h)
  WINDOW	*win;
  int		 ymin;
  int		 xmin;
  int		 ymax;
  int		 xmax;
  char		 v;
  char		 h;
  {
  static int	 l, r, t, b, tl, tr, bl,br;	/* border chars */
  int		 i;

  if (ymax == 0)
    ymax = win->_maxy - 1;
  if (xmax == 0)
    xmax = win->_maxx - 1;

  if (ymin >= win->_maxy || ymax > win->_maxy ||
      xmin >= win->_maxx || xmax > win->_maxx ||
      ymin >= ymax || xmin >= xmax
     )
     return(ERR);

  l = r = v & 0xff;			/* get rid of sign-extended int */
  t = b = h & 0xff;
  tl = tr = bl = br = v;		/* default same as vertical */

  if (l == 0xba)			/* vertical double bars */
    {
    if (t == 0xcd)			/* horizontal too? */
      {tl=0xc9;tr=0xbb;bl=0xc8;br=0xbc;}/* use double bar corners */
    else
      {tl=0xd6;tr=0xb7;bl=0xd3;br=0xbd;}/* use hor-s vert-d corners */
    } /* if */

  if (l == 0xb3)			/* vertical single bars */
    {
    if (t == 0xcd)			
      {tl=0xd5;tr=0xb8;bl=0xd4;br=0xbe;}/* horizontal double bars */
    else				
      {tl=0xda;tr=0xbf;bl=0xc0;br=0xd9;}/* use hor-s vert-s bars */
    } /* if */
 
  if (win->_borderchars[0])		/* border() settings override parms */
    l = win->_borderchars[0];
  if (win->_borderchars[3])
    r = win->_borderchars[1];
  if (win->_borderchars[3])
    t = win->_borderchars[2];
  if (win->_borderchars[3])
    b = win->_borderchars[3];
  if (win->_borderchars[4])
    tl = win->_borderchars[4];
  if (win->_borderchars[5])
    tr = win->_borderchars[5];
  if (win->_borderchars[6])
    bl = win->_borderchars[6];
  if (win->_borderchars[7])
    br = win->_borderchars[7];

  for (i = xmin+1;i <= xmax-1;i++)
    {
    win->_line[ymin][i] = t | win->_attrs;
    win->_line[ymax][i] = b | win->_attrs;
    }
  for (i = ymin+1;i <= ymax-1;i++)
    {
    win->_line[i][xmin] = l | win->_attrs;
    win->_line[i][xmax] = r | win->_attrs;
    }
  win->_line[ymin][xmin] = tl | win->_attrs;
  win->_line[ymin][xmax] = tr | win->_attrs;
  win->_line[ymax][xmin] = bl | win->_attrs;
  win->_line[ymax][xmax] = br | win->_attrs;

  for (i=ymin; i <= ymax ; i++)
    {
    if (win->_minchng[i] == _NO_CHANGE)
      {
      win->_minchng[i] = xmin;
      win->_maxchng[i] = xmax;
      } /* if */
    else
      {
      win->_minchng[i] = min(win->_minchng[i], xmin);
      win->_maxchng[i] = max(win->_maxchng[i], xmax);
      } /* else */
    } /* for */
  return(OK);
  } /* box */

/****************************************************************/
/* box(win,v,h) draws a box around window window 'win'. 'v' and	*/
/* 'h' are the vertical and horizontal characters to use.	*/
/****************************************************************/

void	box(win,v,h)
  WINDOW	*win;
  char		 v;
  char		 h;
  {
  wbox(win,0,0,0,0,v,h);
  } /* box */
