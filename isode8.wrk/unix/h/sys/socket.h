#define	SOCK_STREAM	1
#define	SOCK_DGRAM	2

#define	SO_DEBUG	0x01
#define	SO_ACCEPTCONN	0x02
#define	SO_REUSEADDR	0x04
#define	SO_KEEPALIVE	0x08
#define	SO_LINGER	0x80
#define	SO_DONTLINGER	(~SO_LINGER)

#define	AF_UNSPEC	0
#define AF_ERROR	0
#define	AF_INET		2
#define	AF_CCITT	10
#define AF_X25		10

struct sockaddr {
   unsigned short sa_family;
   char           sa_data[14];
};

#define	SOL_SOCKET	0xffff

#define	MSG_OOB	1
#define	MSG_PEEK 2
