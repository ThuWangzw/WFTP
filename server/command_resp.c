#include "command_resp.h"
#include <sys/socket.h>
int codenum[]={220,500,332};
char *codemsg[]={"220 ftp.ssast.org FTP server ready.\r\n",
				"500 Syntax error, command unrecognized.\r\n",
				"332 Need account for login.\r\n"};
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
	//printf("%d,%d\n",codeidx,sizeof(codemsg[codeidx]));
	send(connfd, codemsg[codeidx],strlen(codemsg[codeidx]),0);
}