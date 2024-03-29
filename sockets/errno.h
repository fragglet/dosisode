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

#ifndef errno_h
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#define ENOENT	 2		/* No such file or directory	*/
#define ENOTDIR  3              /* No path                      */
/*#define EMFILE	 4		/* Too many open files		*/
#define EINTR		4		/* Interrupted system call */
#define EACCES	 5		/* Permission denied		*/
#define EBADF	 6		/* Bad file number		*/
#define EARENA   7		/* Arena trashed		*/
#define ENOMEM	 8		/* Not enough core		*/
#define ESEGV    9		/* invalid memory address	*/
#define EBADENV 10		/* invalid environment		*/
#define ENODEV	15		/* No such device		*/
#define EINVAL	19		/* Invalid argument		*/
#define E2BIG	20		/* Arg list too long		*/
#define ENOEXEC 21		/* Exec format error		*/
#define EXDEV	22		/* Cross-device link		*/
#define EDOM	33		/* Math argument		*/
#define ERANGE	34		/* Result too large		*/
/*#define EEXIST	35		/* File already exists		*/
#define EEXIST	17		/* File already exists		*/

#define ENFILE		23		/* File table overflow */
#define EMFILE		24		/* Too many open files */
#define ENOTTY		25		/* Not a typewriter */
#define ETXTBSY		26		/* Text file busy */
#define EFBIG		27		/* File too large */
#define ENOSPC		28		/* No space left on device */
#define ESPIPE		29		/* Illegal seek */
#define EROFS		30		/* Read-only file system */
#define EMLINK		31		/* Too many links */
#define EPIPE		32		/* Broken pipe */

/* non-blocking and interrupt i/o */
#define EWOULDBLOCK	35		/* Operation would block */
#define EINPROGRESS	36		/* Operation now in progress */
#define EALREADY	37		/* Operation already in progress */
/* ipc/network software */

	/* argument errors */
#define ENOTSOCK	38		/* Socket operation on non-socket */
#define EDESTADDRREQ	39		/* Destination address required */
#define EMSGSIZE	40		/* Message too long */
#define EPROTOTYPE	41		/* Protocol wrong type for socket */
#define ENOPROTOOPT	42		/* Protocol not available */
#define EPROTONOSUPPORT 43		/* Protocol not supported */
#define ESOCKTNOSUPPORT 44		/* Socket type not supported */
#define EOPNOTSUPP	45		/* Operation not supported on socket */
#define EPFNOSUPPORT	46		/* Protocol family not supported */
#define EAFNOSUPPORT	47		/* Address family not supported by protocol family */
#define EADDRINUSE	48		/* Address already in use */
#define EADDRNOTAVAIL	49		/* Can't assign requested address */

	/* operational errors */
#define ENETDOWN	50		/* Network is down */
#define ENETUNREACH	51		/* Network is unreachable */
#define ENETRESET	52		/* Network dropped connection on reset */
#define ECONNABORTED	53		/* Software caused connection abort */
#define ECONNRESET	54		/* Connection reset by peer */
#define ENOBUFS		55		/* No buffer space available */
#define EISCONN		56		/* Socket is already connected */
#define ENOTCONN	57		/* Socket is not connected */
#define ESHUTDOWN	58		/* Can't send after socket shutdown */
#define ETOOMANYREFS	59		/* Too many references: can't splice */
#define ETIMEDOUT	60		/* Connection timed out */
#define ECONNREFUSED	61		/* Connection refused */

	/* */
#define ELOOP		62		/* Too many levels of symbolic links */
#define ENAMETOOLONG	63		/* File name too long */

/* should be rearranged */
#define EHOSTDOWN	64		/* Host is down */
#define EHOSTUNREACH	65		/* No route to host */
#define ENOTEMPTY	66		/* Directory not empty */

/* quotas & mush */
#define EPROCLIM	67		/* Too many processes */
#define EUSERS		68		/* Too many users */
#define EDQUOT		69		/* Disc quota exceeded */

#ifdef __cplusplus
}
#endif

#ifndef errno_h
#define errno_h 1
#endif

#endif
