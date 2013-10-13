#include "game_server.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
int main() {
	Game_Server server = Game_Server();
	int port = 4001;
	int sockID;
	 socklen_t clilen;
     char buffer[256];
     struct sockaddr_in serv_addr;
	 struct sockaddr *addr;
     unsigned int n = 100;
	 int connectID;
	 if( (sockID = socket(AF_INET, SOCK_STREAM, 0)) <0 ) {
		printf("Error creating socket\n");
		return false;
	 }
	 serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(port);
     if (bind(sockID, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        printf("Error while binding");
		return false;
	}
    if(listen(sockID, 1) < 0) {
		printf("Error while listening");
		return false;
	}
	connectID = accept(sockID, addr, &n);
	std::string welcome = "WELCOME\n";
	if( send(connectID, welcome.c_str(), welcome.length(), 0) < 0) {
		printf("Error sending.\n");
		return false;	
	}
	char * buf = new char[500];
	while(true) {
		int length = recv(connectID, buf, 500, 0);
		if(length < 0) {
			printf("Error receiving message.\n");
			break;
		}
		if(length > 0) {
			std::string message = std::string(buf);
			int response_num = server.parse_cmd(message);
			std::string response = server.reply(response_num);
			if( send(connectID, response.c_str(), response.length(), 0) < 0){
				printf("Error sending.\n");
				break;		
			} 
			if(message.find("EXIT") != std::string::npos) 
				break;
		}
	}	
	if( shutdown(connectID, 2) < 0)  {
		printf("Error shutting down connection.\n");
		return false;
	}
	if( close(connectID) < 0) {
		printf("Error closing connection.\n");
		return false;
	}
	return true;
}