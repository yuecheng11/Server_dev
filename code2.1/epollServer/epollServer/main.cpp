#include <stdlib.h>
#include <iostream>
#include "XTcp.h"
#include <thread>
#include <string.h>
#include <fcntl.h>

using namespace std;

/*
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

*/
#include <sys/epoll.h>
int main(int argc, char* argv[])
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

	int epfd = epoll_create(256);
	//注册epoll事件
	struct epoll_event ev;
	ev.data.fd = TcpServer.GetServerSock();

	//数据接入事件|边缘检测
	ev.events = EPOLLIN | EPOLLET;
	epoll_ctl(epfd, EPOLL_CTL_ADD, TcpServer.GetServerSock(), &ev);

	struct epoll_event event[20];
	char buf[1024] = { 0 };
	const char *msg = "HTTP/1.1 200 OK\r\nContent-Length: 1\r\n\r\nX";
	int size = strlen(msg);

	//int flags = fcntl(TcpServer.GetServerSock(), F_GETFL, 0);
	//fcntl(TcpServer.GetServerSock(), F_SETFL, flags | O_NONBLOCK);

	while (1)
	{
		//检测事件
		int count = epoll_wait(epfd,event,20,500);
		if (count <= 0) continue;
		for (int i = 0; i < count; i++)
		{
			//连接事件
			if (event[i].data.fd == TcpServer.GetServerSock())
			{
				//for (;;)
				{
					check = TcpServer.Accept();
					if (check < 0)
					{
						break;
					}

					//新注册客户端事件
					ev.data.fd = TcpServer.GetClientSock();
					ev.events = EPOLLIN | EPOLLET;
					epoll_ctl(epfd, EPOLL_CTL_ADD, TcpServer.GetClientSock(), &ev);

				}
			}
			else
			{
				XTcp Client;
				int client_sock = event[i].data.fd;
				Client.setclientsock(client_sock);
				Client.Recv(buf,1024);
				Client.Send(msg,size);
				epoll_ctl(epfd, EPOLL_CTL_DEL, Client.GetLocalSock(), &ev);
				Client.Close(client_sock);
			}
		}
		/*
		check = TcpServer.Accept();
		if (check < 0)
		{
			return -1;
		}

		Tcpthread* th = new Tcpthread();
		th->Tcpserver = TcpServer;
		thread sth(&Tcpthread::Execute, th);
		sth.detach();
		*/
	}


	getchar();

	TcpServer.Close(TcpServer.GetServerSock());

	return 0;
}