/*
    File: test_main.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    THIS FILE CONTAINS UNIT TESTS FOR CLASS MEMBER FUNCTIONS
	OF THE CLASS Game_Server. THIS MAIN DOES NOT DO ANYTHING
	RELEVANT IN TERMS OF THE REVERSI PROJECT. 

*/

#include "game_server.h"

int main() {
	
	
	Game_Server _s = Game_Server();
	std::string query = "";
	bool run = true;
	std::cout << "Welcome" << "\t\t\t ;chose side (YELLOW/BLACK)" <<std::endl; 
	while(run)
	{
		std::cin >> query; 
		if(query == "EXIT")
		{
			run = false;
		}
		 _s.parse_cmd(query);
	}
	return 0;
}