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

#define	INADDR_ANY 0x00000000
#define	INADDR_BROADCAST 0xffffffff
#define INADDR_LOOPBACK	0x7f000001

struct sockaddr_in {
        short  sin_family;
        unsigned short  sin_port;
        struct in_addr  sin_addr;
        char   sin_zero[8];
       };

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

#define IPPORT_RESERVED 1024
