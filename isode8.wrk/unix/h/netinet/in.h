/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 *
 *	@(#)in.h	7.1 (Berkeley) 6/5/86
 */

/*
 * Constants and structures defined by the internet system,
 * Per RFC 790, September 1981.
 */

/*
 * Protocols
 */
#define	IPPROTO_IP		0		/* dummy for IP */
#define	IPPROTO_ICMP		1		/* control message protocol */
#define	IPPROTO_GGP		2		/* gateway^2 (deprecated) */
#define	IPPROTO_TCP		6		/* tcp */
#define	IPPROTO_EGP		8		/* exterior gateway protocol */
#define	IPPROTO_PUP		12		/* pup */
#define	IPPROTO_UDP		17		/* user datagram protocol */
#define	IPPROTO_IDP		22		/* xns idp */

#define	IPPROTO_RAW		255		/* raw IP packet */
#define	IPPROTO_MAX		256


/*
 * Ports < IPPORT_RESERVED are reserved for
 * privileged processes (e.g. root).
 * Ports > IPPORT_USERRESERVED are reserved
 * for servers, not necessarily privileged.
 */
#define	IPPORT_RESERVED		1024
#define	IPPORT_USERRESERVED	5000

/*
 * Link numbers
 */
#define	IMPLINK_IP		155
#define	IMPLINK_LOWEXPER	156
#define	IMPLINK_HIGHEXPER	158

/*
 * Internet address (a structure for historical reasons)
 */
struct in_addr {
        union  {
               struct { unsigned char s_b1,s_b2,s_b3,s_b4;} S_un_b;
               struct { unsigned short s_w1,s_w2;} S_un_w;
               unsigned long S_addr;
	} S_un;
#define   s_addr S_un.S_addr
#define   s_host S_un.S_un_b.s_b2
#define   s_net  S_un.S_un_b.s_b1
#define   s_imp  S_un.S_un_w.s_w2
#define   s_impno S_un.S_un_b.s_b4
#define   s_lh   S_un.S_un_b.s_b3
};

/*
 * Definitions of bits in internet address integers.
 * On subnets, the decomposition of addresses to host and net parts
 * is done according to subnet mask, not the masks here.
 */
#define	IN_CLASSA(i)		(((long)(i) & 0x80000000) == 0)
#define	IN_CLASSA_NET		0xff000000
#define	IN_CLASSA_NSHIFT	24
#define	IN_CLASSA_HOST		0x00ffffff
#define	IN_CLASSA_MAX		128

#define	IN_CLASSB(i)		(((long)(i) & 0xc0000000) == 0x80000000)
#define	IN_CLASSB_NET		0xffff0000
#define	IN_CLASSB_NSHIFT	16
#define	IN_CLASSB_HOST		0x0000ffff
#define	IN_CLASSB_MAX		65536

#define	IN_CLASSC(i)		(((long)(i) & 0xc0000000) == 0xc0000000)
#define	IN_CLASSC_NET		0xffffff00
#define	IN_CLASSC_NSHIFT	8
#define	IN_CLASSC_HOST		0x000000ff

#define	INADDR_ANY		(u_long)0x00000000
#define	INADDR_BROADCAST	(u_long)0xffffffff	/* must be masked */

/*
 * Socket address, internet style.
 */
struct sockaddr_in {
	short	sin_family;
	u_short	sin_port;
	struct	in_addr sin_addr;
	char	sin_zero[8];
};

/*
 * Options for use with [gs]etsockopt at the IP level.
 */
#define	IP_OPTIONS	1		/* set/get IP per-packet options */

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

#ifdef KERNEL
extern	struct domain inetdomain;
extern	struct protosw inetsw[];
struct	in_addr in_makeaddr();
u_long	in_netof(), in_lnaof();
#endif
