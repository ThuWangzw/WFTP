#include "command.h"
#include <string.h>
#include <WinSock2.h>
#include <stdio.h>
#pragma comment(lib,"ws2_32.lib")
RETRCtrl retrCtrl;
STORCtrl storCtrl;
QUITCtrl quitCtrl;
PORTCtrl portCtrl;
PASVCtrl posvCtrl;
CommonCtrl commonCtrl;

CommandCtrl * command_dispatch(char * com, int len)
{
	char *name = com;
	int namelen = 0;
	for (int i = 0; i < len; i++) {
		if (com[i] == ' ') {
			namelen = i;
			break;
		}
	}
	if (namelen == 0) {
		namelen = len;
	}
	//dispatch
	if ((namelen == (sizeof("RETR") - 1)) && (_strnicmp(name, "RETR", namelen) == 0)) {
		return &retrCtrl;
	}
	if ((namelen == (sizeof("STOR") - 1)) && (_strnicmp(name, "STOR", namelen) == 0)) {
		return &storCtrl;
	}
	if ((namelen == (sizeof("QUIT") - 1)) && (_strnicmp(name, "QUIT", namelen) == 0)) {
		return &quitCtrl;
	}
	if ((namelen == (sizeof("PORT") - 1)) && (_strnicmp(name, "PORT", namelen) == 0)) {
		return &portCtrl;
	}
	if ((namelen == (sizeof("POSV") - 1)) && (_strnicmp(name, "POSV", namelen) == 0)) {
		return &posvCtrl;
	}
	return &commonCtrl;
}

CommandCtrl::CommandCtrl()
{
}

CommandCtrl::~CommandCtrl()
{
}

int CommandCtrl::run(int t_sock)
{
	this->sock = t_sock;
	this->recvOnecom();
	if (this->reclen==0) {
		//connection failed
		printf("Connection failed");
		return 1;
	}
	printf("%s",this->resp);
	return 0;
}

int CommandCtrl::recvOnecom()
{
	//return 0:ok 1:connection failed
	memset(this->resp, 0, RECV_LEN);
	if ((this->reclen = recv(this->sock, (this->resp), RECV_LEN, 0)) == 0) {
		printf("Connection failed");
		return 1;
	}
	return 0;
}
