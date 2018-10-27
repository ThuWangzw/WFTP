#include "command_parse.h"
#include "command_resp.h"
#include "command.h"
#include <strings.h>
int command_find(struct Command* com,int status){
	//return value 0:ok, 500:not found -1:connection closed
	int command_num  = COMMAND_NUM;
	int i;
	int com_idx = -1;
	//find
	for(i = 0;i < command_num; i++){
		printf("%d\n",strlen(command_type[i]));
		if((com->name_len==(strlen(command_type[i])))&&(!strncasecmp(com->name,command_type[i],com->name_len))){
			//found!
			com_idx = i;
			break;
		}
		
	}
	if(com_idx==-1){
		//not found
		return 500;
	}
	//dispatch
	switch(status){
		case STATUS_LOGOUT:
			switch(com_idx){
				case CUSER:
					com->func = runcommand_user;
					break;
				default:
					return 332;
					break;
			}
			break;
		case STATUS_WAITINGPASS:
			switch(com_idx){
				case CPASS:
					com->func = runcommand_pass;
					break;
				default:
				return 332;
					break;		
			}
		case STATUS_LOGIN:
			switch(com_idx){
				case CRETR:
					com->func = runcommand_retr;
					break;
				case CSTOR:
					com->func = runcommand_stor;
					break;
				case CQUIT:
					com->func = runcommand_quit;
					break;
				case CSYST:
					com->func = runcommand_syst;
					break;
				case CTYPE:
					com->func = runcommand_type;
					break;
				case CPORT:
					com->func = runcommand_port;
					break;
				case CPASV:
					com->func = runcommand_pasv;
					break;
				case CMKD:
					com->func = runcommand_mkd;
					break;
				case CCWD:
					com->func = runcommand_cwd;
					break;
				case CPWD:
					com->func = runcommand_pwd;
					break;
				case CLIST:
					com->func = runcommand_list;
					break;
				case CRMD:
					com->func = runcommand_rmd;
					break;
				case CRNFR:
					com->func = runcommand_rnfr;
					break;
				case CRNTO:
					com->func = runcommand_rnto;
					break;
				default:
					printf("strange error at command_find!\n");
					break;
			}
		default:
			break;
	}
	switch(com_idx){
		case CPASS:
			com->func = runcommand_pass;
			break;
		case CRETR:
			com->func = runcommand_retr;
			break;
		case CSTOR:
			com->func = runcommand_stor;
			break;
		case CQUIT:
			com->func = runcommand_quit;
			break;
		case CSYST:
			com->func = runcommand_syst;
			break;
		case CTYPE:
			com->func = runcommand_type;
			break;
		case CPORT:
			com->func = runcommand_port;
			break;
		case CPASV:
			com->func = runcommand_pasv;
			break;
		case CMKD:
			com->func = runcommand_mkd;
			break;
		case CCWD:
			com->func = runcommand_cwd;
			break;
		case CPWD:
			com->func = runcommand_pwd;
			break;
		case CLIST:
			com->func = runcommand_list;
			break;
		case CRMD:
			com->func = runcommand_rmd;
			break;
		case CRNFR:
			com->func = runcommand_rnfr;
			break;
		case CRNTO:
			com->func = runcommand_rnto;
			break;
		default:
			printf("strange error at command_find!\n");
			break;
	}
	return 0;
}
int command_parser(char *str, int strlen, struct Command* com,int status){
	//return value 0:ok 500:not found -1:connection closed
	int i;
	//init com
	com->name = str;
	com->name_len = 0;
	com->arg = 0;
	com->arg_len = 0;
	//parser
	for(i = 0; i < strlen; i++){
		if(str[i]==' '){
			str[i]=0;
			com->name_len = i;
			com->arg = str+i+1;
			com->arg_len = strlen-i-1;
			break;
		}
	}
	if(com->name_len == 0){
		com->name_len = strlen;
	}
	//test
	//printf("com name:%s\ncomlen:%d\narg:%s\narglen:%d\n",com->name,com->name_len,com->arg,com->arg_len);
	//endtest
	//find
	return command_find(com,status);
}