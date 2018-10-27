#define CUSER 0
#define CPASS 1
#define CRETR 2
#define CSTOR 3
#define CQUIT 4
#define CSYST 5
#define CTYPE 6
#define CPORT 7
#define CPASV 8
#define CMKD 9
#define CCWD 10
#define CPWD 11
#define CLIST 12
#define CRMD 13
#define CRNFR 14
#define CRNTO 15
extern char **command_type;

int runcommand_user(int sock,int arglen, char* arg);
int runcommand_pass(int sock,int arglen, char* arg);
int runcommand_retr(int sock,int arglen, char* arg);
int runcommand_stor(int sock,int arglen, char* arg);
int runcommand_quit(int sock,int arglen, char* arg);
int runcommand_syst(int sock,int arglen, char* arg);
int runcommand_type(int sock,int arglen, char* arg);
int runcommand_port(int sock,int arglen, char* arg);
int runcommand_pasv(int sock,int arglen, char* arg);
int runcommand_mkd(int sock,int arglen, char* arg);
int runcommand_cwd(int sock,int arglen, char* arg);
int runcommand_pwd(int sock,int arglen, char* arg);
int runcommand_list(int sock,int arglen, char* arg);
int runcommand_rmd(int sock,int arglen, char* arg);
int runcommand_rnfr(int sock,int arglen, char* arg);
int runcommand_rnto(int sock,int arglen, char* arg);