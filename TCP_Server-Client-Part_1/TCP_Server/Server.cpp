#include<iostream>
#include<ws2tcpip.h>
#include<sstream>
#include<thread>

using namespace std;

#pragma comment (lib, "ws2_32.lib") 
char buff[4096];
std::string userData;

void write(SOCKET& clientsock) {
	do {
		getline(cin, userData);
		int sendres = send(clientsock, userData.c_str(), userData.size() + 1, 0);
		if (sendres != SOCKET_ERROR) {
			/*ZeroMemory(buff, 4096);
			int byterec = recv(clientsock, buff, 4096, 0);
			if (byterec > 0) {
				//std::cout << "<Server> " << std::string(buff, 0, byterec) << std::endl;
			}
			else std::cout << "Errrrrr" << std::endl;*/
		}
	} while (userData.size() > 0);
}

void read(SOCKET& clientsock) {
	while (true) {
		memset(buff, 0, 4096);
		int byterec = recv(clientsock, buff, 4096, 0);
		if (byterec == SOCKET_ERROR) {
			std::cout << "Error in recieving " << std::endl;
			break;
		}
		if (byterec == 0) {
			std::cout << "Connected" << std::endl;
			break;
		}
		std::cout << "<Client> " << std::string(buff, 0, byterec) << std::endl;
		//send(clientsock, buff, byterec + 1, 0);

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


	SOCKET listening = socket(AF_INET, SOCK_STREAM, 0);
	if (listening == INVALID_SOCKET) {
		std::cerr << "Can't Create a Socket!" << std::endl;
		return;
	}


	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(22);
	server.sin_addr.S_un.S_addr = INADDR_ANY;

	bind(listening, (sockaddr*)&server, sizeof(server));

	listen(listening, SOMAXCONN);


	sockaddr_in client;
	int clientsize = sizeof(client);

	SOCKET clientsock = accept(listening, (sockaddr*)&client, &clientsize);

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


	std::thread readthreadserver(read, std::ref(clientsock));
	std::thread writethreadserver(write, std::ref(clientsock));


	readthreadserver.join();
	writethreadserver.join();


	closesocket(listening);
	closesocket(clientsock);

	WSACleanup();

 
}