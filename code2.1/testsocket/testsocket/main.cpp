#include <stdlib.h>
#include <iostream>
#include "XTcp.h"
#include <thread>
#include <string.h>

using namespace std;

class Tcpthread
{
public:
	void Execute()
	{
		char buff[1024] = { 0 };
		while (1)
		{
			int bufflen = Tcpserver.Recv(buff, sizeof(buff) - 1);
			if (bufflen <= 0) break;

			buff[bufflen] = '\0';
			if (strstr(buff, "quit") != NULL)
			{
				printf("client exit\n");
				char reply[] = "quit succed!\n";
				int sendsize = Tcpserver.Send(reply, strlen(reply) + 1);
				if (sendsize != strlen(reply) + 1)
				{
					cout << "send reply error!" << endl;
				}
				break;
			}
			int sendlen = Tcpserver.Send("ok\n", 4);
			int sendsize = Tcpserver.Send("ok\n", 4);
			if (sendsize != 4)
			{
				cout << "send reply error!" << endl;
		}
			printf("recv %s\n", buff);
		}
		Tcpserver.Close(Tcpserver.GetClientSock());
			delete this;
	}
	XTcp Tcpserver;
};

int main(int argc,char* argv[])
{

	XTcp TcpServer;
	unsigned short port = 8080;
	if (argc > 1)
	{
		port = atoi(argv[1]);
	}
	int check;
	check = TcpServer.CreateSocket();
	if (check < 0)
	{
		return -1;
	}
	if (!TcpServer.Bind(port))
	{
		return -1;
	}

	while (1)
	{
		
		check = TcpServer.Accept();
		if (check < 0)
		{
			return -1;
		}

		Tcpthread* th = new Tcpthread();
		th->Tcpserver = TcpServer;
		thread sth(&Tcpthread::Execute,th);
		sth.detach();
	}
	

	getchar();

	TcpServer.Close(TcpServer.GetServerSock());

	return 0;
}