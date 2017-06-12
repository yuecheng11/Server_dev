#pragma once

#include <string>
#ifdef _WIN64
#define WIN32
#endif
#include <string.h>
#include <stdio.h>
#include <thread>
#include <iostream>

#ifdef WIN32
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#define socklen_t int
#else
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

using namespace std;
class XTcp
{
public:
	XTcp();
	int CreateSocket();
	bool Bind(unsigned short port);
	int Accept();
	void Close(int sock);
	int Recv(char* buff, int buffsize);
	int Send(const char* buf, int sendsize);
	virtual ~XTcp();
	int GetClientSock();
	int GetServerSock();
	int GetLocalSock();
	int CreateclientSocket();

	int Connect(char* argv[]);
private:
	int sock;
	unsigned short port;
	std::string ip;
	int client_sock;
};
