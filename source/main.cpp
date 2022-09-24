#include "../includes/server.h"
#include "../includes/client.h"


using namespace std::literals::chrono_literals;

void serverStuff(){
	server theServer(10021);
	theServer.openServer();
	theServer.stablishConnetion();
	// theServer.handleClient();
}

void clientStuff(){
	std::string theIp = "192.168.0.191";
	client theClient(10021,theIp);
	theClient.connectClient();
	theClient.sendMessage();	
}

int main(int argc, char const *argv[]){
	

	std::thread serverHandler(serverStuff);
	
	std::this_thread::sleep_for(1s);
	
	std::thread clientHandler(clientStuff);

	serverHandler.join();
	clientHandler.join();



	return 0;
}