#include "../includes/server.h"

using namespace std::literals::chrono_literals;

server::server(int thePort){
	this->port = thePort;
}

bool server::openServer(){
	std::cout <<"Using port: " << this->port << std::endl;
	// Open socket
	if((this->serverSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0){
		std::cout << "Failed to open server socket" << std::endl;
	}

	// build sockaddr_in
	memset(&(this->serverAddr), 0, sizeof(this->serverAddr));
	this->serverAddr.sin_family = AF_INET;
	this->serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	this->serverAddr.sin_port = htons(this->port);

	// Bind
	if(bind(this->serverSocket, (struct sockaddr *) &(this->serverAddr), sizeof(this->serverAddr)) < 0){
		std::cout << "Failed to bind" << std::endl;
		return false;
	}

	// Listen
	if(listen(this->serverSocket, 10) < 0){
		std::cout << "Listen Failed" << std::endl;
		return false;
	}
	return true;
}

bool server::stablishConnetion(){

	unsigned int clientLength;
	int socketClient;
	
	std::cout << "Listening" << std::endl;
	clientLength = sizeof(this->clientAddr);
	if((socketClient = accept(this->serverSocket, (struct sockaddr *) &(this->clientAddr), &clientLength)) < 0){
		std::cout << "Failed at accept" << std::endl;
		return false;
	}

	this->theClientSocket = socketClient;
		
	std::cout << "Connect to client %s"<< inet_ntoa(this->clientAddr.sin_addr) << std::endl;
	
	for (int i = 0; i < 1; ++i){
		this->handleClient(socketClient);
	}

	close(socketClient);
	close(this->serverSocket);
	return true;
}

void server::handleClient(int socketClient) {
	int* buffer = new(int[256]);
	int recievedLength;

	recievedLength = recv(socketClient, buffer, 256, 0);
	std::cout << "Recieved: " << recievedLength << std::endl;
	for (int i = 0; i < 4; ++i){
		std::cout << "buffer: " << i << "  "<<buffer[i] << std::endl; 
	}
}