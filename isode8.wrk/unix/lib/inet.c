#include <stdio.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <ctype.h>

unsigned long inet_addr(cp)
char *cp;
{
  int i,j,ti[4];
  unsigned long k;
  char *q;
  char s[10];

  q = cp;
  j = 0;
  while (!isspace(*q) && *q != '\0') {
    if (*q == '.') q++;
    i = 0;
    while ((*q >= '0') && (*q <= '9')) {
      s[i++] = *q;
      q++;
    }
    if ((*q != '.') && (*q != '\0') && !isspace(*q)) return(0xffffffff);
    s[i] = '\0';
    if (j > 3) return(0xffffffff);
    ti[j++] = atoi(s);
  }
  switch (j) {
  case 1:
    k = ti[0];
    break;
  case 2:
    k = (ti[0] * 0x01000000) + ti[1];
    break;
  case 3:
    k = (ti[0] * 0x01000000) + (ti[1] * 0x00010000) + ti[2];
    break;
  case 4:
    k = (ti[0] * 0x01000000) + (ti[1] * 0x00010000) + (ti[2] * 0x00000100) + ti[3];
    break;
  }
  k = htonl(k);
  return(k);
}

char *inet_ntoa(in)
struct in_addr in;
{
   char *s;
   unsigned char *p;

   p = (unsigned char *)&in;
   s = (char *)malloc(16);
/*   sprintf(s,"%d.%d.%d.%d",in.s_net,in.s_host,in.s_lh,in.s_impno);*/
   sprintf(s,"%d.%d.%d.%d",p[0],p[1],p[2],p[3]);
   return(s);
}
inet_network(name)
  char *name;
{
  long bytes[4];
  int byte_ctr = -1;
  int i;
  int state = 0;  /* init bytes jobber */
  int base;
  unsigned long value;

  while (*name != '\0') {
    if (state == 0) { /* at beginning of byte */
      byte_ctr++;
      if (byte_ctr > 4)
         return (-1);
      bytes[byte_ctr] = 0;
      if (*name == '0') {
         base = 8;
	 name++;
      }
      if ((*name == 'x') || (*name == 'X')) {
         base = 16;
	 name++;
      }
      state = 1;
    }
    else {  /* state != 0 */
      if (*name == '.') {
         name++;
         state = 0;
         continue;
      }
      if (isdigit(*name)) {
	 bytes[byte_ctr] = (bytes[byte_ctr] * base) + (*name - '0');
	 name++;
	 continue;
      }
      if ((base == 16) && isxdigit(*name)) { /* a-f,A-F */
         *name = toupper(*name);
         bytes[byte_ctr] = (bytes[byte_ctr] * base) + (10 + (*name - 'A'));
	 name++;
	 continue;
      }
      if (*name && (!isspace(*name)))
         return(-1);
    } /* end of state != 0 */
  } /* end of while loop */

  for(value = 0,i=0; i < byte_ctr; i++) {
     value = value << 8;
     value = value | (bytes[i] & 0xFF);
  }

  return(value);

} /* end of inet_network */

inet_lnaof(in)
        struct in_addr in;
{
        unsigned long addr = ntohl(in.s_addr);

        if ((addr & 0x80000000) == 0 ) /* class A */
           return(addr & 0x00FFFFFF);
        else if ((addr & 0xC0000000) == 0x80000000) /* class B */
           return(addr & 0x0000FFFF);
        else  /* class C */
           return(addr & 0x000000FF);
}

inet_netof(in)
	struct in_addr in;
{
        unsigned long addr = ntohl(in.s_addr);

        if ((addr & 0x80000000) == 0 ) /* class A */
           return(addr & 0xFF000000);
        else if ((addr & 0xC0000000) == 0x80000000) /* class B */
           return(addr & 0xFFFF0000);
        else  /* class C */
           return(addr & 0xFFFFFF00);
}

