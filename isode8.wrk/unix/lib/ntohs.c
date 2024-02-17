unsigned long ntohl(x)
unsigned long x;
{
return(( ((x) >> 24)& 0x000000ff ) | ( ((x) >> 8) & 0x0000ff00 ) |
       ( ((x) << 8) & 0x00ff0000 ) | ( ((x) << 24)& 0xff000000 ));
/*
return(x);
*/
}

unsigned short ntohs(x)
unsigned short x;
{
return((((x) >> 8) | ((x) << 8)) & 0xffff);
/*
return(x);
*/
}

unsigned long htonl(x)
unsigned long x;
{

return(( ((x) >> 24)& 0x000000ff ) | ( ((x) >> 8) & 0x0000ff00 ) |
       ( ((x) << 8) & 0x00ff0000 ) | ( ((x) << 24)& 0xff000000 ));
/*
return(x);
*/
}

unsigned short htons(x)
unsigned short x;
{
return((((x) >> 8) | ((x) << 8)) & 0xffff);
/*
return(x);
*/
}
