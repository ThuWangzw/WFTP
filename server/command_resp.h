#ifndef COMMAND_RESP
#define COMMAND_RESP
int send_code(int connfd, int code, int argc, int *argv);
int lenofstr(char* str);

#endif //COMMAND_RESP