/* Emulation of 4.2 UNIX socket interface routines              */
#include <stdio.h>
#include <std.h>
#include <dos.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <sys/uio.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <netx25/x25_ctl.h>
#include <netx25/x25_ioctl.h>
#include <netx25/x25_pk.h>
#include "si_header.h"
#include "si_ip.h"
SOCK __sock[_NFILE];
extern int errno;
extern int si_xlate[];

static int unreaddata(int);
static int socket_close(int);
static void set_echo(void);
static void set_noecho(void);
static int udp_create(int, int);
static start_udp_read(int);
static start_passive_open(int);
static int accept_waiting(int);
static int convert_errno(int);
static void tcp_exit(void);

static int debug = 0;
static int exit_flag = 0;
static int unique = 0;
static short retval;
FILE *si_fopen();
union REGS regs;
char *dos_buffer;

union ioctl_arg {int i;struct sgttyb sg;struct ltchars t;};
static struct sgttyb def_tty = {13, 13, 0x7f, 0x18, 0000010};

/************************************************************/
/* socket routine                                           */
/************************************************************/
int socket(domain,type,protocol)
int domain,type,protocol;
{
	FILE *fp;
	int s;
	char buffer[80], *getenv();

	unique++;
if (debug) {fprintf(stderr,"socket open called\n");fflush(stderr);}
	sprintf(buffer,"%s/si_file.%03d",getenv("TMP"),unique);
	if ((fp = fopen(buffer,"w+")) == NULL) {
		fprintf(stderr,"Can't create tempfile \\tmp\\si_file!\n");
		fprintf(stderr,"Check the directory exists!\n");
		exit(1);
	}
	s = fileno(fp);

	if (! exit_flag) {
		atexit(tcp_exit);
		exit_flag = 1;
	}

	regs.x.ax = SI_CHECKLOAD;
	int86(INTR,&regs,&regs);
	if (regs.x.cx != 0x1234) {
		fprintf(stderr,"'Sockets' TSR is not loaded!\n");
		exit(1);
	}
	regs.x.ax = SI_SOCKET;
	regs.x.cx = type;
	regs.x.dx = s;
	int86(INTR,&regs,&regs);
	dos_buffer = (char *)(0xe0000000 + (regs.x.cx<<4) + regs.x.dx);
	if (regs.x.ax == FAIL) {
		close(s);
		remove(buffer);
		fprintf(stderr,"Can't allocate any more sockets %d %d!\n",regs.x.ax,FAIL);
		errno = regs.x.cx;
		return(-1);
	}
	__sock[s].unique = unique;
	__sock[s].bit.in_use = 1;
	si_xlate[s] = s;
	return(s);
}

/************************************************************/
/* bind routine                                             */
/************************************************************/
int bind(s,name,namelen)
int s;
void *name;
int namelen;
{
	struct sockaddr_in *sin;
	sin = (struct sockaddr_in *)name;

if (debug) {fprintf(stderr,"socket bind called\n");fflush(stderr);}
	bcopy((char *)name, dos_buffer,namelen);
	regs.x.ax = SI_BIND;
	regs.x.dx = si_x(s);
	int86(INTR,&regs,&regs);
	errno = regs.x.cx;
	return((retval=regs.x.ax));
}

/************************************************************/
/* connect routine                                          */
/************************************************************/
int connect(s,name,namelen)
int s;
struct sockaddr *name;
int namelen;
{
	short retval;
	struct sockaddr_in *sin;
	sin = (struct sockaddr_in *)name;

if (debug) {fprintf(stderr,"socket connect called\n");fflush(stderr);}
	regs.x.ax = SI_CONNECT;
	regs.x.dx = si_x(s);
	bcopy((char *)name, dos_buffer, namelen);
	int86(INTR,&regs,&regs);
	errno = regs.x.cx;
	return((retval=regs.x.ax));
}
/************************************************************/
/* listen routine                                           */
/************************************************************/
int listen(s,backlog)
int s;
int backlog;
{
if (debug) {fprintf(stderr,"socket listen called 1\n");fflush(stderr);}

	regs.x.ax = SI_LISTEN;
	regs.x.cx = backlog;
	regs.x.dx = si_x(s);
	int86(INTR,&regs,&regs);
	errno = regs.x.cx;
	return((retval=regs.x.ax));
}

/************************************************************/
/* accept routine                                           */
/************************************************************/
int accept(s, addr, addrlen)
int s;
struct sockaddr *addr;
int *addrlen;
{
	int news;

if (debug) {fprintf(stderr,"socket accept called\n");fflush(stderr);}
	news = dup(s);
	if (news != -1) si_xlate[news] = news; /*!*/

	regs.x.ax = SI_ACCEPT;
	regs.x.dx = s;
	regs.x.cx = news;
	int86(INTR,&regs,&regs);
	errno = regs.x.cx;
	if (regs.x.ax == FAIL) return(-1);
	if (addr != NULL) {
		*addrlen = sizeof (struct sockaddr_in);
		bcopy(dos_buffer, (char *)addr, *addrlen);
	}
	return(news);
}

