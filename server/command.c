#include <strings.h>
#include "command.h"
#include "command_resp.h"
#include <sys/socket.h>
#include <ctype.h>
#include <pthread.h>
char *command_type[] = {
	"USER", "PASS", "RETR", "STOR", "QUIT", "SYST", "TYPE", "PORT", "PASV", "MKD", "CWD", "PWD","LIST", "RMD", "RNFR", "RNTO"
};

int runcommand_user(int sock,int arglen, char *arg, struct ConInfo* info){
	if(arglen==0){
		//no user
		send_code(info->sock,501,0,0);
		return 0;
	}
	
	bzero(info->username,50);
	bcopy(arg,info->username,arglen);
	info->userlen = arglen;
	info->status = STATUS_WAITINGPASS;
	//printf("%d%s\n",arglen,arg);
	send_code(info->sock,331,0,0);
	return 0;
}
int runcommand_pass(int sock,int arglen, char *arg, struct ConInfo* info){
	//if an anonymous
	//printf("pass %d%s\n",arglen,arg);
	if((info->userlen==9)&&(!strcmp(info->username,"anonymous"))){
		//check password
		
		//
		info->status = STATUS_LOGIN;
		send_code(info->sock,230,0,0);
		return 0;
	}
	//not anoutmous.forbid
	send_code(info->sock,530,0,0);
	return 0;
}
int runcommand_retr(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_stor(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_quit(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_syst(int sock,int arglen, char *arg, struct ConInfo* info){
	if(arglen>0){
		send_code(info->sock,501,0,0);
	}
	send_code(info->sock,215,0,0);	return 0;
}
int runcommand_type(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_port(int sock,int arglen, char *arg, struct ConInfo* info){
	unsigned int ip=0;
	int port=0;
	int i;
	int dotcount = 0;
	int portidx=0;
	int correct = 1;
	int temp = 0;
	//parse
	for(i=0;i<arglen;i++){
		if(arg[i]=='.'){
			dotcount++;
			if(dotcount==4){
				portidx = i+1;
			}
		}
		else{
			if(!isdigit(arg[i])){
				correct = 0;
			}
		}
	}
	if((dotcount!=5)){
		correct = 0;
	}
	if(correct==0){
		send_code(info->sock,501,0,0);
		return 0;
	}
	for(i=0;i<arglen;i++){
		if(arg[i]=='.'){
			if(i<portidx){
				ip=(ip<<8)+temp;
				temp=0;
			}
			else{
				port = temp<<8;
				temp=0;
			}
			continue;
		}
		temp=temp*10+(arg[i]-'0');
	}
	port = port + temp;
	//port or pasv,close
	if(info->status == STATUS_PORT){
		info->cip = ip;
		info->cport = port;
	}
	else if(info->status == STATUS_PASV){
		if(pthread_cancel(info->tid)){
			//kill failed
			send_code(info->sock,425,0,0);
			printf("Error occured in pthread_cancel()\n");
		}
		info->status = STATUS_PORT;
		info->cip = ip;
		info->cport = port;
	}
	else if(info->status == STATUS_LOGIN){
		info->status = STATUS_PORT;
		info->cip = ip;
		info->cport = port;
	}
	else{
		//will never enter this code
		printf("Error occred in command_port,Entering error code.\n");
		send_code(info->sock,425,0,0);
		return 0;
	}
	//printf("%d\n%x,%d\n",arglen,info->cip,info->cport);
	send_code(info->sock,200,0,0);	return 0;
}
int runcommand_pasv(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_mkd(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_cwd(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_pwd(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_list(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_rmd(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_rnfr(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}
int runcommand_rnto(int sock,int arglen, char *arg, struct ConInfo* info){
return 0;
}