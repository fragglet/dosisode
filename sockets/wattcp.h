#define WATTCPH

#define SOCKESTABLISHED 1
#define SOCKDATAREADY   2
#define SOCKCLOSED      4

/*
#define DEBUG
*/
/*
#define MoveW( a , b, c ) movmem( a, b,c )
#define busyouta(c) (putch(c))
*/


#include <stdio.h>
#include "elib.h"

#define set_mstimeout( x ) (set_timeout(0)+ (x / 55))

#define MAX_GATE_DATA 12
#define MAX_NAMESERVERS 10
#define MAX_COOKIES 10
#define MAX_STRING 50	/* most strings are limited */

#define MAXVJSA     1440 /* 10 s */
#define MAXVJSD     360  /* 10 s */
#define SAFETYTCP  0x538f25a3L
#define SAFETYUDP  0x3e45e154L
#define TRUE        1
#define true        TRUE
#define FALSE       0
#define false       FALSE

/* These are Ethernet protocol numbers but I use them for other things too */
#define UDP_PROTO  0x11
#define TCP_PROTO  0x06
#define ICMP_PROTO 0x01

#define TCP_MODE_BINARY  0       /* default mode */
#define TCP_MODE_ASCII   1
#define UDP_MODE_CHK     0       /* default to having checksums */
#define UDP_MODE_NOCHK   2       /* turn off checksums */
#define TCP_MODE_NAGLE   0       /* Nagle algorithm */
#define TCP_MODE_NONAGLE 4


typedef int (*procref)();

typedef unsigned long longword;     /* 32 bits */
typedef unsigned short word;        /* 16 bits */
typedef unsigned char byte;         /*  8 bits */
typedef byte eth_address[6];

/* undesirable */
extern longword MsecClock();
#define clock_ValueRough() MsecClock()

#define TICKS_SEC 18

#define checksum( p, len) inchksum( p, len )

#define PD_ETHER 1
#define PD_SLIP  6

extern word sock_inactive;      /* in pcbootp.c */
extern word _pktdevclass;
extern word _mss;
extern word _bootptimeout;	/* in pcbootp.c */
extern longword _bootphost;	/* in pcbootp.c */
extern word _bootpon;

/* The Ethernet header */
typedef struct {
    eth_address     destination;
    eth_address     source;
    word            type;
} eth_Header;

/* The Internet Header: */
typedef struct {
    unsigned	    hdrlen  : 4;
    unsigned	    ver     : 4;
    byte	    tos;
    word            length;
    word            identification;
    word            frag;
    byte	    ttl;
    byte	    proto;
    word            checksum;
    longword        source;
    longword        destination;
} in_Header;


#ifdef WATTCPH
#define in_GetVersion(ip) ( (ip)->ver )
#define in_GetHdrlen(ip)  ( (ip)->hdrlen )  /* 32 bit word size */
#define in_GetHdrlenBytes(ip)  ( in_GetHdrlen(ip) << 2 ) /* 8 bit byte size */
#define in_GetTos(ip)      ( (ip)->tos)

#define in_GetTTL(ip)      ((ip)->ttl)
#define in_GetProtocol(ip) ((ip)->proto )

#else
/*
#define in_GetVersion(ip) (((ip)->vht >> 12) & 0xf)
#define in_GetHdrlen(ip)  (((ip)->vht >> 8) & 0xf)
#define in_GetHdrlenBytes(ip)  (((ip)->vht >> 6) & 0x3c)
#define in_GetTos(ip)      ((ip)->vht & 0xff)

#define in_GetTTL(ip)      ((ip)->ttlProtocol >> 8)
#define in_GetProtocol(ip) ((ip)->ttlProtocol & 0xff)
*/
#endif WATTCPH
typedef struct {
    word	    srcPort;
    word	    dstPort;
    word	    length;
    word	    checksum;
} udp_Header;

#define UDP_LENGTH ( sizeof( udp_Header ))

typedef struct {
    word            srcPort;
    word            dstPort;
    longword        seqnum;
    longword        acknum;
    word            flags;
    word            window;
    word            checksum;
    word            urgentPointer;
} tcp_Header;

#define tcp_FlagFIN     0x0001
#define tcp_FlagSYN     0x0002
#define tcp_FlagRST     0x0004
#define tcp_FlagPUSH    0x0008
#define tcp_FlagACK     0x0010
#define tcp_FlagURG     0x0020
#define tcp_FlagDO      0xF000
#define tcp_GetDataOffset(tp) (intel16((tp)->flags) >> 12)

