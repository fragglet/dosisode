void outch( char ch );		/* print character to stdio */
void outs( char far *s);	/* print a ASCIIZ string to stdio */
void outsn( char far *s,int n);	/* print a string with len max n */
void outhex( char ch );
void outhexes( char far *ch, int n );
void qmove( void far * src, void far * dest, int len );
int  qcmp( void far *src, void far *dest, int len );
void _keep( int status, int paragraphs );
int  sem_up( void far * ptr );
unsigned long set_timeout( unsigned int seconds );
unsigned long set_ttimeout( unsigned int ticks );
int chk_timeout( unsigned long timeout );

unsigned long intel( unsigned long );
unsigned intel16( unsigned );
unsigned inchksum( void far *ptr, int len);	/* IP checksum */
