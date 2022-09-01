#pragma once

#include <string>
#include <WS2tcpip.h>
#include"Socket.h"

#define MAX_SOCKET 100

#pragma comment (lib, "ws2_32.lib")



class ServerSocket {

	WSADATA		    wsdata;
	struct sockaddr_in  serverinf;
	int		    listeningsocket;
	Socket*		    clientsock;
	static int	    clientsockcnt;
	int create(int);

public:

	ServerSocket(); 
	ServerSocket(int);
	void close(); 
	bool initializeWinsock();
	Socket& acceptconnection();
	void sendmessage(Socket& , std::string);
	std::string readmessage(Socket&);
};
