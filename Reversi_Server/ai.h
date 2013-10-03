/* 
    File: ai.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    WHITE SHIT ABOUT AI HERE

*/

#ifndef _AI_
#define _AI_

#include <map>
#include <string>

class AI {
private:
	//std::map<std::string> _tree;
	//map or tree.hh variant to implement a tree structure (or we can write our own)
	
	enum Color { YELLOW = 1, BLACK = 2};
	
	Color color;
	unsigned int difficulty; 
	// difficulty is a scalar which we use to adjust allotted search time
	// and/or tree depth for AI and/or sub-optimalization of choices
	// 0 = randomly chosen move
	// 9 = optimally chosen move
	// random = ~0; easy = ~2; medium = ~4; hard = ~6; gosuswag = ~8;

public:
	AI(): difficulty(0), color(BLACK) {}
	AI(unsigned int i): difficulty(0), color((Color)i) {}
	
	unsigned int compare(std::string a, std::string b);
	// compares two boardstates and decides which is "winning"
	// return 0 for equal
	// return 1 for a > b
	// return 2 for a < b

	void create_tree(std::string state);
	/*
		Takes a state in the form of a string and generates branches off current state
		node where each branch represents a possible move. The depth of the tree generated 
		can either be constant ( see X moves ahead ) or variable based on the difficulty
		level of the AI. NOTE: Replaces old tree.
	*/
	
	std::string choose();
	/*
		Called only after the tree has been created. Bredth first search through tree
		to determine the choice the AI makes. Each branch contains a gamestate in the
		form of a string and are compared to each other with the compare() function.
		Based on difficulty scalar, the AI may choose non-optimal choice. 
	*/
	
	void set_difficulty(unsigned int i);
	// Manually sets AI difficulty
	
	
};

#endif











