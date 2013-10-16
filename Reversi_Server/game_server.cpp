/*
    File: game_server.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
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

int Game_Server::parse_move(std::string move)
{
 //Lazy man's parser, checks first char in string if valid checks second char in string from the pool of all possible moves, else invalid move
	bool check_legal; // true == legal move, false == illegal move
	if (move[1] == 'a' || move[1] == 'b' || move[1] == 'c' || move[1] == 'd' || move[1] == 'e' || move[1] == 'f' || move[1] == 'g' || move[1] == 'h')
	{
		if(move[0] == '1'|| move[0] == '2' || move[0] == '2' || move[0] == '3' || move[0] == '4' || move[0] == '5' || move[0] == '6'|| move[0] == '7')
		{
			if(_e.get_color() == 0)
			{
				if(check_legal = _e.is_legal_black(move) == true)
				{
					if(!_e.move(move)) //GAME OVER
						return 4;
					return 3;
				}
				else
				{
					return 0;
				}
			}
			if(_e.get_color() == 1)
			{
				if(check_legal = _e.is_legal_yellow(move) == true)
				{
					if(!_e.move(move)) //GAME OVER
						return 4;
					return 3;
				}
				else
				{
					return 0;
				}
			}
		}
		else 
		{
			return 0; 
		}
	}
	else 
	{
		return 0; 
	}
}

unsigned int Game_Server::parse_cmd(std::string s){
	if(s.length() < 3)
		return 0;
	s.erase(s.end()-2, s.end());
	//STEP 1) set HUMAN and AI color, colorSet is a restriction if the user tries to enter a color query again we skip this statement 
	if(s == "BLACK" && !colorSet) {colorSet = true; _e.set_color("BLACK"); _ai.set_ai_color("YELLOW");} 
	else if(s == "YELLOW" && !colorSet) {colorSet = true; _e.set_color("YELLOW"); _ai.set_ai_color("BLACK");} 
	
	//STEP 2) set game type, AI_Set is a restriction if the user tries to enter a gametype query again or not set colors skip this statement  
	else if(s == "AI-AI" && colorSet && !AI_Set) { AI_Set = true; }
	else if(s == "HUMAN-AI" && colorSet && !AI_Set) {AI_Set = true; }
	
	//STEP 3) set difficulty, AI_diff_set is a restriction if the user tries to enter a diff. again or has not entered color or game type skip this statement  
	else if(s == "HARD" && !AI_diff_Set && colorSet && AI_Set) { AI_diff_Set = true; unsigned int hard = 7; setup_ai(hard) ;}
	else if(s == "EASY" && !AI_diff_Set && colorSet && AI_Set) { AI_diff_Set = true; unsigned int easy = 2; setup_ai(easy); }
	else if(s == "MEDIUM" && !AI_diff_Set && colorSet && AI_Set) {AI_diff_Set = true; unsigned int med = 4; setup_ai(med);}
	
	//STEP 4) if user had not satisfied previous steps then game is not set up and cannot use these commands 
	else if(s == "DISPLAY" && colorSet && AI_Set && AI_diff_Set && !display) {display = true; return 3;}
	else if(s == "UNDO" && colorSet && AI_Set && AI_diff_Set) {_e.undo_move();}
	else if(s == "EXIT") {exit();}
	
	//Step 5) Enter valid moves, sends to move parser has satified previous steps and has entered DISPLAY, parser checks move's validity then needs to check legality 
	else if(s.length() == 2 && colorSet && AI_Set && AI_diff_Set && display){ char c = s.at(0); s[0] = s[1]; s[1] = c; return parse_move(s);}
	
	else 
	{
		return 0;
	}
		return 1;
}

std::string Game_Server::reply(int i) {
	if( i == 0)
		return "ILLEGAL COMMAND\n";
	if(i == 1)
		return "OK\n";
	if(i==2)
		return "Enter Move\n";
	if(i == 3)
		return _e.print();
	if(i == 4)
		return _e.get_winner();
	return "\n";
}

void Game_Server::exit() {
	//exits program 
	std::cout<<"EXITING..." <<std::endl;
	std::exit(EXIT_SUCCESS);
}









