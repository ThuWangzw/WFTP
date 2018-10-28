#include "command_resp.h"
#include <sys/socket.h>
int codenum[]={220,500,332,331,501,230,530,425,200,215};
char *codemsg[]={"220 ftp.ssast.org FTP server ready.\r\n",
				"500 Syntax error, command unrecognized.\r\n",
				"332 Need account for login.\r\n",
				"331 Guest login ok, send your complete e-mail address as password.\r\n",
				"501 Syntax error in parameters or arguments.\r\n",
				"230 Guest login ok, access restrictions apply.\r\n",
				"530 Login incorrect.\r\n",
				"425 Can't open data connection.\r\n",
				"200 Command okay.\r\n",
				"215 UNIX Type: L8.\r\n"};
int send_code(int connfd, int code, int argc, char *argv){
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
	if(argc==0){
		send(connfd, codemsg[codeidx],strlen(codemsg[codeidx]),0);
	}
	else{
		send(connfd, argv,argc,0);
	}
	return 0;
}