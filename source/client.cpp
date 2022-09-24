#include "../includes/client.h"
#include <chrono>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace std::literals::chrono_literals;

client::client(int thePort,std::string ipServer){
	this->port = thePort;
	this->serverIp = ipServer;
}


void client::connectClient(){
	struct sockaddr_in serverAddr;

	//Create socket
	if((this->clientSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		std::cout << "Socket error" << std::endl;
	}

	//Build struct sockaddr_in
	memset(&serverAddr, 0, sizeof(serverAddr)); // Zerando a estrutura de dados
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = inet_addr(this->serverIp.c_str());
	serverAddr.sin_port = htons(this->port);

	// Connect
	if(connect(this->clientSocket, (struct sockaddr *) &serverAddr, 
							sizeof(serverAddr)) < 0){
		std::cout << this->serverIp << std::endl;
		perror("Error to connect");
		std::cout <<"Error to connect"<< std::endl;
	}
}

void client::sendMessage(){
	message = new(int[4]);

	message[0] = 1;
	message[1] = 33;
	message[2] = 55;
	message[3] = 1234;
	
	send(this->clientSocket,message,256,0);
	
	std::this_thread::sleep_for(1s);
	
	// recv(theClient.clientSocket, &recievedMessage, 16, 0);
	// std::cout << "Recieve message from sever 1" << std::endl;
	return;
}