/************************************************************/
/* recv routine                                             */
/************************************************************/
int recv(s, buf, len, flags)
int s;
char *buf;
int len, flags;
{
   return(recvfrom(s, buf, len, flags, NULL, NULL)); /*its just a subset*/
}

/************************************************************/
/* recvfrom routine                                         */
/************************************************************/
int recvfrom(s, buf, len, flags, from, fromlen)
int s;
char *buf;
int len, flags;
struct sockaddr *from;
int *fromlen;
{
if (debug) fprintf(stderr,"recvfrom called\n");

	regs.x.ax = SI_RECVFROM;
	regs.x.dx = si_x(s);
	regs.x.cx = len;
	int86(INTR,&regs,&regs);
	errno = regs.x.cx;
	if (regs.x.ax == FAIL) return(-1);
	bcopy(dos_buffer+16, (char *)buf, regs.x.ax);
	if (from != NULL) {
		bcopy(dos_buffer, (char *)from, sizeof (struct sockaddr));
		*fromlen = sizeof (struct sockaddr);
	}
	return((retval=regs.x.ax));
}

/************************************************************/
/* send routine                                             */
/************************************************************/
int send(s , buf, len, flags)
int s;
char *buf;
int len, flags;
{
  return(sendto(s, buf, len, flags, NULL, NULL)); /*a subset of sendto */
}

/************************************************************/
/* sendto routine                                           */
/************************************************************/
int sendto(s, buf, len, flags, to, tolen)
int s;
char *buf;
int len, flags;
struct sockaddr *to;
int tolen;
{
if (debug) fprintf(stderr,"sendo called len = %d\n",len);

	if (to != NULL) bcopy((char *)to, dos_buffer, sizeof (struct sockaddr));
	bcopy((char *)buf, dos_buffer+16, len);
	regs.x.ax = SI_SENDTO;
	regs.x.dx = si_x(s);
	regs.x.cx = len;
	int86(INTR,&regs,&regs);
if (debug) fprintf(stderr,"sendto returns %d %d\n",regs.x.ax,regs.x.cx);
	errno = regs.x.cx;
	if (regs.x.ax == FAIL) return(-1);
	bcopy(buf, dos_buffer+16, regs.x.ax);
	return((retval=regs.x.ax));
}

/************************************************************/
/* getsockname routine                                      */
/************************************************************/
int getsockname(s,name,namelen)
int s;
struct sockaddr_in *name;
int *namelen;
{

	*namelen = sizeof(*name);
	name->sin_family = AF_INET;
	name->sin_port = 0;/*xxxx*/
	return(0);
}

/************************************************************/
/* select routine                                           */
/************************************************************/
int select(nfds,readfds,writefds,exceptfds,timeout)
int nfds;
fd_set *readfds,*writefds,*exceptfds;
struct timeval *timeout;
{
	static fd_set new_readfds, new_writefds, new_exceptfds;
	int total;
	short int secs;
	int x,y,z;

	bzero(dos_buffer,32);
	if (readfds) bcopy((char *)readfds, dos_buffer, 4);
	if (writefds) bcopy((char *)writefds, dos_buffer+4, 4);
	if (exceptfds) bcopy((char *)exceptfds, dos_buffer+8, 4);
	if (timeout) secs = timeout->tv_sec;
	else secs = -1;
	bcopy((char *)&secs, dos_buffer+12, 2);

	regs.x.ax = SI_SELECT;
	regs.x.dx = nfds;
	int86(INTR,&regs,&regs);
	total = regs.x.ax;
	if (readfds) bcopy(dos_buffer, (char *)readfds, 4);
	if (writefds) bcopy(dos_buffer+4, (char *)writefds, 4);
	if (exceptfds) bcopy(dos_buffer+8, (char *)exceptfds, 4);
	bcopy(dos_buffer, (char *)&x, 4);
	bcopy(dos_buffer+4, (char *)&y, 4);
	bcopy(dos_buffer+8, (char *)&z, 4);
if (debug) {fprintf(stderr,"select returns %d r=%x w=%x e=%x\n",total,x,y,z);fflush(stderr);}
	return(total);
}

