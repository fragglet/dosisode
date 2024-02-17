#define _NFILE 32
typedef struct {
	int unique;
	struct {
		unsigned non_block :1;
		unsigned sigio :1;
		unsigned in_use :1;
	} bit;
} SOCK;
extern SOCK __sock[_NFILE];
