#define MAXHOSTADR 16

#define CONN_DB struct conn_dB
CONN_DB {
	unsigned char hostlen;
	unsigned char host[8];
	unsigned char datalen;
	unsigned char data[102];
};

#define FAST_OFF		0
#define FAST_CLR_ONLY		1
#define FAST_ACPT_CLR		2
#define FACILITY_DB struct facility_dB
FACILITY_DB {
	unsigned char    reverse_charge;
        unsigned short   recvpktsize;
        unsigned short   sendpktsize;
        unsigned char    recvwndsize;
        unsigned char    sendwndsize;
        unsigned char    recvthruput;
        unsigned char    sendthruput;
        unsigned char    cug_req;
        unsigned char    cug_index;
	unsigned char    fast_select_type;
        unsigned char    rpoa_req;
        unsigned short   rpoa;
	unsigned char	stdservice;
	unsigned char	osiservice;
	unsigned char	precedence_req;
	unsigned char	precedence;
};
#define Q_BIT		3
#define D_BIT		2
#define M_BIT		0

typedef struct {
	unsigned char		datalen;
	unsigned char 		data[124];
} USER_DATA_DB;

typedef struct {
	unsigned char		masklen;
	unsigned char 		mask[16];
} MASK_DATA_DB;

typedef struct {
	unsigned char	data[16];
	unsigned char	datalen;
} CONN_DATA;

typedef struct {
	unsigned char	hostlen;
	unsigned char	host[8];
} CONN_ADR;

typedef struct {
	unsigned char	masklen;
	unsigned char 	mask[16];
} CONN_LCNCB;

#define RECV_DIAG 0
#define DIAG_TYPE 1
#define X25_CAUSE_DIAG struct x25_cause_diaG
X25_CAUSE_DIAG {
   unsigned char flags;
   unsigned char datalen;
   unsigned char data[64];
};
