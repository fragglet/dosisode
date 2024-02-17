/* <sys/wait.h> */
union wait {
   int w_status;
   struct {
   unsigned short w_termsig:7;
   unsigned short w_Coredump:1;
   unsigned short w_Retcode:8;
   } w_T;
   struct {
   unsigned short w_Stopval:8;
   } w_S;
};
#define w_termsig w_T.w_Termsig
#define w_coredump w_T.w_Coredump
#define w_retcode w_T.w_Retcode
#define w_stopval w_S.w_Stopval
#define w_stopsig w_S.w_Stopsig
#define WSTOPPED 0177
#define WNOHANG  1
#define WUNTRACED 2
#define WIFSTOPPED(x) ((x).w_stopval == WSTOPPED)
#define WIFSIGNALED(x) ((x).w_stopval != WSTOPPED && (x).w_termsig !=0)
#define WIFEXITED(x) ((x).w_stopval != WSTOPPED && (x).w_termsig == 0)

