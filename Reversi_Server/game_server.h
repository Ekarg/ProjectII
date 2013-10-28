/* 
    File: game_server.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the Game_Server class that manages
	the communication between client-server and directs the
	Gamestate_Engine for the Reversi project. 

*/

#ifndef _Game_Server_
#define _Game_Server_

#include "global_const.h"
#include "game_state_engine.h"
#include "ai.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class Game_Server {
private:
	Gamestate_Engine _e;
	// Primary engine that simulates the current game being played
	// Current implementation does NOT suppose multi-game without the
	// spawn of a new Game_Server object.
	
	AI _ai;
	// AI that should be used with the Gamestate_Engine _e in 
	// the event that the user plays against AI.

	int clientID;
	
	int aiID;
public:
	Game_Server();
	// Default Constructor sets up initial conditions
	
	void setup_ai(unsigned int difficulty);
	// If AI mode is chosen, this function is called.
	// Initializes _ai as well as set difficulty.
	
	void ai_play(); 
	//indicates to AI it is it's turn to play 
	
	void run();
	// Server client interface is handled in here. Server makes a
	// socket, binds socket to port, and then listens for connections
	// made to port. List of file descriptors is kept to manage 
	// multiple connections to the server. Communication between the
	// server and client are managed. Incoming messages are handled 
	// while string representations of the gamestate are sent. 
	// TCP rather than UDP seems to be the best solution.
	// Communication in should look something like the following...
	// reply(parse_cmd(input));
	
	unsigned int parse_cmd(std::string s);
	// Parses command and calls associated function.
	// Returns an int that maps to a reply for reply function.
	// DISPLAY - Handled in GUI????
	// RANDOM | EASY | MEDIUM | HARD | GOSUSWAG
	// 		- Handled with _ai.set_difficulty();
	// YELLOW | BLACK
	//		- Handled by setting _e.player_color to choice
	//		- and _ai.color to other color
	// UNDO - Handled with _e.undo_move();
	// HUMAN-AI - Handled with setup_ai(x); where x = random or 0
	// AI-AI - Handled by setting up AI and treating other AI as client
	// 		- ?????????? Maybe ????????
	
	int parse_move(std::string move);
	//parse the users move to check validity 
	
	std::string reply(int i);
	// Given an int, replies with cooresponding message
	// as well as gamestate update. 
	
	void exit();
	// Obvious.
	
	void set_up_AI_connection();
	
	
	void Default_Setup();
	//default game 

	
};

#endif


