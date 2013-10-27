/* 
    File: game_client.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang, Violeta Torres
            Department of Computer Science
            Texas A&M University
			
    This file contains the fuctions for the Game_Client which will communicate with the server 
	that is housing the application to play a game of Reversi

*/
#ifndef _GAME_CLIENT_
#define _GAME_CLIENT_


#include <string>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "game_state_engine.h"


class Game_Client {
private:
	Gamestate_Engine _e;
	int sockID;
public:

	
	Game_Client();
	
	bool send_cmd(std::string s);
	// Takes in the user command and sends it to the server	
	// The response from the server is printed out in this function to the main screen
	// The return value specifies if the game has ended and the connection should be termintated
	
	bool set_up_connection(int port);
	// Takes the port number entered by the user and attempts to connect. 	
	
	bool disconnect();
	// Close socket connection
	
	void run_gui();
	//runs gui
	
	bool send_message(std::string message); 
	//send message to server 
	
	std::string receive_message();
	//receive message from server
};

#endif
