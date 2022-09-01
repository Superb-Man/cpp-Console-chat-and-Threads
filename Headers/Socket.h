#pragma once

#include <string>
#include <WS2tcpip.h>

#define MAX_SIZE 4096

#pragma comment (lib, "ws2_32.lib")

class Socket {

	WSADATA		wsdata;
	struct		sockaddr_in serverinf;
	int		sock;
	int create(int, std::string);

	friend class	ServerSocket;

public:

	Socket();
	Socket(int, std::string);
	void close();
	bool initializeWinsock();
	bool operator==(Socket&);
	void sendmessage(std::string);
	std::string readmessage();
};

