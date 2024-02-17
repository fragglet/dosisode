#include <stdio.h>
#include <ctype.h>
#include <Types.h>
#include <Files.h>
#include <Traps.h>
#include <Desk.h>
#include <Devices.h>

extern int errno;

main(argc, argv)
int argc;
char *argv[];
{
	char last_token[128];
	char last_function[128];
	char token[128];
	int in_function = 0;
	int extra_brace_needed = 0;
	int return_found = 0;
	char *p = token;
	int brace_count = 0;
	int loop_count = 0;
	int i;
	FILE *fopen(), *infile, *outfile;

	if (argc < 2) {
		printf("Usage: Trace infile outfile\n");
		exit();
	}

	if ( (infile = fopen(argv[1],"r")) == NULL) {
		printf("%s does not exist\n",argv[1]);
		exit();
	}
	if ( (outfile = fopen(argv[2],"w")) == NULL) {
		printf("Cannot open output file errno=%d\n",errno);
		exit();
	}

	/*read in characters - if in quotes ignore - if \ ignore next char*/
	/*pick out tokens  - store the last one if we are outside fcts*/
	/*if token is a ( then store last_token as possible fct name */
	/*if we find a { and last_token was a ) or ; then we at start of fct*/

	/*if we are at start of function - write :
		char *si_fct_name = "FCT";int si_trace_flag = si_trace_in(si_fct_name);*/

	/*if this token is a 'return' then if next token is a ; write :
		return(si_trace_out(si_fct_name));

	  if next token is a ( write :
	  	return((si_trace_out(si_fct_name),.......)) */
	/*if we find a } that finishes a function write :
		si_trace_out(si_fct_name);} */

	while ( (i=fgetc(infile)) != EOF ) {
		loop_count++;
		if (loop_count == 100) {SystemTask();loop_count = 0;}
		if (isspace(i)) {
			fputc(i,outfile);
			while (isspace(i=fgetc(infile))) fputc(i,outfile);
			if (i == EOF) exit(0);
		}
		if (i == '\'') { /*ignore all within single quotes*/
			fputc(i,outfile);
			while ( (i=fgetc(infile)) != '\'') {
				fputc(i,outfile);
				if (i == '\\') fputc(fgetc(infile),outfile);
			}
			fputc(i,outfile);
		}
		else if (i == '\"') { /*ignore all within double quotes*/
			fputc(i,outfile);
			while ( (i=fgetc(infile)) != '\"') {
				fputc(i,outfile);
				if (i == '\\') fputc(fgetc(infile),outfile);
			}
			fputc(i,outfile);
		}
		else {
			if (isalpha(i)) {
				*p++ = i;
				while ( (isalnum (i=fgetc(infile))) || i == '_') *p++ = i;
				ungetc(i, infile);
				p--;
				i = *p;
				p++;
				*p = '\0';
				p = token;
				if (strcmp(token, "return") == 0) {
					fprintf(outfile,"{si_trace_out(si_fct_name);");
					extra_brace_needed = 1;
				}
				fprintf(outfile,"%s",token);
			}
			else {
				if (i != '}') fputc(i,outfile);
				*p++ = i;
				*p = '\0';
				p = token;
			}

			if (i == '{') brace_count++;
			if (i == '}') brace_count--;
			if (in_function) {
				if ((i == '}') && (brace_count == 0)) {
					in_function = 0;
					fprintf(outfile,"si_trace_out(si_fct_name);");
				}
			}
			else {
				if ((i == '{') && (brace_count == 1) &&
				 ((*last_token == ';') || (*last_token == ')'))) {
				 	if (strcmp(last_function,"main")) { /*Macs don't like this one*/
						in_function = 1;
						fprintf(outfile,"char *si_fct_name = \"%s\";",last_function);
						fprintf(outfile,"int pk_trace_flag = si_trace_in(si_fct_name);");
					}
				}
				else if (i == '(') {
					strcpy(last_function, last_token);
				}
			}
			if (i == ';') {
				if (extra_brace_needed) { extra_brace_needed = 0;fputc('}',outfile);}
			}
			if (i == '}') fputc(i,outfile);
			strcpy(last_token, token);
		}
	}
	exit(0);
}
