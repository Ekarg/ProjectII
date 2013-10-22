/* 
    File: game_state_engine.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains the Gamestate_Engine class that does 
	the heavy lifting on the serverside of the Reversi project. 

*/

#ifndef _Gamestate_Engine_
#define _Gamestate_Engine_

#include <vector>
#include <stack>
#include <string>

#include "global_const.h"

class Gamestate_Engine {
private:

	enum columns { a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7, i = 8, 
					j = 9, k = 10, l = 11, m = 12, n = 13, o = 14, p = 15, q = 16, 
					r = 17, s = 18, t = 19, u = 20, v = 21, w = 22, x = 23, y = 24, 
					z = 25};
					
	std::vector<std::vector<State> > _board;
	std::stack<std::string> played_moves; //stack of string representations of previous boards
	std::stack<std::string> undid_moves; //stack of string representations of boards that have been undone

	bool player_color;
	bool can_play;
	std::string winner;
	// True = YELLOW; False = BLACK;

public:
	
	Gamestate_Engine();
	//Default Constructor sets up initial conditions
	//e.g.
	//	1.) Two yellow, two black pieces in middle of the board
	//	....
	//
	
	void check_play();
	
	bool move(std::string square_id);
	// Returns false if invalid, otherwise update _board to reflect move made
	// Simplistic parsing of two character move command should be done here
	// Insert move to played_moves for use with undo/redo
	// Input square_id is the chosen destination for moved piece 
	// Check is_play(); if false, game-over
	
	bool unmove(std::string square_id);
	// Returns false if invalid, otherwise update _board to reflect undid move
	// Simplistic parsing of two character move command should be done here
	// Should only ever be called by undo_move()
	// Input square_id is the location of the piece we want to undo

	bool is_play();
	// Returns false if no more available moves
	
	bool undo_move();
	// Returns false on fail, return true on success
	// unmove(played_moves.top());
	// undid_moves.push_back(played_moves.top());
	// played_moves.pop();
	
	bool redo_move();
	// Returns false on fail, return true on success
	// move(undid_moves.top());
	// played_moves.push_back(undid_moves.top());
	// undid_moves.pop();
	
	bool is_legal_yellow(std::string square_id);
	// Returns true if square is a legal move for yellow
	// autofalse is square is occupied
	// i.e - checks to see if square is 3 or 5
	
	bool is_legal_black(std::string square_id);
	// Returns true if square is a legal move for black
	// autofalse is square is occupied
	// i.e - checks to see if square is 4 or 5
	
	std::string print();
	// Print _board to console
	
	std::string get_board();
	
	// returns string representation of board
	// i.e. "0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n  0 0 0 0 1 2 0 0 \n" ...etc.
	// call to get data to send to client 
	
	std::string itos_loc(int x, int y);
	// converts grid coordinates to string representation
	
	void stoi_loc(std::string s, int &x, int &y);
	// viceversa of itos_loc();
	
	void set_color(std::string color);
	//sets player's color
	
	int get_color();
	//gets player's color
	
	void legality();
	
	void ai_move(int y, int x);
	
	std::string get_winner() {return winner;}
};

#endif


