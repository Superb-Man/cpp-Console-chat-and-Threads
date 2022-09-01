#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<iostream>
#include<ws2tcpip.h>
#include<sstream>
#include<thread>

using namespace std;

#pragma comment (lib, "ws2_32.lib") 
char buff[4096];
std::string userData;

void write(SOCKET& listening,sockaddr_in& client ) {
	do {
		getline(cin, userData);
		int clientsize = sizeof(client);
		int sendres = sendto(listening, userData.c_str(), userData.size() + 1, 0,(sockaddr*)&client,clientsize);
		if (sendres != SOCKET_ERROR) {
			
		}
	} while (userData.size() > 0);
}

void read(SOCKET& listening,sockaddr_in& client) {
	while (true) {
		memset(buff, 0, 4096);
		int clientsize = sizeof(client);
		int byterec = recvfrom(listening, buff, 4096, 0,(sockaddr*)&client,&clientsize);
		if (byterec == SOCKET_ERROR) {
			std::cout << "Error in recieving " << std::endl;
			break;
		}
		if (byterec == 0) {
			std::cout << "Connected" << std::endl;
			break;
		}
		std::cout << "<Client> " << std::string(buff, 0, byterec) << std::endl;

	}
}

void main(){
	WSADATA wsData ;
	WORD ver = MAKEWORD(2, 2);
	
	int winsock = WSAStartup(ver, &wsData);
	if (winsock  != 0) {
		std::cerr << "Can't Initialize !" << std::endl;
		return;
	}


	SOCKET listening = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (listening == INVALID_SOCKET) {
		std::cerr << "Can't Create a Socket!" << std::endl;
		return;
	}


	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(22);
	server.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

	bind(listening, (sockaddr*)&server, sizeof(server));

	sockaddr_in client;


	char host[NI_MAXHOST];
	char service[NI_MAXHOST];

	memset(host, 0, NI_MAXHOST); //ZeroMemory(host, NI_MAXHOST);
	memset(service, 0, NI_MAXHOST);

	if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0) {
		std::cout << host << "connected on port " << service << std::endl;
	}
	else {
		inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
		std::cout << host << "Connected on port " << ntohs(client.sin_port) << std::endl;
	}


	std::thread readthreadserver(read, std::ref(listening),ref(client));
	std::thread writethreadserver(write, std::ref(listening),ref(client));


	readthreadserver.join();
	writethreadserver.join();


	closesocket(listening);

	WSACleanup();

 
}