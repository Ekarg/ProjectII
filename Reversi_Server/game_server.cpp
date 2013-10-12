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


bool colorSet = false; //checks if user has already entered a color
bool AI_Set = false; //checks if users has already entered game type
bool AI_diff_Set = false; //checks if user has already entered a difficulty
bool display = false; //checks if user has entered diplay command


Game_Server::Game_Server() {
	_e = Gamestate_Engine();
	//do work
}

void Game_Server::setup_ai(unsigned int difficulty) {
	//sets up a defaul AI then alters diffculty EASY ~ 2, MED ~4, HARD ~7 
	_ai = AI();
	_ai.set_difficulty(difficulty);
}

void Game_Server::run() {
	//do work
}

void Game_Server::parse_move(std::string move)
{
 //Lazy man's parser, checks first char in string if valid checks second char in string from the pool of all possible moves, else invalid move
	
	bool check_legal; // true == legal move, false == illegal move
	if (move[0] == 'a' || move[0] == 'b' || move[0] == 'c' || move[0] == 'd' || move[0] == 'e' || move[0] == 'f' || move[0] == 'g' || move[0] == 'h')
	{
		if(move[1] == '1'|| move[1] == '2' || move[1] == '2' || move[1] == '3' || move[1] == '4' || move[1] == '5' || move[1] == '6'|| move[1] == '7')
		{
			if(_e.get_color() == 0)
			{
				if(check_legal = _e.is_legal_black(move) == true)
				{
					std::cout << "Enter Move" << std::endl; //allowed to enter a new move
				}
				else
				{
					std::cout << "ILLEGAL MOVE" << std::endl;
				}
			}
			if(_e.get_color() == 1)
			{
				if(check_legal = _e.is_legal_yellow(move) == true)
				{
					std::cout << "Enter Move" << std::endl; //allowed to enter a new move
				}
				else
				{
					std::cout << "ILLEGAL MOVE" << std::endl;
				}
			}
		}
		else 
		{
			std::cout << "Invalid Move, please try again" << std::endl; //first char is correct but second is not 
		}
	}
	else 
	{
		std::cout << "Invalid Move, please try again" << std::endl; //not a correct move at all 
	}
}

unsigned int Game_Server::parse_cmd(std::string s){

	//STEP 1) set HUMAN and AI color, colorSet is a restriction if the user tries to enter a color query again we skip this statement 
	if(s == "BLACK" && !colorSet) {colorSet = true; std::cout << "OK \t\t\t ;choose game mode"<< std::endl; _e.set_color("BLACK"); _ai.set_ai_color("YELLOW");} 
	else if(s == "YELLOW" && !colorSet) {colorSet = true; std::cout << "OK \t\t\t ;choose game mode"<< std::endl; _e.set_color("YELLOW"); _ai.set_ai_color("BLACK");} 
	
	//STEP 2) set game type, AI_Set is a restriction if the user tries to enter a gametype query again or not set colors skip this statement  
	else if(s == "AI-AI" && colorSet && !AI_Set) { AI_Set = true; std::cout << "OK \t\t\t ;set AI difficulty"<< std::endl;}
	else if(s == "HUMAN-AI" && colorSet && !AI_Set) {AI_Set = true; std::cout << "OK \t\t\t ;set AI difficulty"<< std::endl;}
	
	//STEP 3) set difficulty, AI_diff_set is a restriction if the user tries to enter a diff. again or has not entered color or game type skip this statement  
	else if(s == "HARD" && !AI_diff_Set && colorSet && AI_Set) { AI_diff_Set = true; unsigned int hard = 7; setup_ai(hard) ;std::cout << "OK"<< std::endl;}
	else if(s == "EASY" && !AI_diff_Set && colorSet && AI_Set) { AI_diff_Set = true; unsigned int easy = 2; setup_ai(easy); std::cout << "OK"<< std::endl;}
	else if(s == "MEDIUM" && !AI_diff_Set && colorSet && AI_Set) {AI_diff_Set = true; unsigned int med = 4; setup_ai(med);std::cout << "OK"<< std::endl;}
	
	//STEP 4) if user had not satisfied previous steps then game is not set up and cannot use these commands 
	else if(s == "DISPLAY" && colorSet && AI_Set && AI_diff_Set && !display) {display = true; std::cout <<"OK"<< std::endl; _e.print(); std::cout <<"Enter move"<<std::endl;}
	else if(s == "UNDO" && colorSet && AI_Set && AI_diff_Set) {std::cout <<"OK"<< std::endl; _e.undo_move();}
	else if(s == "EXIT") {exit();}
	
	//Step 5) Enter valid moves, sends to move parser has satified previous steps and has entered DISPLAY, parser checks move's validity then needs to check legality 
	else if(s.length() == 2 && colorSet && AI_Set && AI_diff_Set &&display){parse_move(s);}
	
	else 
	{
		std::cout << "Invalid query, please try again" << std::endl;
	}
		return 0;
}

void Game_Server::reply(int i) {
	//do work
}

void Game_Server::exit() {
	//exits program 
	std::cout<<"EXITING..." <<std::endl;
	std::exit(EXIT_SUCCESS);
}









