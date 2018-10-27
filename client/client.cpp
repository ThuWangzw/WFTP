#include <WinSock2.h>
#include <errno.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include "command.h"
#pragma comment(lib,"ws2_32.lib")
#define host_address "127.0.0.1"
#define port_num 6789
char *codemsg[] = { "ftp.ssast.org FTP server ready.\r\n",
"Syntax error, command unrecognized.\r\n" };
int main(int argc, char **argv) {
	int sockfd;
	struct sockaddr_in addr;
	char sentence[8192]="";
	int len;
	int p;
	char recvbuff[1024] = "";
	CommandCtrl* ct;
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	int ires;
	//����socket
	if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		printf("Error socket(): %s(%d)\n", strerror(errno), errno);
		return 1;
	}

	//����Ŀ��������ip��port
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_num);
	addr.sin_addr.S_un.S_addr = inet_addr(host_address);

	//������Ŀ����������socket��Ŀ���������ӣ�-- ��������
	if (connect(sockfd, (struct sockaddr*)&addr, sizeof(addr)) < 0) {
		printf("Error connect(): %s(%d)\n", strerror(errno), errno);
		return 1;
	}
	recv(sockfd, recvbuff, 1024, 0);
	printf("%s",recvbuff);
	while (true)
	{
		//��ȡ��������
		printf(">>>");
		fgets(sentence, 4096, stdin);
		len = strlen(sentence);
		sentence[len - 1] = 0;
		
		ct = command_dispatch(sentence, len - 1);

		//�Ѽ�������д��socket
		p = 0;
		int n = send(sockfd, sentence, len, 0);		//write��������֤���е�����д�꣬������;�˳�
		if (n < 0) {
			printf("Error send(): %s(%d)\n", strerror(errno), errno);
			return 1;
		}
		//TODO ������
		if ((ires=ct->run(sockfd)) == 1) {
			//connection failed
			printf("Connection failed");
			WSACleanup();
			return 1;
		}
	}

	closesocket(sockfd);
	WSACleanup();

	return 0;
}
