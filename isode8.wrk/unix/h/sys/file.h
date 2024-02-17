#define L_SET 0
#define L_INCR 1
#define L_XTND 2
#define LOCK_SH 1
#define LOCK_EX 2
#define LOCK_NB 4
#define LOCK_UN 8
/*sys/fcntl.h*/
#define R_OK 4
#define W_OK 2
#define X_OK 1
#define F_OK 0
#define FNDELAY 00004
#define FASYNC  00100
#define F_GETFL 3
#define F_SETFL 4
/*fcntl.h*/
#ifndef __FCNTL__
#define __FCNTL__
# define F_OPEN 		(('d'<<8)|00)		/* 'd' => "directory" ops */
# define F_DELETE		(('d'<<8)|01)
# define F_RENAME		(('d'<<8)|02)

# define F_GTABINFO 	(('e'<<8)|00)		/* 'e' => "editor" ops */	
# define F_STABINFO 	(('e'<<8)|01)
# define F_GFONTINFO	(('e'<<8)|02)
# define F_SFONTINFO	(('e'<<8)|03)
# define F_GPRINTREC	(('e'<<8)|04)
# define F_SPRINTREC	(('e'<<8)|05)
# define F_GSELINFO 	(('e'<<8)|06)
# define F_SSELINFO 	(('e'<<8)|07)
# define F_GWININFO 	(('e'<<8)|08)
# define F_SWININFO 	(('e'<<8)|09)

/*
# define O_RDONLY	  0 
# define O_WRONLY	  1
# define O_RDWR 	  2
# define O_APPEND	(1<<3)
# define O_RSRC 	(1<<4)
# define O_CREAT	(1<<8)
# define O_TRUNC	(1<<9)
# define O_EXCL 	(1<<10)
# define O_BINARY	(1<<11)
# define O_USEP 	(1<<12)
# define O_TMP 		(1<<13)
*/

#define O_RDONLY	0x0001
#define	O_WRONLY	0x0002
#define	O_RDWR		0x0004
#define	O_CREAT		0x0100
#define	O_TRUNC		0x0200
#define O_EXCL		0x0400
#define O_APPEND	0x0800
#define O_TEXT		0x4000
#define O_BINARY	0x8000

extern int _fmode;

int faccess(char*, unsigned int, long*);
int open(const char*, int, ...), close(int);
long lseek(int, long, int); 

# define F_DUPFD 0
#endif __FCNTL__
