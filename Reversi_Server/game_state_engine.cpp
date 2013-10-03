/*
    File: game_state_engine.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains function definitions associated 
	with Gamestate_Engine class in file game_state_engine.h. 

*/

#include <string>
#include <iostream>
#include <stdlib.h>

#include "game_state_engine.h"

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
}
	
bool Gamestate_Engine::move(std::string square_id) {
	//do work
	return true;
}

bool Gamestate_Engine::unmove(std::string square_id) {
	//do work
	return true;
}

bool Gamestate_Engine::is_play() {
	//do work
	return true;
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
	//do work
	return true;
}

bool Gamestate_Engine::is_legal_black(std::string square_id) {
	//do work
	return true;
}

void Gamestate_Engine::print() {
	system("clear");
	// System call to clear screen 
	std::cout << ";  _ _ _ _ _ _ _ _\n";
	for (int i = 0; i < _board.size(); ++i) {
		std::cout << ';' << i << '|';
		for (int j = 0; j < _board[i].size(); ++j) {
			switch(_board[i][j]) {
				case EMPTY:
					std::cout << '_';
					break;
				case YELLOW:
					std::cout << '0';
					break;
				case BLACK:
					std::cout << 'X';
					break;
				default:
					std::cout << '_';
					break;
			}
			std::cout << '|';
		}
		std::cout << '\n';
	}
	std::cout << ";  a b c d e f g h\n\n";
}

std::string get_board() {
	//do work
	return "dostuff";
}


















