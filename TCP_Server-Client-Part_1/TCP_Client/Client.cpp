#include<iostream>
#include<ws2tcpip.h>
#include<sstream>
#include<thread>

using namespace std;
#pragma comment (lib, "ws2_32.lib") 

char buff[4096];
std::string userData;

void write(SOCKET& sock) {
	do {
		getline(cin, userData);
		int sendres = send(sock, userData.c_str(), userData.size() + 1, 0);
		if (sendres != SOCKET_ERROR) {
			/*ZeroMemory(buff, 4096);
			int byterec = recv(sock, buff, 4096, 0);
			if (byterec > 0) {
				//std::cout << "<Server> " << std::string(buff, 0, byterec) << std::endl;
			}
			else std::cout << "Errrrrr" << std::endl;*/
		}
	} while (userData.size() > 0);
}

void read(SOCKET& sock) {
	while (true) {
		memset(buff, 0, 4096);
		int byterec = recv(sock, buff, 4096, 0);
		if (byterec == SOCKET_ERROR) {
			std::cout << "Error in recieving " << std::endl;
			break;
		}
		if (byterec == 0) {
			//std::cout << "Connected" << std::endl;
			//break;
		}
		std::cout << "<Server> " << std::string(buff, 0, byterec) << std::endl;
		//send(sock, buff, byterec + 1, 0);

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


	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) {

		std::cout << "Can't Create a Socket!" << std::endl;
		WSACleanup();
		return;
	}


	sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(port);
	inet_pton(AF_INET, address.c_str(), &server.sin_addr);

	int conn = connect(sock, (sockaddr*)&server, sizeof(server));

	if (conn == SOCKET_ERROR) {
		std::cout << "ERRRRRRRR" << std::endl;
		closesocket(sock);
		WSACleanup();
		return;
	}

	std::thread readthreadclient(read, std::ref(sock));
	std::thread writethreadclient(write, std::ref(sock));

	readthreadclient.join();
	writethreadclient.join();



	closesocket(sock);

	WSACleanup();



}