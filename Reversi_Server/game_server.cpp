/*
    File: game_server.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains function definitions associated 
	with Game_Server class in file game_server.h. 

*/

#include "game_server.h"
#include "game_state_engine.h"
#include "ai.h"

Game_Server::Game_Server() {
	_e = Gamestate_Engine();
	//do work
}

void Game_Server::setup_ai(unsigned int difficulty) {
	//do work
	_ai = AI();
	//_ai.set_difficulty(difficulty); // does not want to work but works on ai unit test
}

void Game_Server::run() {
	//do work
}

unsigned int Game_Server::parse_cmd(std::string s){
	
	if(s == "BLACK") {_e.set_color(s); std::cout << "OK"<< std::endl;}
	else if (s == "YELLOW") {_e.set_color(s);std::cout << "OK"<< std::endl;}
	else if(s == "DISPLAY") {std::cout << "OK"<< std::endl; _e.print();}
	else if(s == "EXIT") {exit();}
	else if(s == "HARD") {unsigned int hard = 7; setup_ai(hard);std::cout << "OK"<< std::endl;}
	else if(s == "EASY") {unsigned int easy = 2; setup_ai(easy);std::cout << "OK"<< std::endl;}
	else if(s == "MEDIUM") {unsigned int med = 7; setup_ai(med);std::cout << "OK"<< std::endl;}
	else if(s == "BLACK") { _e.set_color("BLACK"); /*_ai.set_ai_color("YELLOW");*/std::cout << "OK"<< std::endl;} // doesnt work cant change anything from ai 
	else if(s == "YELLOW") { _e.set_color("YELLOW"); /*_ai.set_ai_color("BLACK");*/std::cout << "OK"<< std::endl;} // doesnt work cant change anything from ai 
	else if(s == "UNDO") {std::cout << "OK"<< std::endl; _e.undo_move();}
	//else it is a move tokenizer? i found a way to see if the move is valid (not legal) by placing all moves in a vector
	return 0;
}

void Game_Server::reply(int i) {
	//do work
}

void Game_Server::exit() {
	//do work
}









