#include "command_resp.h"
#include <sys/socket.h>
int codenum[]={220,500};
char *codemsg[]={"ftp.ssast.org FTP server ready.",
				"Syntax error, command unrecognized."};
int send_code(int connfd, int code, int argc, int *argv){
	int respsize = (sizeof codenum)/(sizeof (int));
	int i;
	int codeidx=-1;
	//find code
	for(i = 0; i < respsize; i++){
		if(codenum[i]==code) {
			codeidx = i;
			break;
		}
	}
	if(codeidx==-1){
		printf("Error: No codenum %d\n", code);
		return 1;
	}
	send(connfd, codemsg[codeidx],sizeof(codemsg[codeidx]),0);
}