/************************************************************/
/* si_ioctl routine                                            */
/************************************************************/
si_ioctl(s,request,argp)
int s;
unsigned long request;
union ioctl_arg *argp;
{
if (debug) fprintf(stderr,"ioctl called - request=%d (FIONBIO=%d)\n",request,FIONBIO);
	if (request == SIOCSPGRP) {
		return(0);
	}
#ifdef FIONBIO
	if (request == FIONBIO) {
		regs.x.ax = SI_IOCTL;
		regs.x.dx = si_x(s);
		int86(INTR,&regs,&regs);
	}
#endif
	if (request == FIONREAD) {
		argp->i = 1; /*xxxx*/
		return(0);
	}
	if (request == TIOCGETP) {
		argp->sg.sg_ispeed = def_tty.sg_ispeed;
		argp->sg.sg_ospeed = def_tty.sg_ospeed;
		argp->sg.sg_erase = def_tty.sg_erase;
		argp->sg.sg_kill  = def_tty.sg_kill;
		argp->sg.sg_flags = def_tty.sg_flags;
		return(0);
	}
	if (request == TIOCSETP) {
		def_tty.sg_ispeed = argp->sg.sg_ispeed;
		def_tty.sg_ospeed = argp->sg.sg_ospeed;
		def_tty.sg_erase = argp->sg.sg_erase;
		def_tty.sg_kill = argp->sg.sg_kill;
		def_tty.sg_flags = argp->sg.sg_flags;
		if ( (def_tty.sg_flags & ECHO) == ECHO ) set_echo();
		else set_noecho();
		return(0);
	}
	if (request == TIOCGLTC) {
		argp->t.t_suspc = 0x19;
		argp->t.t_dsuspc = 0x19;
		argp->t.t_rprntc = 0xff;
		argp->t.t_flushc = 0xff;
		argp->t.t_werasc = 0xff;
		argp->t.t_lnextc = 0x0;
		return(0);
	}
	if (request == TIOCSLTC) {
		return(0);
	}
}
/************************************************************/
/* set_echo routine	                                        */
/************************************************************/
static void set_echo()
{
/*can't think how to do this*/
}

/************************************************************/
/* set_noecho routine	                                       */
/************************************************************/
static void set_noecho()
{
}

/************************************************************/
/* shutdown routine                                         */
/************************************************************/
shutdown(s,how)
int s,how;
{
if (debug) fprintf(stderr,"shutdown called\n");
}

/************************************************************/
/* getsockopt routine                                       */
/************************************************************/
getsockopt(s,level,optname,optval,optlen)
int s, level, optname;
char *optval;
int *optlen;
{
	return(0);
}

/************************************************************/
/* setsockopt routine                                       */
/************************************************************/
setsockopt(s,level,optname,optval,optlen)
int s, level, optname;
char *optval;
int optlen;
{
	return(0);
}

/************************************************************/
/* sigvec - must remember name of function to be called   */
/************************************************************/
sigvec(sig,vec,ovec)
int sig;
struct sigvec *vec, *ovec;
{
if (debug) fprintf(stderr,"sigvec called\n");
}

/************************************************************/
/* alarm - insert a call to our own alarm function        */
/************************************************************/
unsigned alarm(i)
unsigned i;
{
if (debug) fprintf(stderr,"alarm called\n");
}

static struct hostent my_hostent;

/************************************************************/
/* stty - obsolete form of ioctl                            */
/************************************************************/
stty(fd,buf)
int fd;
struct sgttyb *buf;
{
	return(si_ioctl(fd, TIOCSETP, (union ioctl_arg *)buf));
}

/************************************************************/
/* gtty - obsolete form of ioctl                            */
/************************************************************/
gtty(fd,buf)
int fd;
struct sgttyb *buf;
{
	return(si_ioctl(fd, TIOCGETP, (union ioctl_arg *)buf));
}

/************************************************************/
/*  si_close - new close routine			    */
/************************************************************/

si_close(s)
int s;
{
	if (__sock[s].unique) socket_close(s);
	__sock[s].unique = 0;
	__sock[s].bit.in_use = 0;
	si_xlate[s] = s;
	return(close(s));
}

/************************************************************/
/*  socket_close - close socket				    */
/************************************************************/

socket_close(s)
int s;
{
	char buffer[80];

if (debug) fprintf(stderr,"socket close called s = %d\n",s);
	close(s);
	sprintf(buffer,"%s/si_file.%03d",getenv("TMP"),__sock[s].unique);
	remove(buffer);
	regs.x.ax = SI_CLOSE;
	regs.x.dx = s;
	int86(INTR,&regs,&regs);
	errno = regs.x.cx;
	return((retval=regs.x.ax));
}
int gethostaddr()
{
}

gethostname(name, namelen)
char *name;
int namelen;
{
	strncpy(name,getenv("HOSTNAME"),namelen);
	return;
}

void tcp_exit()
{
	int s;

	for (s=0;s<_NFILE;s++) if (__sock[s].unique) si_close(s);
	regs.x.ax = SI_SHUTDOWN;
	int86(INTR,&regs,&regs);
}
