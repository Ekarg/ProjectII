/* 
    File: main.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    *---* DESCRIPTION *---*

*/



#include "game_server.h"
#include "global_const.h"

int main() {
	Game_Server server = Game_Server();
	server.run();
	return true;
}