/*
    File: test_main.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    THIS FILE CONTAINS UNIT TESTS FOR CLASS MEMBER FUNCTIONS
	OF THE CLASS Gamestate_Engine. THIS MAIN DOES NOT DO ANYTHING
	RELEVANT IN TERMS OF THE REVERSI PROJECT. 

*/

#include <iostream>

#include "game_state_engine.h"

int main() {
	Gamestate_Engine _e = Gamestate_Engine();
	_e.print();
	std::cout << _e.get_board() << '\n';
	int a = 4;
	int b = 5;
	std::cout << a << b << " is : " << _e.itos_loc(a, b);
}