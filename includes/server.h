#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "tcpProtocol.h"
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <chrono>
#include <thread>

class server : public tcpProtocol {
public:

	int theClientSocket;
	int serverSocket;
	
	server(int thePort);

	bool openServer();
	bool stablishConnetion();
	void handleClient(int socketCliente);
	bool resetTimes();
	void closeServer();

};

#endif //EVENTHANDLER_H