// httpp.cpp : Defines the entry point for the application.
//

#include "servepp.h"

namespace servepp
{
	Server::Server()
		: serverSocket(INVALID_SOCKET), acceptSocket(INVALID_SOCKET)
	{
		// Any additional initialization can be added here
	}

	void Server::init_server(const char *address, int port)
	{
		WSADATA wsaData;
		int wsaerr;
		WORD wVersionRequested = MAKEWORD(2, 2);
		wsaerr = WSAStartup(wVersionRequested, &wsaData);
		// WSAStartup resturns 0 if it is successfull or non zero if failed
		if (wsaerr != 0)
		{
			fmt::println("The Winsock dll not found!");
			exit(0);
		}
		else
		{
			fmt::println("The Winsock dll found");
			fmt::println("The status: ", wsaData.szSystemStatus);
		}

		/*
		refer ServerCreation.md
		*/
		serverSocket = INVALID_SOCKET; // initializing as a inivalid socket
		serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		// check if creating socket is successfull or not
		if (serverSocket == INVALID_SOCKET)
		{
			fmt::println("Error at socket(): {}", WSAGetLastError());
			WSACleanup();
			exit(0);
		}
		else
		{
			fmt::println("socket is OK!");
		}

		/*
		3. Bind the socket to ip address and port number
		//refer ServerCreation.md
		*/
		sockaddr_in service; // initialising service as sockaddr_in structure
		service.sin_family = AF_INET;
		if (InetPton(AF_INET, address, &service.sin_addr) != 1)
		{
			fmt::println("Invalid IP address: {}", address);
			closesocket(serverSocket);
			WSACleanup();
			exit(0);
		}
		//    service.sin_addr.s_addr = inet_addr("192.168.43.42");
		service.sin_port = htons(port);
		// using the bind function
		if (bind(serverSocket, (SOCKADDR *)&service, sizeof(service)) == SOCKET_ERROR)
		{
			fmt::println("bind() failed: {}", WSAGetLastError());
			closesocket(serverSocket);
			WSACleanup();
			exit(0);
		}
		else
		{
			fmt::println("bind() is OK!");
		}
	}

	void Server::listen_server()
	{
		// 4. Listen to incomming connections
		if (listen(serverSocket, 1) == SOCKET_ERROR)
		{
			fmt::println("listen(): Error listening on socket: {}", WSAGetLastError());
		}
		else
		{
			fmt::println("listen() is OK!, I'm waiting for new connections...");
		}

		// 5. accepting incomming connections
		acceptSocket = accept(serverSocket, NULL, NULL);
		if (acceptSocket == INVALID_SOCKET)
		{
			fmt::println("accept failed: {}", WSAGetLastError());
			WSACleanup();
			exit(-1);
		}
		else
		{
			fmt::println("accept() is OK!");
		}
	}

	void Server::send_buffer(char *buffer)
	{
		int sbyteCount = send(acceptSocket, buffer, (int)strlen(buffer), 0);
		if (sbyteCount == SOCKET_ERROR)
		{
			fmt::println("Server send error: {}", WSAGetLastError());
			exit(-1);
		}
		else
		{
			fmt::println("Server: sent {}", sbyteCount);
		}
		closesocket(acceptSocket);
	}

	void Server::recieve_buffer(char* buffer)
	{
		int rbyteCount = recv(acceptSocket, buffer, 1000, 0);
		if (rbyteCount < 0)
		{
			fmt::println("Server recv error: {}", WSAGetLastError());
			exit(0);
		}
		else
		{
			fmt::println("Received data!");
		}
		closesocket(acceptSocket);
	}
}
