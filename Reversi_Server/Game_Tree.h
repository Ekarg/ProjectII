#ifndef GAME_TREE_H_
#define GAME_TREE_H_

#include "stdafx.h"

using namespace std;

struct Node
{
	Node() {}
	Node(vector<vector<State>> b) { board = b;	}
	~Node() {}


	vector<vector<State>> board;
	vector<Node*> children;
	int score;
	State node_color;
};

class Game_Tree
{
public:
	Game_Tree() { root = NULL; }
	~Game_Tree() { delete root; }

	vector<vector<State>> negamax(vector<vector<State>>& board, State color, int height);
	vector<vector<State>> alphaBeta(vector<vector<State>> & board, State color, int alpha, int beta, int height);

	void buildTree(int height);
	int numOfBranch();
	void initiateBoard(vector<vector<State>>& board, State c);
//	void legal(vector<vector<State>> board, State color);

protected:
	void _buildTree(Node* n, int height, State color);
	int _numOfBranch(Node* n);
	void findBranch(Node* n, State color);
private:
	void removeFormerTree(Node* node); //disposal function
	int eval_node(Node* node, State color);
	int eval_tree(Node* node, int height, State color);
	int eval_tree(Node* node, int height, State color, int alpha, int beta);
	void legal(vector<vector<State>>& board, State color);
	void reverse(vector<vector<State>>& board, State color, int x, int y);
	void reverse_one_direction(vector<vector<State>>& board, State color, int x, int y, int a, int b); // this is an auxiliary function for reversion, a an b represent the direction.
	string print(vector<vector<State>> board);

	Node* best_Node;
	Node* root;
};

#endif