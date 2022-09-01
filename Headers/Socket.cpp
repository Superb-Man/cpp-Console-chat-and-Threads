#include "Socket.h"
#include <iostream>
#include <string>
#include <sstream>


Socket::Socket() {

}

Socket::Socket(int port, std::string ip_address) {
	initializeWinsock();
	this->sock = create(port, ip_address);
	int conn = connect(this->sock, (sockaddr*)&serverinf, sizeof(serverinf));//SOCKET can be used instead of int

	if (conn == SOCKET_ERROR) {
		std::cout << "Error: can't connect to server.\n";
		closesocket(sock);
		WSACleanup();
	}
	else if (conn != SOCKET_ERROR)
		std::cout << "Connected to server" << std::endl;
}

void Socket::close() {

	closesocket(sock);
	WSACleanup();
}


bool Socket::initializeWinsock() {
	WORD ver = MAKEWORD(2, 2);

	int winsock = WSAStartup(ver, &wsdata);

	if (winsock != 0) {
		std::cout << "Error: can't initialize Winsock." << std::endl;
		return false;
	}

	return true;
}

int Socket::create(int port, std::string ip_address) {
	int client = socket(AF_INET, SOCK_STREAM, 0);

	if (client == INVALID_SOCKET) {
		std::cout << "Can't Create a Socket!" << std::endl;
		return -1;
	}

	serverinf.sin_family = AF_INET;
	serverinf.sin_port = htons(port);
	inet_pton(AF_INET, ip_address.c_str(), &serverinf.sin_addr);

	return client;

}

bool Socket::operator==(Socket& s) {

	return s.sock == this->sock;
}

void Socket::sendmessage(std::string msg) {
	send(sock, msg.c_str(), msg.length() + 1, 0);
}

std::string Socket::readmessage() {
	std::string msg;
	char buff[MAX_SIZE];
	ZeroMemory(buff, MAX_SIZE);
	int byterec = recv(sock, buff, sizeof(buff), 0);

	if (byterec <= 0) {
		closesocket(sock);
		WSACleanup();
	}

	else {
		msg = std::string(buff, 0, byterec);
	}

	return msg;
}
