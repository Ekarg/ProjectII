/*
    File: game_state_engine.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains function definitions associated 
	with Gamestate_Engine class in file game_state_engine.h. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "game_state_engine.h"
#include "Position.h"
#include <vector>
#include <time.h> 
Gamestate_Engine::Gamestate_Engine() {
	_board.resize(GRID_SIZE);
	for (int i = 0; i < GRID_SIZE; ++i) {
		_board[i].resize(GRID_SIZE);
		for (int j = 0; j < GRID_SIZE; ++j) {
			_board[i][j] = EMPTY;
		}
	}
	_board[GRID_SIZE/2]     [e] = BLACK;
	_board[GRID_SIZE/2]     [d] = YELLOW;
	_board[(GRID_SIZE/2)-1] [d] = BLACK;
	_board[(GRID_SIZE/2)-1] [e] = YELLOW;
	
	_board[GRID_SIZE/2]     [e+1] = LEGAL_YELLOW;
	_board[GRID_SIZE/2-1]     [d-1] = LEGAL_YELLOW;
	
	_board[GRID_SIZE/2-1]     [e+1] = LEGAL_BLACK;
	_board[GRID_SIZE/2]     [d-1] = LEGAL_BLACK;
	
	_board[GRID_SIZE/2+1]     [e] = LEGAL_YELLOW;
	_board[GRID_SIZE/2+1]     [d] = LEGAL_BLACK;
	
	_board[(GRID_SIZE/2)-2] [d] = LEGAL_YELLOW;
	_board[(GRID_SIZE/2)-2] [e] = LEGAL_BLACK;
		
		
	can_play=true;	
	//TEST CASE
	//_board[0] [h] = YELLOW;
}
	

bool Gamestate_Engine::move(std::string square_id) {
	if(!can_play) 
		return false;
	int x, y;
	stoi_loc(square_id, y, x);
	int other_color;
	int our_color;
	if (player_color) {
		_board[y][x] = YELLOW;
		our_color = YELLOW;
		other_color = BLACK;
	}
	else {
		_board[y][x] = BLACK;
		other_color = YELLOW;
		our_color = BLACK;
	}
	std::stack<int> xs;
	std::stack<int> ys;
	int count = 0;
	
	//Diag
	int a = x+1;
	int b = y+1;
	
	for ( ; ( (a < GRID_SIZE) && (b < GRID_SIZE) ); ) {
		if (_board[b][a] == other_color) {
			xs.push(a);
			ys.push(b);
			++count;			
		}
		else if (_board[b][a] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
		++a;
		++b;
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	a = x-1;
	b = y-1;
	for ( ; ( (a > 0) && (b > 0) ); ) {
		if (_board[b][a] == other_color) {
			xs.push(a);
			ys.push(b);
			++count;
		}
		else if (_board[b][a] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
		--a;
		--b;
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	a = x-1;
	b = y+1; 
	for ( ; ( (a > 0) && (b < GRID_SIZE) ); ) {
		if (_board[b][a] == other_color) {
			xs.push(a);
			ys.push(b);
			++count;
		}
		else if (_board[b][a] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
		--a;
		++b;
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	a = x+1;
	b = y-1;
	for ( ; ( (a < GRID_SIZE) && (b>0) ); ) {
		if (_board[b][a] == other_color) {
			xs.push(a);
			ys.push(b);
			++count;
		}
		else if (_board[b][a] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
		++a;
		--b;
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	a = x;
	b = y;
	//Diag

	
	//---Horizontal
	
	for (int i = y+1; i < GRID_SIZE; ++i) {
		if (_board[i][x] == other_color) {
			xs.push(x);
			ys.push(i);
			++count;
		}
		else if (_board[i][x] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	
	for (int i = y-1; i > 0; --i) {
		if (_board[i][x] == other_color) {
			xs.push(x);
			ys.push(i);
			++count;
		}
		else if (_board[i][x] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	
	//---Horizontal
	
	//---Vertical
	
	for (int i = x+1; i < GRID_SIZE; ++i) {
		if (_board[y][i] == other_color) {
			xs.push(i);
			ys.push(y);
			++count;
		}
		else if (_board[y][i] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	for (int i = x-1; i > 0; --i) {
		if (_board[y][i] == other_color) {
			xs.push(i);
			ys.push(y);
			++count;
		}
		else if (_board[y][i] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	
	//---Vertical
	while(!xs.empty() && !ys.empty()) {
		int x_cor = xs.top();
		int y_cor = ys.top(); 
		xs.pop();
		ys.pop();
		_board[y_cor][x_cor] = _board[y][x];
	}
	
	legality();
	std::vector<int> x_cor;
	std::vector<int> y_cor;
	if(player_color) {
		for(int x = 0; x < GRID_SIZE; x++)
			for(int y = 0; y<GRID_SIZE; y++) {
				if(_board[y][x] == LEGAL_BLACK || _board[y][x] == LEGAL_BOTH) {
					x_cor.push_back(x); 
					y_cor.push_back(y);
				}			
		}
	//	srand (time(NULL));
	//	int m = rand() % (x_cor.size());
		set_color("BLACK");
		ai_move(y_cor[0], x_cor[0]);
		set_color("YELLOW");
	}
	
	
	
	else {
		for(int x = 0; x < GRID_SIZE; x++)
			for(int y = 0; y<GRID_SIZE; y++) {
				if(_board[y][x] == LEGAL_YELLOW || _board[y][x] == LEGAL_BOTH) {
					x_cor.push_back(x); 
					y_cor.push_back(y);
				}
			srand (time(NULL));
			int m = rand() % (x_cor.size());
			set_color("YELLOW");
			ai_move(y_cor[0], x_cor[0]);
			set_color("BLACK");
		}	
	}
	check_play();
	return can_play;
}

void Gamestate_Engine::ai_move(int y, int x) {
	int other_color;
	int our_color;
	if (player_color) {
		_board[y][x] = YELLOW;
		our_color = YELLOW;
		other_color = BLACK;
	}
	else {
		_board[y][x] = BLACK;
		other_color = YELLOW;
		our_color = BLACK;
	}
	std::stack<int> xs;
	std::stack<int> ys;
	int count = 0;
	
	//Diag
	int a = x+1;
	int b = y+1;
	
	for ( ; ( (a < GRID_SIZE) && (b < GRID_SIZE) ); ) {
		if (_board[b][a] == other_color) {
			xs.push(a);
			ys.push(b);
			++count;			
		}
		else if (_board[b][a] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
		++a;
		++b;
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	a = x-1;
	b = y-1;
	for ( ; ( (a > 0) && (b > 0) ); ) {
		if (_board[b][a] == other_color) {
			xs.push(a);
			ys.push(b);
			++count;
		}
		else if (_board[b][a] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
		--a;
		--b;
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	a = x-1;
	b = y+1; 
	for ( ; ( (a > 0) && (b < GRID_SIZE) ); ) {
		if (_board[b][a] == other_color) {
			xs.push(a);
			ys.push(b);
			++count;
		}
		else if (_board[b][a] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
		--a;
		++b;
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	a = x+1;
	b = y-1;
	for ( ; ( (a < GRID_SIZE) && (b>0) ); ) {
		if (_board[b][a] == other_color) {
			xs.push(a);
			ys.push(b);
			++count;
		}
		else if (_board[b][a] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
		++a;
		--b;
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	a = x;
	b = y;
	//Diag

	
	//---Horizontal
	
	for (int i = y+1; i < GRID_SIZE; ++i) {
		if (_board[i][x] == other_color) {
			xs.push(x);
			ys.push(i);
			++count;
		}
		else if (_board[i][x] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	
	for (int i = y-1; i > 0; --i) {
		if (_board[i][x] == other_color) {
			xs.push(x);
			ys.push(i);
			++count;
		}
		else if (_board[i][x] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	
	//---Horizontal
	
	//---Vertical
	
	for (int i = x+1; i < GRID_SIZE; ++i) {
		if (_board[y][i] == other_color) {
			xs.push(i);
			ys.push(y);
			++count;
		}
		else if (_board[y][i] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	for (int i = x-1; i > 0; --i) {
		if (_board[y][i] == other_color) {
			xs.push(i);
			ys.push(y);
			++count;
		}
		else if (_board[y][i] == our_color) {
			count = 0;
			break;
		}
		else {		
			break;
		}
	}
	while (count > 0) {
		xs.pop();
		ys.pop();
		--count;
	}
	
	//---Vertical
	while(!xs.empty() && !ys.empty()) {
		int x_cor = xs.top();
		int y_cor = ys.top(); 
		xs.pop();
		ys.pop();
		_board[y_cor][x_cor] = _board[y][x];
	}
	
	legality();
}


bool Gamestate_Engine::unmove(std::string square_id) {
	//do work
	return true;
}

bool Gamestate_Engine::is_play() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if ( is_legal_yellow(itos_loc(i, j)) || is_legal_black(itos_loc(i, j)) ) {
				return true;
			}
		}
	}
	return false;
}

bool Gamestate_Engine::undo_move() {
	//do work
	return true;
}

bool Gamestate_Engine::redo_move() {
	//do work
	return true;
}

bool Gamestate_Engine::is_legal_yellow(std::string square_id) {
	int x, y;
	stoi_loc(square_id, x, y);
	//std::cout << _board[x][y];
	if ( (_board[x][y] == LEGAL_YELLOW) || (_board[x][y] == LEGAL_BOTH) ) {
		return true;
	}
	return false;
}

bool Gamestate_Engine::is_legal_black(std::string square_id) {
	int x, y;
	stoi_loc(square_id, x, y);
	//std::cout << _board[x][y];
	if ( (_board[x][y] == LEGAL_BLACK) || (_board[x][y] == LEGAL_BOTH) ) {
		return true;
	}
	return false;
}

std::string Gamestate_Engine::print() {
	system("clear");
	// System call to clear screen 
	std::string s;
	s = ";  _ _ _ _ _ _ _ _\n";
	for (int i = 0; i < _board.size(); ++i) {
		s+= ";";
		//taken from stackoverflow forum
		std::ostringstream stream;
		stream << s << i;
		s = stream.str();
		s+= "|";
		for (int j = 0; j < _board[i].size(); ++j) {
			switch(_board[i][j]) {
				case EMPTY:
					s+= "_";
					break;
				case YELLOW:
					s+= "0";
					break;
				case BLACK:
					s+= "X";
					break;
				default:
					s+= "_";
					break;
			}
			s+= "|";
		}
		s+= "\n";
	}
	s+= ";  a b c d e f g h\n\n";
	return s;
}

std::string Gamestate_Engine::get_board() {
	std::stringstream ss;
	std::string s = "";
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			ss << (int)_board[i][j];
			char a;
			ss >> a;
			s += a;
			s += " ";
		}
		s += "\n";
	}
	return s;
}

std::string Gamestate_Engine::itos_loc(int x, int y) {
	std::string s = "";
	if ( (x >= GRID_SIZE) || (y >= GRID_SIZE) ) {
		printf("ERROR : itos_loc(x, y) | x || y >= GRID_SIZE;\n");
		return s;
	}
	std::stringstream ss;
	ss << x;
	ss >> s;
	//Quick and dirty: Never ever ever ever do this.
	s += (char)(y+97);
	//Quick and dirty: Never ever ever ever do this.
	return s;
}

void Gamestate_Engine::stoi_loc(std::string s, int &x, int &y) {
	if (s.size() != 2) {
		printf("ERROR : stoi_loc(s, x, y) | s.size() != 2;\n");
		return;
	}
	std::string s_2 = "";
	s_2 += s[1];		// s_2 = y;
	s.erase(s.end()-1); // s = x;
	x = atoi(s.c_str());
	//Quick and dirty: Never ever ever ever do this.
	y = ((int)s_2[0]) - 97;
	//Quick and dirty: Never ever ever ever do this.
	if ( (x < 0) || (y < 0) || (x >= GRID_SIZE) || (y >= GRID_SIZE) ) {
		printf("ERROR : stoi_loc(s, x, y) | x and/or y out of bounds;\n");		
	}
}

void Gamestate_Engine::set_color(std::string color)
{
	if(color == "YELLOW")
	{	
		player_color = true;
	}
	if(color == "BLACK")
	{
		player_color = false;
	}
}

int Gamestate_Engine::get_color() 
{
	return player_color;
}

void Gamestate_Engine::legality() {
	for(int x = 0; x < GRID_SIZE; x++)
		for(int y = 0; y<GRID_SIZE; y++) {
			if(_board[y][x] != YELLOW && _board[y][x] !=BLACK) {
					int other_color;
					int our_color;
					
					other_color = YELLOW;
					our_color = BLACK;
					std::stack<int> xs;
					std::stack<int> ys;
					int count = 0;
		
					//Diag
					int a = x+1;
					int b = y+1;
					
					for ( ; ( (a < GRID_SIZE) && (b < GRID_SIZE) ); ) {
						if (_board[b][a] == other_color) {
							xs.push(a);
							ys.push(b);
							++count;
						}
						else if (_board[b][a] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
						++a;
						++b;
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					a = x-1;
					b = y-1;
					for ( ; ( (a > 0) && (b > 0) ); ) {
						if (_board[b][a] == other_color) {
							xs.push(a);
							ys.push(b);
							++count;
						}
						else if (_board[b][a] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
						--a;
						--b;
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					a = x-1;
					b = y+1;
					for ( ; ( (a > 0) && (b < GRID_SIZE) ); ) {
						if (_board[b][a] == other_color) {
							xs.push(a);
							ys.push(b);
							++count;
						}
						else if (_board[b][a] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
						--a;
						++b;
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					a = x+1;
					b = y-1;
					for ( ; ( (a < GRID_SIZE) && (b > 0) ); ) {
						if (_board[b][a] == other_color) {
							xs.push(a);
							ys.push(b);
							++count;
						}
						else if (_board[b][a] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
						++a;
						--b;
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					a = x;
					b = y;
					//Diag

					
					//---Vertical
					
					for (int i = y+1 ; i < GRID_SIZE; ++i) {
						if (_board[i][x] == other_color) {
							xs.push(x);
							ys.push(i);
							++count;
						}
						else if (_board[i][x] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
				
					for (int i = y-1; i > 0; --i) {
						if (_board[i][x] == other_color) {
							xs.push(x);
							ys.push(i);
							++count;
						}
						else if (_board[i][x] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					
					//---Horizontal
					
					for (int i = x+1; i < GRID_SIZE; ++i) {
						if (_board[y][i] == other_color) {
							xs.push(i);
							ys.push(y);
							++count;
						}
						else if (_board[y][i] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					for (int i = x-1; i > 0; --i) {
						if (_board[y][i] == other_color) {
							xs.push(i);
							ys.push(y);
							++count;
						}
						else if (_board[y][i] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					
					if(xs.size() > 0) 
						_board[y][x] = LEGAL_BLACK;				
					else
						_board[y][x] = EMPTY;	
					}
		}
					for(int x = 0; x < GRID_SIZE; x++)
						for(int y = 0; y < GRID_SIZE; y++) {
							if(_board[y][x] != YELLOW && _board[y][x] != BLACK) {
								
								int other_color = BLACK;
								int our_color = YELLOW;
								
								std::stack<int> xs;
								std::stack<int> ys;
								int count = 0;
								
										//Diag
					int a = x+1;
					int b = y+1;
					
					for ( ; ( (a < GRID_SIZE) && (b < GRID_SIZE) ); ) {
						if (_board[b][a] == other_color) {
							xs.push(a);
							ys.push(b);
							++count;
						}
						else if (_board[b][a] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
						++a;
						++b;
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					a = x-1;
					b = y-1;
					for ( ; ( (a > 0) && (b > 0) ); ) {
						if (_board[b][a] == other_color) {
							xs.push(a);
							ys.push(b);
							++count;
						}
						else if (_board[b][a] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
						--a;
						--b;
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					a = x-1;
					b = y+1;
					for ( ; ( (a > 0) && (b < GRID_SIZE) ); ) {
						if (_board[b][a] == other_color) {
							xs.push(a);
							ys.push(b);
							++count;
						}
						else if (_board[b][a] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
						--a;
						++b;
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					a = x+1;
					b = y-1;
					for ( ; ( (a < GRID_SIZE) && (b > 0) ); ) {
						if (_board[b][a] == other_color) {
							xs.push(a);
							ys.push(b);
							++count;
						}
						else if (_board[b][a] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
						++a;
						--b;
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					a = x;
					b = y;
					//Diag

					
					//---Vertical
					
					for (int i = y+1 ; i < GRID_SIZE; ++i) {
						if (_board[i][x] == other_color) {
							xs.push(x);
							ys.push(i);
							++count;
						}
						else if (_board[i][x] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
				
					for (int i = y-1; i > 0; --i) {
						if (_board[i][x] == other_color) {
							xs.push(x);
							ys.push(i);
							++count;
						}
						else if (_board[i][x] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					
					//---Horizontal
					
					for (int i = x+1; i < GRID_SIZE; ++i) {
						if (_board[y][i] == other_color) {
							xs.push(i);
							ys.push(y);
							++count;
						}
						else if (_board[y][i] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
					for (int i = x-1; i > 0; --i) {
						if (_board[y][i] == other_color) {
							xs.push(i);
							ys.push(y);
							++count;
						}
						else if (_board[y][i] == our_color) {
							count = 0;
							break;
						}
						else {		
							break;
						}
					}
					while (count > 0) {
						xs.pop();
						ys.pop();
						--count;
					}
											
					if(xs.size() > 0) 
					{
						if(_board[y][x] == LEGAL_BLACK)
							_board[y][x] = LEGAL_BOTH;
						else
							_board[y][x] = LEGAL_YELLOW;								
					}	
									
				}
				
			}
}


void Gamestate_Engine::check_play() {
	bool black_can = false;
	bool yellow_can =false;
	for(int x = 0; x < GRID_SIZE; x++)
		for(int y = 0; y < GRID_SIZE; y++) {
			if(_board[y][x] == LEGAL_BLACK || _board[y][x] == LEGAL_BOTH) {
				black_can=true;
				return;
			}
	}
	
	for(int x = 0; x < GRID_SIZE; x++)
		for(int y = 0; y < GRID_SIZE; y++) {
			if(_board[y][x] == LEGAL_YELLOW || _board[y][x] == LEGAL_BOTH) {
				yellow_can=true;
				return;
			}
	}

	if(!yellow_can && !black_can) {
		winner = "IT'S A TIE!";
		can_play = false;
	}
	
	else if (yellow_can && !black_can) {
		if(player_color)
			winner = "You win!\n";
		else 
			winner = "You lose!\n";
		can_play = false;
	}
	else if (!yellow_can && black_can) {
		if(!player_color)
			winner = "You win!\n";
		else 
			winner = "You win\n";
		can_play = false;
	}
}













