/* 
    File: ai.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    WRITE SHIT ABOUT AI HERE

*/
#include <stdio.h>

#include "ai.h"

class AI::Board_state {
private:
	std::vector<std::vector<int> > board;
	int num_black;
	int num_yellow;
public:
	Board_state(std::string s): num_yellow(0), num_black(0) {
		std::stringstream ss;
		ss << s;
		board.resize(GRID_SIZE);
		for (int i = 0; i < GRID_SIZE; ++i) {
			board[i].resize(GRID_SIZE);
			for (int j = 0; j < GRID_SIZE; ++j) {
				std::string t;
				ss >> t;
				board[i][j] = atoi(t.c_str());
				std::cout << board[i][j];
			}
			std::cout << '\n';
		}
	}
};


unsigned int AI::compare(std::string a, std::string b) {
	//do work
	return 0;
}

void AI::create_tree(std::string state) {
	Board_state b = Board_state(state); //TESTING
	//do work
	return;
}

std::string AI::choose() {
	//do work

	return "dowork";
}

void AI::set_difficulty(unsigned int i) {
	if ( (i > 9) || (i < 0) ) {
		printf("ERROR : Difficulty not valid;\n");
		return;
	}
	difficulty = i;
}

void AI::set_ai_color(std::string ai_color)
{
	if(ai_color == "BLACK")
	{
		color = BLACK;
	
	}
	if(ai_color == "YELLOW")
	{
		color = YELLOW;
		
	}

}





















