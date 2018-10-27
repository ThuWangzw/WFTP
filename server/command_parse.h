struct Command{
	char *name;
	int name_len;
	char *arg;
	int arg_len;
	void* func(int,char*);
}; 
//return -1:command not found, 0:success
int command_parser(char *str, int strlen, Command* com);