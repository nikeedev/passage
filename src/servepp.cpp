// httpp.cpp : Defines the entry point for the application.
//

#include "servepp.h"

namespace servepp
{
	void init_server(std::string_view &address, int port)
	{
		WSADATA wsaData;
		int wsaerr;
		WORD wVersionRequested = MAKEWORD(2, 2);
		wsaerr = WSAStartup(wVersionRequested, &wsaData);
		// WSAStartup resturns 0 if it is successfull or non zero if failed
		if (wsaerr != 0)
		{
			std::cout << "The Winsock dll not found!" << endl;
			return 0;
		}
		else
		{
			cout << "The Winsock dll found" << endl;
			cout << "The status: " << wsaData.szSystemStatus << endl;
		}

		/*
		refer ServerCreation.md
		*/
		SOCKET serverSocket;
		serverSocket = INVALID_SOCKET; // initializing as a inivalid socket
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		// check if creating socket is successfull or not
		if (serverSocket == INVALID_SOCKET)
		{
			cout << "Error at socket():" << WSAGetLastError() << endl;
			WSACleanup();
			return 0;
		}
		else
		{
			cout << "socket is OK!" << endl;
		}

		/*
		3. Bind the socket to ip address and port number
		//refer ServerCreation.md
		*/
		sockaddr_in service; // initialising service as sockaddr_in structure
		service.sin_family = AF_INET;
		// InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
		// InetPton function is encountering an issue, so replaced with the following line which uses inet_addr to convert IP address string to the binary form (only for ipv4) and storing it
		service.sin_addr.s_addr = inet_addr("127.0.0.1");
		//    service.sin_addr.s_addr = inet_addr("192.168.43.42");
		service.sin_port = htons(55555);
		// using the bind function
		if (bind(serverSocket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR)
		{
			cout << "bind() failed: " << WSAGetLastError() << endl;
			closesocket(serverSocket);
			WSACleanup();
			return 0;
		}
		else
		{
			cout << "bind() is OK!" << endl;
		}
	}
}
