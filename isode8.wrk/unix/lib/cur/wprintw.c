#include <curses.h>

int wprintw(here,fmt,a,b,c,d,e,f,g,h,i,j)
WINDOW *here;
char *fmt,*a,*b,*c,*d,*e,*f,*g,*h,*i,*j;
{
	char buffer[128];
	sprintf(buffer,fmt,a,b,c,d,e,f,g,h,i,j);
	return(waddstr(here,buffer));
}
