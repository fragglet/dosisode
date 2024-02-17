#include <stdio.h>
#include <dos.h>
#include <alloc.h>
#include <mem.h>
#include <time.h>
#include "si_ip.h"
#include "errno.h"
#include "wattcp.h"

#define ATTR 0x7900
#define HI(a)	((a & 0xff00) >> 8)
#define LO(a)	(a & 0x00ff)
#define MAX_SOCK 6
#define SOCK_STREAM 1
#define SOCK_DGRAM 2
#define ntohl(x) (( (((unsigned long) x) >> 24)& 0x000000ff ) |\
                  ( (((unsigned long) x) >> 8) & 0x0000ff00 ) |\
                  ( (((unsigned long) x) << 8) & 0x00ff0000 ) |\
                  ( (((unsigned long) x) << 24)& 0xff000000 ))
#define ntohs(x) (( (((unsigned short) x) >> 8) |\
		  ( (((unsigned short) x) << 8)) & 0xffff ))
#define htonl(x) (( (((unsigned long) x) >> 24)& 0x000000ff ) |\
                  ( (((unsigned long) x) >> 8) & 0x0000ff00 ) |\
                  ( (((unsigned long) x) << 8) & 0x00ff0000 ) |\
                  ( (((unsigned long) x) << 24)& 0xff000000 ))
#define htons(x) (( (((unsigned short) x) >> 8) |\
		  ( (((unsigned short) x) << 8)) & 0xffff ))

#define FD_SET(f,l) (l |= (1<<(f)))
#define FD_CLR(f,l) (l &= ~(1<<(f)))
#define FD_ISSET(f,l) (l & (1<<(f)))
#define FD_ZERO(l) (l = 0)

/*extern unsigned _heaplen = 0x0600;
extern unsigned _stklen = 0x0200;*/

void interrupt (*oldhandler)(void);
sock_type *look_up();
sock_type *new_array();
sock_type *remove_array();

int sock_table[MAX_SOCK] = {0,0,0,0,0,0};
sock_type sock[MAX_SOCK];
char dos_buffer[4500]; /*transfer array*/
struct {
	int type;
	struct {
		unsigned non_block :1;
		unsigned is_connected :1;
		unsigned non_block_failed :1;
	} bit;
} __sock[32];
unsigned long host;
struct rsockaddr {
	int s_family;
	int s_port;
	longword s_ip;
	char zero[8];
};

static unsigned int fd;
static int total, nfds, timeout;
static long readfds,writefds,exceptfds;
static long new_readfds,new_writefds,new_exceptfds;
static time_t end;
static time_t now;
static int debug = 0;

