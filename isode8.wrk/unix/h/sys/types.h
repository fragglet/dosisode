/* This is file TYPES.H */
/*
** Copyright (C) 1991 DJ Delorie, 24 Kirsten Ave, Rochester NH 03867-2954
**
** This file is distributed under the terms listed in the document
** "copying.dj", available from DJ Delorie at the address above.
** A copy of "copying.dj" should accompany this file; if not, a copy
** should be available from where this file was obtained.  This file
** may not be distributed without a verbatim copy of "copying.dj".
**
** This file is distributed WITHOUT ANY WARRANTY; without even the implied
** warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*/

#ifndef _TYPES_H_
#define _TYPES_H_

typedef unsigned long time_t;
typedef unsigned char u_char;
typedef unsigned int u_int;
typedef unsigned long u_long;
typedef	unsigned short	u_short;
typedef	unsigned short	ushort;		/* sys III compat */
typedef long off_t;
typedef char *caddr_t;

typedef	struct	_quad { long val[2]; } quad;
typedef	long	daddr_t;
typedef	u_short	ino_t;
typedef	long	swblk_t;
#ifndef __TIME__
#include <time.h>
#endif __TIME__
typedef	char	*dev_t;
typedef	u_short	uid_t;
typedef	u_short	gid_t;

#define	NBBY	8		/* number of bits in a byte */

typedef	struct	fd_set { int fds_bits[1]; } fd_set; /*pkay*/
typedef long    fd_mask;
#define NFDBITS (sizeof (fd_mask) * NBBY)       /* bits per mask */

#define FD_SETSIZE          (sizeof (fd_set) * 8)

#define FD_SET(f,s)         ((s)->fds_bits[0] |= (1 << (f)))
#define FD_CLR(f,s)         ((s)->fds_bits[0] &= ~(1 << (f)))
#define FD_ISSET(f,s)       ((s)->fds_bits[0] & (1 << (f)))
#define FD_ZERO(s)          ((s)->fds_bits[0] = 0)

#endif
