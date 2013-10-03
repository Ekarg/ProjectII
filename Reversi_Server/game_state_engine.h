/* 
    File: game_state_engine.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang
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

const int GRID_SIZE = 8;

class Gamestate_Engine {
private:

	enum State { EMPTY = 0, YELLOW = 1, BLACK = 2};
	enum columns { a = 0, b = 1, c = 2, d = 3, e = 4, f = 5, g = 6, h = 7, i = 8, 
					j = 9, k = 10, l = 11, m = 12, n = 13, o = 14, p = 15, q = 16, 
					r = 17, s = 18, t = 19, u = 20, v = 21, w = 22, x = 23, y = 24, 
					z = 25};
					
	std::vector<std::vector<State> > _board;
	std::stack<std::string> played_moves;
	std::stack<std::string> undid_moves;
	bool player_color;
	// True = YELLOW; False = BLACK;

public:

	Gamestate_Engine();
	//Default Constructor sets up initial conditions
	
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
	// Returns false if no more avaiable moves
	
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
	
	bool is_legal_black(std::string square_id);
	// Returns true if square is a legal move for black
	// autofalse is square is occupied
	
	void print();
	// Print _board to console
	
	std::string get_board();
	// returns string representation of board
	// i.e. "0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n  0 0 0 0 1 2 0 0 \n" ...etc.
	// call to get data to send to client 
	
};

#endif


