#ifndef COMMAND_H
#define COMMAND_H
#define RECV_LEN 1000
class CommandCtrl
{
public:
	CommandCtrl();
	~CommandCtrl();
	int run(int t_sock);
protected:
	int sock;
	char resp[RECV_LEN];
	int reclen;
	int recvOnecom();
};
class CommonCtrl :public CommandCtrl
{

};
class PORTCtrl :public CommandCtrl
{

};
class PASVCtrl :public CommandCtrl
{

};
class RETRCtrl :public CommandCtrl
{

};
class STORCtrl :public CommandCtrl
{

};
class QUITCtrl :public CommandCtrl
{

};
CommandCtrl* command_dispatch(char* com,int len);
extern RETRCtrl retrCtrl;
extern STORCtrl storCtrl;
extern QUITCtrl quitCtrl;
extern PORTCtrl portCtrl;
extern PASVCtrl posvCtrl;
extern CommonCtrl commonCtrl;
#endif // !COMMAND_H
