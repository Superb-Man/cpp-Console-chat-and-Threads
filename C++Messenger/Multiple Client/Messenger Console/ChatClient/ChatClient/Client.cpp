#include <iostream>
#include "Socket.h"
#include <string>
#include <sstream>
#include <WS2tcpip.h>
#include<thread>
#include <mutex>

#pragma comment (lib, "ws2_32.lib")


using namespace std;

mutex mu;

int port = 22;
string ip = "127.0.0.1";

class Client {

	string name;
	thread readthread;
	thread writethread;
	Socket* clientsocket;

public:

	Client(int port,string ip) {
		
		cout << "Enter the name : ";
		getline(cin, name) ;

		clientsocket = new Socket(port, ip);
		clientsocket->sendmessage(name);
		
		showmenu();
		start();
	}

	void start() {
		writethread = thread(&Client::write, this);
		readthread  = thread(&Client::read, this);
	}


	string getname() {
		return name;
	}

	void showmenu() {
		cout << "**************   1. Press 1 for sending message   ******\n";
		cout << "**************   2. Press 2 for broadcast message   ****\n";
		cout << "**************   3. Active Clientinfo   ****************\n";
	}

	void write() {
		string msg, option;
		while (true) {
			//try {
				
				lock_guard<mutex>lock(mu);
				getline(cin, option);

				if (option == "1") {

					cout << "Type the name of the receiver : ";
					string receiver;
					getline(cin, receiver);
					cout << "Meassage : ";
					getline(cin, msg);
					msg = "< " + receiver + " > " + msg;
					clientsocket->sendmessage(msg);
					cout << '\n';
					//showmenu();

				}
				else if (option == "2") {
					cout << "Meassage : ";
					getline(cin, msg);
					msg = "< Broadcast > " + msg;
					clientsocket->sendmessage(msg);
					cout << '\n';
					//showmenu();
				}
				else if (option == "3") {
					msg = "Show all active chats!";
					clientsocket->sendmessage(msg);
					//showmenu();
				}
			/* } catch (exception& e) {
				clientsocket->close();
				cout << "exiting" << endl;
				break;
			}*/
		}
	}

	void read() {
		while (true) {
			cout << clientsocket->readmessage() << std::endl;
		}
	}

	void stop() {
		readthread.join();
		writethread.join();
	}
};

int main() {
	Client client(port, ip);
	client.stop();

	cout << "Exiting";
	return 0;
}
