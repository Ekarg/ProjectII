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

class Game_Client {
private:


public:
	
	bool send_cmd(std::string s);
	// Takes in the user command and sends it to the server	
	// The response from the server is printed out in this function to the main screen
	// The return value specifies if the game has ended and the connection should be termintated
	
	bool connect(int port);
	// Takes the port number entered by the user and attempts to connect. 	
	
	bool disconnect();
	// Close socket connection
	
	void run_gui();
	//runs gui
	
};

#endif
