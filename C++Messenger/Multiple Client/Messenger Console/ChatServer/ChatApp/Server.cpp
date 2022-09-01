#include <iostream>
#include<map>
#include<vector>
#include <string>
#include<thread>
#include "ServerSocket.h"


class Server {

	ServerSocket* serversocket;
	static int clientcount;
	std::thread* readthreadserver;
	std::vector<std::string>names;
	std::map<std::string, Socket> _activeclientmap;

public:

	Server(int port) {
		serversocket = new ServerSocket(port);
		readthreadserver = new std::thread[MAX_SOCKET];

		while (true) {

			Socket& clientsocket     = serversocket->acceptconnection();
			std::string _clientname  = serversocket->readmessage(clientsocket);
			_activeclientmap[_clientname] = clientsocket;
			names.push_back(_clientname);
			std::string welcmmsg = "Welcome!!! "+_clientname;
			serversocket->sendmessage(clientsocket,welcmmsg);
			std::cout <<"total entry : "<< ++clientcount << std::endl;
			readthreadserver[clientcount-1] = std::thread(&Server::serverresponse, this);
		}
	}

	void stop() {
		for (int i = 0; i < clientcount ;i++) {
			readthreadserver[i].join();
		}
	}

	std::string messagextractor(std::string& msg) {
		int lesser  = msg.find('<');
		int greater = msg.find('>');

		return std::string(msg,lesser + 2,greater-lesser-3);
	}

	void serverresponse() {

		int idx = clientcount - 1;
		Socket& receivingsocket = _activeclientmap[names[idx]];

		//try {
			while (true) {

				std::string msgrecvd = serversocket->readmessage(receivingsocket);
				if (msgrecvd == "Error in receiving") {

					std::cout << names[idx] << " left !" << '\n';

					_activeclientmap.erase(names[idx]);


					//exit(1);
					break;
				}

				std::map<std::string, Socket> ::iterator it = _activeclientmap.begin();

				std::cout << "< " + names[idx] + " >" + msgrecvd << std::endl;

				if (msgrecvd == "Show all active chats!") {
					msgrecvd = "";
					while(it!=_activeclientmap.end()) {

						msgrecvd += "{ " + it->first + " }";
						it++;
					}
					serversocket->sendmessage(_activeclientmap[names[idx]], msgrecvd);
				}

				else if (messagextractor(msgrecvd) == "Broadcast") {

					msgrecvd.erase(0, msgrecvd.find('>') + 2);
					while(it!=_activeclientmap.end()) {

						if (receivingsocket == _activeclientmap[it->first]) {
							it++;
							continue;
						}
						else {
							serversocket->sendmessage(_activeclientmap[it->first], names[idx] + ": " + msgrecvd);
							it++;
						}
					}
				}

				else {
					
					std::string receiver = messagextractor(msgrecvd);
					msgrecvd.erase(0, msgrecvd.find('>') + 2);
					
					if (_activeclientmap.find(receiver) == _activeclientmap.end()) {
						serversocket->sendmessage(_activeclientmap[names[idx]], std::string("Sorry ,User may be Not Connected"));
					}
					else {
						serversocket->sendmessage(_activeclientmap[receiver], names[idx] + ": " + msgrecvd);
					}
				}


			}
		//}
		//catch (std::exception& e) {

		//}

	}
};

int Server::clientcount = 0;

int main() {
	
	Server server(22);
	server.stop();

}

