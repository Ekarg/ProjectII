/* 
    File: ai.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    WRITE SHIT ABOUT AI HERE

*/
#include <stdio.h>

#include "ai.h"
#include "Position.h"

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
string AI::convert(int x, int y)
 {
 std::string s = ""; 
	std::stringstream ss;
	ss << x;
	ss >> s;
	//Quick and dirty: Never ever ever ever do this.
	s += (char)(y+97);
	//Quick and dirty: Never ever ever ever do this.
	return s;
}

unsigned int AI::compare(std::string a, std::string b) {
	//do work
	return 0;
}

void AI::create_tree(std::string state) {
	
	Board_state b = Board_state(state); //TESTING
	printf("tree created\n");
	_board = b.get_board();
	_board_c.resize(GRID_SIZE);
	for (int i = 0; i < GRID_SIZE; ++i) 
	{
		_board_c[i].resize(GRID_SIZE);
				for (int j = 0; j < GRID_SIZE; ++j) 
				{
					if(_board[i][j] == 0) {_board_c[i][j] = EMPTY;}
					else if(_board[i][j] == 1) {_board_c[i][j] = YELLOW;}
					else if(_board[i][j] == 2) {_board_c[i][j] = BLACK;}
					else if(_board[i][j] == 3) {_board_c[i][j] = LEGAL_YELLOW;}
					else if(_board[i][j] == 4) {_board_c[i][j] = LEGAL_BLACK;}
					else if(_board[i][j] == 5) {_board_c[i][j] = LEGAL_BOTH;}
				}
		}
	
	//do work
	return;
}

std::string AI::chooseHard() {
// check what color the AI is??
// need help figuring out what the color is for the AI 


//default color is black for now 
// runs for AI being black 
 std::vector<Position>old_values; 
 std::vector<Position>new_values;
 std::vector<std::vector<State> >new_board; 
 int letter;
 int number; 
 string temp = ""; 
 
 
 	if(get_color() == 2) // ai is black 
	{
		for (int i = 0; i < GRID_SIZE; ++i) 
		{
			for (int j = 0; j < GRID_SIZE; ++j) 
			{
				if(_board_c[i][j] == LEGAL_BLACK)
				{
					old_values.push_back(Position(i,j,_board_c[i][j])); 
				}
			}
		}
			
		new_board = gt.alphaBeta(_board_c, BLACK, -60, 60, 6);
			 		
		for (int i = 0; i < GRID_SIZE; ++i) 
		{
			for (int j = 0; j < GRID_SIZE; ++j)
			{
				if(new_board[i][j] == BLACK)
				{
					new_values.push_back(Position(i,j,new_board[i][j])); 
				}
			}
	
		}
		// this will check if the values are the same 		
		for(int g = 0; g<new_values.size(); g++)
		{
			for(int n = 0; n<old_values.size(); n++)
			{
				 if(new_values[g].getColum() == old_values[n].getColum() && new_values[g].getRow() == old_values[n].getRow() )
				 { 
				  // new move 
				  letter = new_values[g].getColum(); 
				  number = new_values[g].getRow();
				  
				 }
			}
		
		}
	}
	
	if(get_color() == 1) // ai is yellow
	{
		for (int i = 0; i < GRID_SIZE; ++i) 
		{
			for (int j = 0; j < GRID_SIZE; ++j) 
			{
				if(_board_c[i][j] == LEGAL_YELLOW)
				{
					old_values.push_back(Position(i,j,_board_c[i][j])); 
				}
			}
		}
			
		new_board = gt.alphaBeta(_board_c, YELLOW, -60, 60, 6);
			 		
		for (int i = 0; i < GRID_SIZE; ++i) 
		{
			for (int j = 0; j < GRID_SIZE; ++j)
			{
				if(new_board[i][j] == YELLOW)
				{
					new_values.push_back(Position(i,j,new_board[i][j])); 
				}
			}
	
		}
		// this will check if the values are the same 		
		for(int g = 0; g<new_values.size(); g++)
		{
			for(int n = 0; n<old_values.size(); n++)
			{
				 if(new_values[g].getColum() == old_values[n].getColum() && new_values[g].getRow() == old_values[n].getRow() )
				 { 
				  // new move 
				  letter = new_values[g].getColum(); 
				  number = new_values[g].getRow();
				  
				 }
			}
		
		}
	}
	 
	temp = convert(number,letter);
	
	std::cout<<" AI Move = "<<temp<<std::endl; 

	return temp;
}

std::string AI::chooseMedium() {

 std::vector<Position>old_values; 
 std::vector<Position>new_values;
 std::vector<std::vector<State> >new_board; 
 int letter;
 int number; 
 string temp = ""; 
 
if(get_color() == 2) // ai is black 
	{
		for (int i = 0; i < GRID_SIZE; ++i) 
		{
			for (int j = 0; j < GRID_SIZE; ++j) 
			{
				if(_board_c[i][j] == LEGAL_BLACK)
				{
					old_values.push_back(Position(i,j,_board_c[i][j])); 
				}
			}
		}
			
		new_board = gt.alphaBeta(_board_c, BLACK, -40, 40, 4);
			 		
		for (int i = 0; i < GRID_SIZE; ++i) 
		{
			for (int j = 0; j < GRID_SIZE; ++j)
			{
				if(new_board[i][j] == BLACK)
				{
					new_values.push_back(Position(i,j,new_board[i][j])); 
				}
			}
	
		}
		// this will check if the values are the same 		
		for(int g = 0; g<new_values.size(); g++)
		{
			for(int n = 0; n<old_values.size(); n++)
			{
				 if(new_values[g].getColum() == old_values[n].getColum() && new_values[g].getRow() == old_values[n].getRow() )
				 { 
				  // new move 
				  letter = new_values[g].getColum(); 
				  number = new_values[g].getRow();
				  
				 }
			}
		
		}
	}
	
	if(get_color() == 1) // ai is yellow
	{
		for (int i = 0; i < GRID_SIZE; ++i) 
		{
			for (int j = 0; j < GRID_SIZE; ++j) 
			{
				if(_board_c[i][j] == LEGAL_YELLOW)
				{
					old_values.push_back(Position(i,j,_board_c[i][j])); 
				}
			}
		}
			
		new_board = gt.alphaBeta(_board_c, YELLOW, -40, 40, 4);
			 		
		for (int i = 0; i < GRID_SIZE; ++i) 
		{
			for (int j = 0; j < GRID_SIZE; ++j)
			{
				if(new_board[i][j] == YELLOW)
				{
					new_values.push_back(Position(i,j,new_board[i][j])); 
				}
			}
	
		}
		// this will check if the values are the same 		
		for(int g = 0; g<new_values.size(); g++)
		{
			for(int n = 0; n<old_values.size(); n++)
			{
				 if(new_values[g].getColum() == old_values[n].getColum() && new_values[g].getRow() == old_values[n].getRow() )
				 { 
				  // new move 
				  letter = new_values[g].getColum(); 
				  number = new_values[g].getRow();
				  
				 }
			}
		
		}
	}
	 
	temp = convert(number,letter);
	
	std::cout<<" AI Move = "<<temp<<std::endl; 

	return temp;
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
		std::cout<< "this is the Ai color "<<get_color()<<std::endl;
	
	}
	if(ai_color == "YELLOW")
	{
		color = YELLOW;
		
	}

}





















