#include "Game_Tree.h"
#include <stdio.h>
#include <stdint.h>
#include <typeinfo>
#include <sstream>
#include <iostream>
#include <stdlib.h>

//STL library
#include <vector>
#include <string>
#include <stack>

using namespace std;

int main()
{
	vector<vector<State> > board;
	board.resize(GRID_SIZE);
	for(int i = 0; i < GRID_SIZE; i ++)
	{
		board[i].resize(GRID_SIZE);
		for(int j = 0; j < GRID_SIZE; j ++)
			board.at(i).at(j) = EMPTY;
	}

	board.at(3).at(3) = BLACK;
	board.at(3).at(5) = YELLOW;
	board.at(3).at(4) = YELLOW;
	board.at(4).at(4) = BLACK;
	board.at(2).at(2) = BLACK;
	board.at(3).at(2) = BLACK;
	board.at(4).at(2) = BLACK;
	board.at(4).at(3) = BLACK;
	board.at(2).at(3) = BLACK;
	board.at(3).at(3) = BLACK;
	board.at(2).at(4) = BLACK;
	board.at(1).at(2) = BLACK;
	

	Game_Tree gt;
//	gt.initiateBoard(board, YELLOW);
//	gt.negamax(board, YELLOW, 2);
	gt.alphaBeta(board, YELLOW, -50, 50, 5);
	return 0;
}