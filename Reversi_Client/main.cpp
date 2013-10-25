/* 
    File: main.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang, Violeta Torres
            Department of Computer Science
            Texas A&M University
			
    This file contains the main function that will handle the start up of the Game_Client

*/
#include "game_client.h"

int main(int argc, char* argv[])
{
	//Initialize game_server
	
	//begin accepting user inputs and use game client to send
	
	//if exit command is processed by game_client, break from while loop
	
	Game_Client _gc;
	std::cout<<"Please enter port number.\n";
	int port;
	std::cin>>port;
	_gc.set_up_connection(port);
	_gc.run_gui();
	return 0;

}