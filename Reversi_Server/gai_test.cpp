/*
    File: test_main.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    THIS FILE CONTAINS UNIT TESTS FOR CLASS MEMBER FUNCTIONS
	OF THE CLASS AI. THIS MAIN DOES NOT DO ANYTHING
	RELEVANT IN TERMS OF THE REVERSI PROJECT. 

*/

#include "ai.h"

int main() {
	AI _ai;
	_ai.create_tree("0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n 0 0 0 0 0 0 0 0 \n ");
	_ai.set_difficulty(10);
	_ai.set_ai_color("BLACK");
	_ai.out_diff();
	_ai.out_color();
	
}