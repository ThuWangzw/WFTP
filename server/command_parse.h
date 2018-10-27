#ifndef COMMAND_PARSE
#define COMMAND_PARSE
#define STATUS_LOGIN 0
#define STATUS_LOGOUT 1
#define STATUS_WAITINGPASS 2
#include "command.h"

//return -1:command not found, 0:success
int command_parser(char *str, int strlen, struct Command* com,int status);

#endif //COMMAND_PARSE