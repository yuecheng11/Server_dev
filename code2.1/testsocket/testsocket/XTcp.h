#pragma once

#include <string>

class XTcp
{
public:
	XTcp();
	int CreateSocket();
	bool Bind(unsigned short port);
	int Accept();
	void Close(int sock);
	int Recv(char* buff,int buffsize);
	int Send(const char* buf,int sendsize);
	virtual ~XTcp();
	int GetClientSock();
	int GetServerSock();
	int GetLocalSock();
private:
	int sock;
	unsigned short port;
	std::string ip;
	int client_sock;
};