void interrupt handler(bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags)
unsigned bp, di, si, ds, es, dx, cx, bx, ax, ip, cs, flags;
{
	static sock_type *s;
	static struct rsockaddr *q;
	static int init = 0, status;

	enable();
	switch (ax) {
	case 0x0000:
	case 0x0100:
	case 0x0200:
		_AX = ax;
		_DX = dx;
		(*oldhandler)();
	case SI_SOCKET:
if (debug) printf("socket called\n");
		if (!init) {
			sock_init();
			tcp_cbrk(0x01);
			init=1;
		}
		s = new_array(dx, cx);
		ax = (s == NULL) ? FAIL : SUCCESS;
		if (ax == FAIL) {
			cx = ENFILE;
			return;
		}
		__sock[dx].type = cx;
		cx = FP_SEG(dos_buffer);
		dx = FP_OFF(dos_buffer);
		return;
	case SI_BIND:
		return;
	case SI_CONNECT:
if (debug) printf("connect called\n");
		s = look_up(dx);
		if (s == NULL) {
			ax = FAIL;
			cx = EINVAL;
		}
		if (__sock[dx].bit.is_connected) {
			cx = EISCONN;
			ax = FAIL;
			return;
		};
		if (tcp_established(s)) {
			cx = EISCONN;
			ax = FAIL;
			return;
		}
		if (__sock[dx].bit.non_block_failed) {
			__sock[dx].bit.non_block_failed = 0;
			cx = ECONNREFUSED;
			ax = FAIL;
			return;
		}
		q = (struct rsockaddr *)dos_buffer;
		status = tcp_open(s, 0, ntohl(q->s_ip), ntohs(q->s_port),NULL);
if (debug) printf("tcp connecting to %lx %x returns %d\n",ntohl(q->s_ip),ntohs(q->s_port),status);

		if (__sock[dx].bit.non_block) {
			ip_timer_init(s, sock_delay);
			cx = EINPROGRESS;
			ax = FAIL;
			return;
		};
if (debug) printf("connect waiting\n");
		sock_wait_established(s, sock_delay, NULL, &status);
if (debug) printf("connected\n");
		__sock[dx].bit.is_connected = 1;
		ax = SUCCESS;
		return;
sock_err:
if (debug) printf("connect failed\n");
		cx = ECONNREFUSED;
		ax = FAIL;
		return;
	case SI_LISTEN:
		return;
	case SI_ACCEPT:
		return;
	case SI_RECVFROM:
if (debug) printf("recvfrom called\n");
		s = look_up(dx);
		if (__sock[dx].type == SOCK_STREAM) {
			if (!tcp_established(s)) {
				cx = EBADF;
				ax = FAIL;
				return;
			}
		}
		if (__sock[dx].bit.non_block_failed) {
			__sock[dx].bit.non_block_failed = 0;
			cx = ECONNREFUSED;
			ax = FAIL;
			return;
		}

		tcp_tick(s);
		if (__sock[dx].bit.non_block && ! sock_dataready(s)) {
			cx = EWOULDBLOCK;
			ax = FAIL;
			return;
		};
		while (! sock_dataready(s)) tcp_tick(s);
		ax = sock_fastread(s, dos_buffer+16, cx);
		memcpy(dos_buffer+2,(char *)(htons(((tcp_Socket *)s)->hisport)),2);
		memcpy(dos_buffer+4,(char *)(htonl(((tcp_Socket *)s)->hisaddr)),4);
		cx = 0;
		return;
	case SI_SENDTO:
if (debug) printf("sendto called\n");
		s = look_up(dx);
		if (__sock[dx].type == SOCK_STREAM) {
			if (!tcp_established(s)) {
				cx = EBADF;
				ax = FAIL;
				return;
			}
		}
		else {
			sock_close(s);
			q = (struct rsockaddr *)dos_buffer;
			status = udp_open(s, 0, ntohl(q->s_ip), ntohs(q->s_port),NULL);
if (debug) printf("udp connecting to %lx %x returns %d\n",ntohl(q->s_ip),ntohs(q->s_port),status);
		}
		sock_write(s,dos_buffer+16,cx);
		sock_flush(s);
		ax = cx;
		cx = 0;
		return;
	case SI_SELECT:
		nfds = dx;
		memcpy(&readfds,dos_buffer,4);
		memcpy(&writefds,dos_buffer+4,4);
		memcpy(&exceptfds,dos_buffer+8,4);
		memcpy(&timeout,dos_buffer+12,2);
		if (timeout != -1) {
			if (timeout != 0) {
				time(&now);
				end = now + timeout;
			}
			else end = 0;
		}
		else end = -1;
		total = 0;
		FD_ZERO(new_readfds);
		FD_ZERO(new_writefds);
		FD_ZERO(new_exceptfds);
		do {
			for (fd = 0; fd<MAX_SOCK; fd++) {
				s = look_up(fd);
				if (s) tcp_tick(s);
			}

			for (fd = 1; fd <nfds; fd++) {
				s = look_up(fd);
				if (FD_ISSET(fd, writefds)) {
					if (!s || (s && tcp_established(s))) {
						__sock[fd].bit.is_connected = 1;
						FD_SET(fd, new_writefds);
						total++;
					}
					if (s && !tcp_established(s)) {
						if (!s->tcp.ip_type || ip_timer_expired(s)) {
							FD_SET(fd, new_writefds);
							total++;
							sock_close(s);
							__sock[fd].bit.non_block_failed = 1;
						}
						else if (__sock[fd].bit.non_block_failed) {
							FD_SET(fd, new_writefds);
							total++;
						}
					}
				}
			}

			if (FD_ISSET(0,readfds) && kbhit()) {
				FD_SET(fd, new_readfds);
				total++;
			}
			for (fd = 3; fd <nfds; fd++) {
				if (FD_ISSET(fd, readfds)) {
					s = look_up(fd);
					if (!s || (s && unreaddata(s))) {
						__sock[fd].bit.is_connected = 1;
						FD_SET(fd, new_readfds);
						total++;
					}
					if (s && !tcp_established(s)) {
						if (!s->tcp.ip_type || ip_timer_expired(s)) {
							FD_SET(fd, new_readfds);
							total++;
							sock_close(s);
							__sock[fd].bit.non_block_failed = 1;
						}
						else if (__sock[fd].bit.non_block_failed) {
							FD_SET(fd, new_readfds);
							total++;
						}
					}
				}
			}
			if (end == 0) break;
			if (total) break;
			time(&now);
		} while (now < end);
		if (readfds) memcpy(dos_buffer,&new_readfds,4);
		if (writefds) memcpy(dos_buffer+4,&new_writefds,4);
		if (exceptfds) memcpy(dos_buffer+8,&new_exceptfds,4);
		ax = total;
if (debug) if(total) printf("select returns %d\n",total);
		return;
	case SI_IOCTL:
if (debug) printf("ioctl called\n");
		__sock[dx].bit.non_block = 1;
		return;
	case SI_CLOSE:
if (debug) printf("close called\n");
		__sock[dx].type = 0;
		__sock[dx].bit.non_block = 0;
		__sock[dx].bit.non_block_failed = 0;
		__sock[dx].bit.is_connected = 0;
		s = remove_array(dx);
		sock_close(s);
		ax = SUCCESS;
		return;
	case SI_SHUTDOWN:
if (debug) printf("shutdown called\n");
		if (init) tcp_shutdown();
		init = 0;
		break;
	case SI_CHECKLOAD:
		cx = 0x1234;
		return;
	};
}

unreaddata(s)
sock_type *s;
{

	tcp_tick(s);
	return(sock_dataready(s));
}

sock_type *look_up(dx)
int dx;
{
	int i;
	for (i=0; i<MAX_SOCK; i++) {
		if (sock_table[i] == dx) return(sock+i);
	}
	return(NULL);
}

sock_type *remove_array(dx)
int dx;
{
	int i;
	for (i=0; i<MAX_SOCK; i++) {
		if (sock_table[i] == dx) {
			sock_table[i] = 0;
			return(sock+i);
		}
	}
	return(NULL);
}

sock_type *new_array(dx, cx)
int dx, cx;
{
	int i;
	for (i=0; i<MAX_SOCK; i++) {
		if (sock_table[i] == 0) {
			sock_table[i] = dx;
			sock_close(sock+i);/*just in case*/
			return(sock+i);
		}
	}
	return(NULL);
}
int main(void)
{
	union REGS regs;

	regs.x.ax = SI_CHECKLOAD;
	int86(INTR,&regs,&regs);
	if (regs.x.cx == 0x1234) {
		fprintf(stderr,"Socket TSR is already loaded!\n");
		exit(1);
	}
	oldhandler = getvect(INTR);
	setvect(INTR, handler);
	keep(0, (_SS + (_SP/16) - _psp) + 0x10);
	return(0);
}