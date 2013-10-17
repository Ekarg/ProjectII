/* 
    File: ai.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
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
	std::vector<std::vector<int> > get_board() {
		return board;
	}
};


unsigned int AI::compare(std::string a, std::string b) {
	//do work
	return 0;
}

void AI::create_tree(std::string state) {
	Board_state b = Board_state(state); //TESTING
	_board = b.get_board();
	//do work
	return;
}

std::string AI::chooseHard() {

	return "do work\n";
}

std::string AI::chooseMedium() {

	return "do work\n";
}

std::string AI::chooseEasy() {
	std::vector<int> x_cor;
	std::vector<int> y_cor;
	
	std::stringstream ssx;
	std::stringstream ssy;
	std::string s = "";
	std::cout<<"IN CHOOSE()\n";
	//std::cout<<_board.size()<<std::endl;
	//std::cout<<_board[0].size()<<std::endl;
	if(color == YELLOW) {
		for(int y = 0; y < GRID_SIZE; y++)
			for(int x = 0; x < GRID_SIZE; x++) {
				if(_board[y][x] == LEGAL_YELLOW || _board[y][x] == LEGAL_BOTH) {
					x_cor.push_back(x); 
					y_cor.push_back(y);
				}			
		}
		std::cout<<"After loop\n";
		srand (time(NULL));
		int m = rand() % (x_cor.size());
		//set_color("BLACK");
		//ai_move(y_cor[m], x_cor[m]);
		//set_color("YELLOW");
		std::string a;	
	
		ssy << y_cor[m];
		ssy >> a;
		std::cout<<a<<std::endl;
		s += a;
		
		ssx << x_cor[m];
		ssx >> a;
		s += a;
		std::cout<<a<<std::endl;
		return s;
	}
	
	
	
	else {
		for(int y = 0; y < GRID_SIZE; y++)
			for(int x = 0; x < GRID_SIZE; x++) {
				if(_board[y][x] == LEGAL_BLACK || _board[y][x] == LEGAL_BOTH) {
					x_cor.push_back(x); 
					y_cor.push_back(y);
				}
			}
			srand (time(NULL));
			int m = rand() % (x_cor.size());			
			std::string a;	
			
			ssy << y_cor[m];
			ssy >> a;
			std::cout<<a<<std::endl;
			s += a;
			
			ssx << x_cor[m];
			ssx >> a;
			s += a;
			std::cout<<a<<std::endl;
			
			
			return s;
	}
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





















