
#include "ServerSocket.h"
#include <iostream>
#include <string>
#include <sstream>

int ServerSocket::clientsockcnt = 0;


ServerSocket::ServerSocket() {
	//Nothing
}


ServerSocket::ServerSocket(int port){

	this->clientsock = new Socket[MAX_SOCKET];
	initializeWinsock();
	this->listeningsocket = create(port);
}

void ServerSocket::close() {
	delete[] clientsock;
	WSACleanup();
}

bool ServerSocket::initializeWinsock() {
	WORD ver = MAKEWORD(2, 2);

	int winsock = WSAStartup(ver, &wsdata);

	if (winsock != 0) {
		std::cout << "Error: can't initialize Winsock." << std::endl; 
		return false;
	}

	return true;
}


int ServerSocket::create(int port) {

	int listening = socket(AF_INET, SOCK_STREAM, 0);//SOCKET can be used instead of int

	if (listening == INVALID_SOCKET) {
		std::cout << "Can't Create a Socket!" << std::endl;
		return false;
	}

	serverinf.sin_family = AF_INET;
	serverinf.sin_port = htons(port);
	serverinf.sin_addr.S_un.S_addr = INADDR_ANY;



	int binding = bind(listening, (sockaddr*)&serverinf, sizeof(serverinf));

	if (binding != SOCKET_ERROR) {
		int listeningchk = listen(listening, SOMAXCONN); //SOCKET can be used instead of int
		if (listeningchk == SOCKET_ERROR) {
			return false;
		}
	}

	else return false;

	return listening;
}


Socket& ServerSocket::acceptconnection() {

	(clientsock+clientsockcnt)->sock = accept(listeningsocket,nullptr,nullptr);
	//
	//std::cout << "Connnnnected" << std::endl;
	return clientsock[clientsockcnt++];
}

void ServerSocket::sendmessage(Socket& clientsock, std::string msg) {
	send(clientsock.sock, msg.c_str(), msg.length()+1, 0);
}

std::string ServerSocket::readmessage(Socket& clientsock) {

	std::string msg;
	char buff[MAX_SIZE];
	ZeroMemory(buff, MAX_SIZE);
	int cnt = clientsockcnt - 1;
	int byterec = recv(clientsock.sock, buff, sizeof(buff), 0);
	//int byterec = recv(clientsock[i].sock, buff, sizeof(buff), 0);
	if (byterec == SOCKET_ERROR) {
		return "Error in receiving";
	}
	else {
		msg = std::string(buff, 0, byterec);
		return msg;
	}

}