/* The TCP/UDP Pseudo Header */
typedef struct {
    longword    src;
    longword    dst;
    byte        mbz;
    byte        protocol;
    word        length;
    word        checksum;
} tcp_PseudoHeader;

/*
 * TCP states, from tcp manual.
 * Note: close-wait state is bypassed by automatically closing a connection
 *       when a FIN is received.  This is easy to undo.
 */
#define tcp_StateLISTEN  0      /* listening for connection */
#define tcp_StateSYNSENT 1      /* syn sent, active open */
#define tcp_StateSYNREC  2      /* syn received, synack+syn sent. */
#define tcp_StateESTAB   3      /* established */
#define tcp_StateESTCL   4      /* established, but will FIN */
#define tcp_StateFINWT1  5      /* sent FIN */
#define tcp_StateFINWT2  6      /* sent FIN, received FINACK */
#define tcp_StateCLOSWT  7      /* received FIN waiting for close */
#define tcp_StateCLOSING 8      /* sent FIN, received FIN (waiting for FINACK) */
#define tcp_StateLASTACK 9      /* fin received, finack+fin sent */
#define tcp_StateTIMEWT  10     /* dally after sending final FINACK */
#define tcp_StateCLOSEMSL 11
#define tcp_StateCLOSED  12     /* finack received */

#define tcp_MaxBufSize 2048         /* maximum bytes to buffer on input */



/*
 * UDP socket definition
 */
typedef struct _udp_socket {
    struct _udp_socket *next;
    word	    ip_type;		/* always set to UDP_PROTO */
    char	   *err_msg;		/* null when all is ok */
    void	  (*usr_yield)();
    word	    sock_mode;	        /* a logical OR of bits */
    longword	    usertimer;		/* ip_timer_set, ip_timer_timeout */
    procref	    dataHandler;
    eth_address     hisethaddr;		/* peer's ethernet address */
    longword        hisaddr;		/* peer's internet address */
    word	    hisport;		/* peer's UDP port */
    longword        myaddr;
    word	    myport;

    int             queuelen;
    byte           *queue;

    int             rdatalen;           /* must be signed */
    word            maxrdatalen;
    byte           *rdata;
    byte            rddata[ tcp_MaxBufSize + 1];         /* if dataHandler = 0, len == 512 */
    longword        safetysig;
} udp_Socket;
/*
 * TCP Socket definition
 */


typedef struct _tcp_socket {
    struct _tcp_socket *next;
    word	    ip_type;	    /* always set to TCP_PROTO */
    char 	   *err_msg;
    void	  (*usr_yield)();
    word	    sock_mode;	    /* a logical OR of bits */

    longword	    usertimer;	    /* ip_timer_set, ip_timer_timeout */
    procref         dataHandler;    /* called with incoming data */
    eth_address     hisethaddr;     /* ethernet address of peer */
    longword        hisaddr;        /* internet address of peer */
    word            hisport;	    /* tcp ports for this connection */
    longword        myaddr;
    word	    myport;

    int             queuelen;
    byte           *queue;

    int             rdatalen;       /* must be signed */
    word            maxrdatalen;
    byte           *rdata;
    byte            rddata[tcp_MaxBufSize+1];    /* received data */
    longword        safetysig;
    word	    state;          /* connection state */

    longword        acknum;
    longword	    seqnum; 	    /* data ack'd and sequence num */
    long            timeout;        /* timeout, in milliseconds */
    byte            unhappy;        /* flag, indicates retransmitting segt's */
    byte            recent;         /* 1 if recently transmitted */
    word            flags;          /* tcp flags word for last packet sent */

    word	    window;	    /* other guy's window */
    int 	    datalen;        /* number of bytes of data to send */
				    /* must be signed */
    int             unacked;        /* unacked data */

    byte	    cwindow;	    /* Van Jacobson's algorithm */
    byte	    wwindow;

    word	    vj_sa;	    /* VJ's alg, standard average */
    word	    vj_sd;	    /* VJ's alg, standard deviation */
    longword	    vj_last;	    /* last transmit time */
    word	    rto;
    byte	    karn_count;	    /* count of packets */
    byte            tos;            /* priority */
    /* retransmission timeout proceedure */
    /* these are in clock ticks */
    longword        rtt_lasttran;       /* last transmission time */
    longword        rtt_smooth;         /* smoothed round trip time */
    longword        rtt_delay;          /* delay for next transmission */
    longword        rtt_time;           /* time of next transmission */

    word            mss;
    longword        inactive_to;           /* for the inactive flag */

    byte            data[tcp_MaxBufSize+1]; /* data to send */
} tcp_Socket;

