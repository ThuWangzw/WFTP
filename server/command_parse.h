struct Command{
	char *name;
	int name_len;
	char *arg;
	int arg_len;
	int (*func)(int,int,char*);//sock,len,arg
}; 
//return -1:command not found, 0:success
int command_parser(char *str, int strlen, struct Command* com);