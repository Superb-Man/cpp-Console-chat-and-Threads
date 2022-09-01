#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include<ws2tcpip.h>
#include<sstream>
#include<thread>

using namespace std;
#pragma comment (lib, "ws2_32.lib") 

char buff[4096];
std::string userData;

void write(SOCKET& sock,sockaddr_in& server) {
	do {
		getline(cin, userData);
		int len = sizeof(server);
		int sendres = sendto(sock, userData.c_str(), userData.size() + 1, 0,(sockaddr*)&server,len);
		if (sendres != SOCKET_ERROR) {
			
		}
	} while (userData.size() > 0);
}

void read(SOCKET& sock,sockaddr_in& server) {
	while (true) {
		memset(buff, 0, 4096);
		int len = sizeof(server);
		int byterec = recvfrom(sock, buff, 4096, 0,(sockaddr*)&server,&len);

		if(byterec > 0) std::cout << "<Server> " << std::string(buff, 0, byterec) << std::endl;

	}
}

void main() {
	std::string address = "127.0.0.1";
	int port = 22;


	WSADATA Data;
	WORD ver = MAKEWORD(2, 2);

	int winresult= WSAStartup(ver, &Data);
	if (winresult != 0){
		std::cout << "Can't Initialize !" << std::endl;
		return;
	}


	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);;
	if (sock == INVALID_SOCKET) {

		std::cout << "Can't Create a Socket!" << std::endl;
		WSACleanup();
		return;
	}


	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");


	std::thread readthreadclient(read, std::ref(sock),ref(server));
	std::thread writethreadclient(write, std::ref(sock),ref(server));

	readthreadclient.join();
	writethreadclient.join();



	closesocket(sock);

	WSACleanup();



}