/* sock_type used for socket io */
typedef union {
    udp_Socket udp;
    tcp_Socket tcp;
} sock_type;

/* similar to UNIX */
typedef struct sockaddr {
    word        s_type;
    word        s_port;
    longword    s_ip;
    byte        s_spares[6];    /* unused in TCP realm */
};

extern longword my_ip_addr;
extern eth_address _eth_addr;
extern eth_address _eth_brdcast;
extern longword sin_mask;
extern word sock_delay;

/*
 * ARP definitions
 */
#ifdef WATTCPH
#define arp_TypeEther  0x100		/* ARP type of Ethernet address */
#else
#define arp_TypeEther  0x1		/* ARP type of Ethernet address */
#endif WATTCPH

/* harp op codes */
#ifdef WATTCPH
#define ARP_REQUEST 0x0100
#define ARP_REPLY   0x0200
#else
#define ARP_REQUEST 1
#define ARP_REPLY   2
#endif WATTCPH

/*
 * Arp header
 */
typedef struct {
    word            hwType;
    word            protType;
    word            hwProtAddrLen;  /* hw and prot addr len */
    word            opcode;
    eth_address     srcEthAddr;
    longword        srcIPAddr;
    eth_address     dstEthAddr;
    longword        dstIPAddr;
} arp_Header;

#define ETH_MSS 1400  /* MSS for Ethernet */

/*
 * Ethernet interface:
 */

void  _eth_init();
byte *_eth_formatpacket( void *eth_dest, word eth_type );
int   _eth_send( word len);
void  _eth_free( void *buf);
byte *_eth_arrived( word *type_ptr);
void  _eth_release();
void *_eth_hardware(byte *p);

void ip_timer_init();
int  ip_timer_expired();

/*
 * socket macros
 */

/*
 * sock_wait_established()
 *	- waits then aborts if timeout on s connection
 * sock_wait_input()
 *	- waits for received input on s
 *	- may not be valid input for sock_Gets... check returned length
 * sock_tick()
 *	- do tick and jump on abort
 * sock_wait_closed();
 *	- discards all received data
 *
 * jump to sock_err with contents of *statusptr set to
 *	 1 on closed
 *	-1 on timeout
 *
 */

_ip_delay0( sock_type *s, int timeoutseconds, procref fn, int *statusptr );
_ip_delay1( sock_type *s, int timeoutseconds, procref fn, int *statusptr );
_ip_delay2( sock_type *s, int timeoutseconds, procref fn, int *statusptr );

#define sock_wait_established( s, seconds, fn, statusptr ) \
    if (_ip_delay0( s, seconds, fn, statusptr )) goto sock_err;
#define sock_wait_input( s, seconds, fn , statusptr ) \
    if (_ip_delay1( s, seconds, fn, statusptr )) goto sock_err;
#define sock_tick( s, statusptr ) \
    if ( !tcp_tick(s)) { *statusptr = 1 ; goto sock_err; }
#define sock_wait_closed(s, seconds, fn, statusptr )\
    if (_ip_delay2( s, seconds, fn, statusptr )) goto sock_err;

/* in UDP_NDS.C */
longword resolve();

extern int _last_cookie;
extern longword _cookie[MAX_COOKIES];

extern char *def_domain;
extern longword def_nameservers[MAX_NAMESERVERS];
extern int _last_nameserver;
extern char *_hostname;

word isaddr( char *string );
longword aton( char *string );


int _ping( longword host , longword countnum );
longword _chk_ping( longword host , longword *ptr);
void _arp_register( longword use, longword instead_of );
_arp_resolve( longword ina, eth_address *ethap);

void * _pkt_eth_init();
pkt_release();
int pkt_send( char *buffer, int length );
pkt_buf_wipe();
pkt_buf_release( char *ptr );
void * pkt_received();



void _add_server( int *counter, int max, longword *array, longword value );
extern word debug_on;
char *rip( char *s);
_chk_socket( tcp_Socket *s );
char *inet_ntoa( char *s, longword x );
char *psocket( tcp_Socket *s );
longword inet_addr( char *s );
char *sockerr( tcp_Socket *s );
char *sockstate( tcp_Socket *s );
getpeername( tcp_Socket *s, void *dest, int *len );
getsockname(  tcp_Socket *s, void *dest, int *len );
longword gethostid();
longword sethostid( longword ip );
char *getdomainname( char *name, int length );
char *setdomainname( char *string );
word ntohs( word a );
word htons( word a );
longword ntohl( longword x );
longword htonl( longword x );
