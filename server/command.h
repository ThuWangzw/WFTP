#ifndef COMMAND
#define COMMAND
#define COMMAND_NUM 16
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
#define NAME_MAX_LEN
#define STATUS_LOGIN 0
#define STATUS_LOGOUT 1
#define STATUS_WAITINGPASS 2
#define STATUS_PORT 3
#define STATUS_PASV 4
struct ConInfo{
	char username[50];
	int userlen;
	int status;
	int sock;
	unsigned int cip;
	int cport;
	unsigned int mip;
	int mport;
	int tid;
};
struct Command{
	char *name;
	int name_len;
	char *arg;
	int arg_len;
	int (*func)(int,int,char*,struct ConInfo*);//sock,len,arg,status
}; 
extern char *command_type[];

int runcommand_user(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_pass(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_retr(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_stor(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_quit(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_syst(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_type(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_port(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_pasv(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_mkd(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_cwd(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_pwd(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_list(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_rmd(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_rnfr(int sock,int arglen, char* arg, struct ConInfo* info);
int runcommand_rnto(int sock,int arglen, char* arg, struct ConInfo* info);

#endif //COMMAND