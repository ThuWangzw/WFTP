#include "command_parse.h"
#include "command_resp.h"
int command_find(struct Command* com){
	//return value 0:ok, 1:not found 2:connection closed
	return 0;
}
int command_parser(char *str, int strlen, struct Command* com){
	//return value 0:ok 1:not found 2:connection closed
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
	printf("com name:%s\ncomlen:%d\narg:%s\narglen:%d\n",com->name,com->name_len,com->arg,com->arg_len);
	//endtest
	//find
	return command_find(com);
}