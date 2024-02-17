#include <stdio.h>
#include <errno.h>
#define BUFFER 1024

extern int errno;

main(argc, argv)
int argc;
char *argv[];
{
	char buffer[BUFFER], *p, *q, *r, *strchr(), *strcat(), *unix2dos();
	FILE *fopen(), *infile, *outfile;

	if (argc < 2) {
		printf("Usage: pass1 infile outfile\n");
		exit(1);
	}
	if ( (infile = fopen(argv[1],"r")) == NULL) {
		printf("%s does not exist\n",argv[1]);
		exit(1);
	}
	if ( (outfile = fopen(argv[2],"w")) == NULL) {
		printf("Cannot open output file errno=%d\n",errno);
		exit(1);
	}
	if (argv[2][strlen(argv[2]) - 1] == 'c') fprintf(outfile,"#include <fiddle.h>\n");
	
	while (fgets(buffer, BUFFER, infile) != NULL) {
		if (strncmp(buffer,"#include",8) == 0) {
			p = index(buffer,'.');
			if (p && *(p+1) != 'h' 
				&& *(p+1) != 'c'
				&& *(p+1) != '.') *p = '_';
		}
		fputs(buffer, outfile);
	}
	fclose(infile);
	fclose(outfile);
	exit(0);
}

