#include <sys/types.h>
#include <sys/uio.h>

int writev(s,iov,iovcnt)
int s;
struct iovec *iov;
int iovcnt;
{
	int cnt, cc, i, j, bufflen, iovlen;
	char buffer[1024];
	char *ptr;

	cnt = 0; 	/* total character count */
	j = 0;	/* index into the iov entries  */
	i = 0;  bufflen = 512;
	ptr = iov[j].iov_base;
	iovlen = iov[j].iov_len;

	while (j < iovcnt) {    /* do all the iov blocks   */
		if (bufflen < iovlen) cc = bufflen;
		else  cc = iovlen;
		bcopy(ptr, buffer+i, cc);  /* copy from iov to buffer */
		ptr += cc;		/*  increment everything  */
		i += cc;
		iovlen -= cc;
		bufflen -= cc;
		if (i >= 512){    /* if buffer is full--flush   */
			cnt += si_write(s, buffer, i);
			i=0;     /* reinitialize variables  */
			bufflen = 512;
		}
		if (iovlen <= 0){  /* if iov block is done...get next one */
			j += 1;
			if (j < iovcnt){
				ptr = iov[j].iov_base;
				iovlen = iov[j].iov_len;
			}
		}
	}
	if (bufflen != 512){	/* output any partial buffer  */
		cnt += si_write(s, buffer, i);
	}
	return(cnt);	/* return total character count  */
}


