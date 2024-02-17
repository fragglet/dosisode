#define _IO(x,y)     (0x20000000|('x'<<8)|y)
#define _IOR(x,y,t)  (0x40000000|((sizeof(t)&0x7f)<<16)|('x'<<8)|y)
#define _IOW(x,y,t)  (0x80000000|((sizeof(t)&0x7f)<<16)|('x'<<8)|y)
#define _IOWR(x,y,t) (0xc0000000|((sizeof(t)&0x7f)<<16)|('x'<<8)|y)
#define SIOCSPGRP _IOW(s,8,int)
#define TIOCGETP _IOR(t,8,struct sgttyb)
#define TIOCSETP _IOW(t,9,struct sgttyb)
#define TIOCGLTC _IOR(t,116,struct ltchars)
#define TIOCSLTC _IOW(t,117,struct ltchars)
#define TIOCNOTTY _IO(t,113)
#define FIONREAD _IOR(f,127,int)
#define FIONBIO  _IOW(f,126,int)
#ifndef _SGTTYB_
#define _SGTTYB_
struct sgttyb {
  char sg_ispeed;
  char sg_ospeed;
  char sg_erase;
  char sg_kill;
  char sg_flags;
};
struct ltchars {
        char t_suspc;
        char t_dsuspc;
        char t_rprntc;
        char t_flushc;
        char t_werasc;
        char t_lnextc;
};
#endif
#define CBREAK 0x00000002
#define LCASE 0x00000004
#define ECHO 0x00000008
#define CRMOD 0x00000010
#define RAW 0x00000020
