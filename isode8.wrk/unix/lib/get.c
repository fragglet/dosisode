#include <stdio.h>
#include <strings.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fiddle.h>

char *malloc(), *unix2dos();
static int debug = 0;
static char PWDB[] = "/etc/passwd";

static FILE *pwf = NULL;
static char line[129];
static struct passwd pw;
static char *any();
int _pw_stayopen;
FILE *fopen();
char *fgets();

#undef time

char **environ;

static char encrypted_passwd[128];
char *crypt(key,salt)
const char *key, *salt;
{
	strcpy(encrypted_passwd,key);
	return(encrypted_passwd);
}

struct passwd *getpwnam(name)
char *name;
{
	register struct passwd *p;
	register char **cp;

	setpwent();
	while (p = getpwent()) {
		if (strcmp(name, p->pw_name) == 0) break;
	}
	if (!_pw_stayopen) endpwent();
	return (p);
}

struct passwd *getpwuid(uid)
int uid;
{
	register struct passwd *p;
	register char **cp;

	setpwent();
	while (p = getpwent()) {
		if (p->pw_uid == uid) break;
	}
	if (!_pw_stayopen) endpwent();
	return (p);
}

struct passwd *getpwent()
{
	char *p;
	register char *cp, **q;

	if (pwf == NULL && (pwf = fopen(PWDB, "r" )) == NULL)
		return (NULL);
again:
	if ((p = fgets(line, BUFSIZ, pwf)) == NULL)
		return (NULL);
	if (*p == '#') goto again;
	cp = strchr(p, ':');
	if (cp == NULL) goto wrong;
	*cp++ = '\0';
	pw.pw_name = p;
	p = strchr(cp, ':');
	if (p == NULL) goto wrong;
	*p++ = '\0';
	pw.pw_passwd = cp;
	cp = strchr(p, ':');
	if (cp == NULL) goto wrong;
	*cp++ = '\0';
	pw.pw_uid = atoi(p);
	p = strchr(cp, ':');
	if (p == NULL) goto wrong;
	*p++ = '\0';
	pw.pw_gid = atoi(cp);
	cp = strchr(p, ':');
	if (cp == NULL) goto wrong;
	*cp++ = '\0';
	pw.pw_gecos = p;
	p = strchr(cp, ':');
	if (p == NULL) goto wrong;
	*p++ = '\0';
	pw.pw_dir = cp;
	return (&pw);
wrong:
	fprintf(stderr,"Error in format of /etc/passwd file\n - %s -\n",line);
	return(NULL);
}

setpwent()
{
	if (pwf == NULL)
		pwf = fopen(PWDB, "r" );
	else
		rewind(pwf);
	_pw_stayopen = 1;
}

endpwent()
{
	if (pwf) {
		fclose(pwf);
		pwf = NULL;
	}
	_pw_stayopen = 0;
}

unsigned si_getuid()
{
	return(0);
}

int si_geteuid()
{
	return(0);
}

int getppid()
{
	return(0);
}
seteuid(euid)
int euid;
{
  return(0);
}

setruid(ruid)
int ruid;
{
  return(0);
}

getitimer(which, value)
int which;
struct itimerval *value;
{
if (debug) fprintf(stderr,"getitimer called\n");
   return(-1);
}

setitimer(which, value, ovalue)
int which;
struct itimerval *value, *ovalue;
{
if (debug) fprintf(stderr,"setitimer called\n");
   return(-1);
}

getusertty(name, tty)
char *name, *tty;
{
if (debug) fprintf(stderr,"getusertty called\n");
}

getdtablesize()
{
   return(16);
}

getpagesize()
{
   return(BUFSIZ);
}

struct group *getgrent()
{
   return(NULL);
}

struct group *getgrgid(gid)
int gid;
{
   return(NULL);
}

struct group *getgrnam(name)
char *name;
{
   return(NULL);
}

setgrent()
{
}

endgrent()
{
}

initgroups(name,basegid)
char *name;
int basegid;
{
}

int fork()
{
}

int vfork()
{
}

int pipe(p)
int *p;
{
}

int wait(status)
int *status;
{
}

int wait3(status, options, rusage)
union wait *status;
int options;
struct rusage *rusage;
{
}

int chroot(dirname)
char *dirname;
{
	return(0);
}


