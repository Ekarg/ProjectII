#include "Game_Tree.h"
#include "stdafx.h"

using namespace std;

int main()
{
	vector<vector<State>> board;
	board.resize(GRID_SIZE);
	for(int i = 0; i < GRID_SIZE; i ++)
	{
		board[i].resize(GRID_SIZE);
		for(int j = 0; j < GRID_SIZE; j ++)
			board.at(i).at(j) = EMPTY;
	}

	board.at(3).at(3) = BLACK;
	board.at(3).at(4) = YELLOW;
	board.at(4).at(3) = YELLOW;
	board.at(4).at(4) = BLACK;
	board.at(4).at(5) = BLACK;

	Game_Tree gt;
//	gt.initiateBoard(board, YELLOW);
//	gt.negamax(board, YELLOW, 2);
	gt.alphaBeta(board, YELLOW, -20, 20, 2);
	return 0;
}