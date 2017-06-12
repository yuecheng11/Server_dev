#pragma once
#ifdef XSOCKET_EXPORTS
#define XSOCKET_API __declspec(dllexport)
#else
#define XSOCKET_API __declspec(dllimport)
#endif

#include <string>

class XSOCKET_API XTcp
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
private:
	int sock;
	unsigned short port;
	std::string ip;
	int client_sock;
};

