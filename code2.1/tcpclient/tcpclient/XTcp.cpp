#include "XTcp.h"


XTcp::XTcp() :sock(-1), port(0), ip(""), client_sock(-1)
{
#ifdef WIN32
	static bool first = true;
	if (first)
	{
		first = false;
		WSADATA ws;
		WSAStartup(MAKEWORD(2, 2), &ws);
	}

#endif
}


XTcp::~XTcp()
{
}

int XTcp::CreateclientSocket()
{
	client_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (client_sock == -1)
	{
		printf("create socket failed!\n");
		return -1;
	}
	printf("[sock = %d]\n", client_sock);

	return 1;
}

int XTcp::CreateSocket()
{
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == -1)
	{
		printf("create socket failed!\n");
		return -1;
	}
	printf("[sock = %d]\n", sock);

	return 1;
}

bool XTcp::Bind(unsigned short port)
{
	sockaddr_in saddr;
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(port);
	saddr.sin_addr.s_addr = htonl(0);

	if (::bind(sock, (sockaddr*)&saddr, sizeof(saddr)) != 0)
	{
		printf("bind port %d failed\n", port);
		return false;
	}
	printf("bind port %d port succed\n", port);

	listen(sock, 10);

	return true;
}
int XTcp::Accept()
{
	sockaddr_in caddr;
	socklen_t len = sizeof(caddr);
	client_sock = accept(sock, (sockaddr*)&caddr, &len);
	if (client_sock < 0)
	{
		printf("accept error!\n");
		return -1;
	}
	printf("accept client %d\n", client_sock);

	char* ip = inet_ntoa(caddr.sin_addr);
	unsigned short client_port = ntohs(caddr.sin_port);
	printf("recive client ip: %s : %d\n", ip, client_port);

	return 1;
}
void XTcp::Close(int sock)
{
#ifdef WIN32
	closesocket(sock);
#else
	close(sock);
#endif
}
int XTcp::Recv(char* buff, int buffsize)
{
	return recv(client_sock, buff, buffsize, 0);
}
int XTcp::Send(const char* buf, int sendsize)
{
	int s = 0;
	while (s != sendsize)
	{
		int len = send(client_sock, buf + s, sendsize - s, 0);
		if (len <= 0)
			break;
		s += len;
	}
	return s;
}

int XTcp::GetClientSock()
{
	return client_sock;
}
int XTcp::GetServerSock()
{
	return sock;
}

int XTcp::GetLocalSock()
{
	return sock;
}

int XTcp::Connect(char* argv[])
{
	sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_port = htons(atoi(argv[2]));
	inet_pton(AF_INET, argv[1], &saddr.sin_addr.s_addr);

	if (::connect(client_sock, (sockaddr*)&saddr, sizeof(saddr)) < 0)
	{

		cout << "connect error" << endl;
		return -1;
	}


	return 1;
}