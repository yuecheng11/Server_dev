#include <stdlib.h>
#include <iostream>
#include "XTcp.h"
#include <thread>
#include <string.h>


using namespace std;
int main(int argc, char* argv[])
{

	if (argc != 3)
	{
		cout << "param error" << endl;

		return -1;
	}
	XTcp client_obj;
	client_obj.CreateclientSocket();

	int conn = client_obj.Connect(argv);
	if (conn < 0)
	{
		return -1;
	}

	cout << "connect succed" <<endl;


	while (1)
	{
		const char *msg = "Get http/1.1\n";

		client_obj.Send(msg, strlen(msg));

		char buff[1024] = { 0 };

		client_obj.Recv(buff, sizeof(buff));
		cout << buff << endl;

#ifdef WIN32
		Sleep(5);
#else
		sleep(10);
#endif
	}

	client_obj.Close(client_obj.GetLocalSock());
	getchar();
	return 0;
}