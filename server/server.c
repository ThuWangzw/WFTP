#include <sys/socket.h>
#include <netinet/in.h>

#include <unistd.h>
#include <errno.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include <memory.h>
#include <stdio.h>
#include "command_resp.h"
#include "command_parse.h"
#define ip_address "127.0.0.1"
#define port_num 6789
#define STATUS_LOGOUT 1
#define STATUS_WAITINGPASS 2

void *command_dispatch(void *pconnfd);
int main(int argc, char **argv) {
	int listenfd, connfd;		//监听socket和连接socket不一样，后者用于数据传输
	struct sockaddr_in addr;
	char sentence[8192];
	int p;
	int len;
	pthread_t tid;
	//创建socket
	if ((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == -1) {
		printf("Error socket(): %s(%d)\n", strerror(errno), errno);
		return 1;
	}

	//设置本机的ip和port
	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port_num);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);	//监听"0.0.0.0"

	//将本机的ip和port与socket绑定
	if (bind(listenfd, (struct sockaddr*)&addr, sizeof(addr)) == -1) {
		printf("Error bind(): %s(%d)\n", strerror(errno), errno);
		return 1;
	}

	//开始监听socket
	if (listen(listenfd, 10) == -1) {
		printf("Error listen(): %s(%d)\n", strerror(errno), errno);
		return 1;
	}

	//持续监听连接请求
	while (1) {
		//等待client的连接 -- 阻塞函数
		if ((connfd = accept(listenfd, NULL, NULL)) == -1) {
			printf("Error accept(): %s(%d)\n", strerror(errno), errno);
			continue;
		}
		printf("Client %d connects to the server (ftp.ssast.org)\n",connfd);
		if((pthread_create(&tid,NULL,command_dispatch,&connfd))!=0){
			printf("Error pthread__create(): %s(%d)\n", strerror(errno), errno);
			continue;
		}
	}
	close(listenfd);
	return 0;
}
void *command_dispatch(void *pconnfd){
	int connfd = *(int *)pconnfd;
	int status=STATUS_LOGOUT;
	char recv_com[1000]="";
	int iresult = 0;
	struct Command com;
	send_code(connfd, 220,0,NULL);
	while(1){
		if((iresult = recv(connfd, recv_com, 1000, 0))==-1){
			printf("Error recv(): %s(%d)\n", strerror(errno), errno);
			continue;
		}
		else if(iresult == 0){
			//connection has closed
			break;
		}
		if((command_parser(recv_com,iresult,&com))!=0){
			//command not found
			send_code(connfd, 500,0,NULL);
			continue;
		}
		//
		
		//
		if((iresult = com.func(connfd, com.arg_len,com.arg))==1){
			//response error
			printf("Error func(): response error\n");
			continue;
		}
		else if(iresult ==2){
			//connection failed
			printf("Error func(): connection failed\n");
			break;
		}
	}
	//close(connfd);
	printf("closed\n");
	return;
}