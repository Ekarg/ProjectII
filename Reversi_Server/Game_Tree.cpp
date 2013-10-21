#include "Game_Tree.h"

void Game_Tree::initiateBoard(vector<vector<State>>& board, State c)
{
	removeFormerTree(root);

	root = new Node(board);
	root->node_color = c;
	legal(root->board, root->node_color);

	eval_node(root, root->node_color);
	cout << print(root->board) << endl;
}

vector<vector<State>> Game_Tree::negamax(vector<vector<State>>& board, State color, int height)
{
	State our_color, other_color;

	if(color == YELLOW)
	{
		our_color = YELLOW;
		other_color = BLACK;
	}
	else
	{
		our_color = BLACK;
		other_color = YELLOW;
	}
	initiateBoard(board, color);
	findBranch(root, root->node_color);

	
	for(int i = 0; i < root->children.size(); i ++)
	{
		 eval_tree(root->children.at(i), height, other_color);
		//eval_tree(root->children.at(i), 2, other_color);
	}

	Node * temp = root->children.at(0);
	for(int i = 1; i < root->children.size(); i ++)
	{
		if(root->children.at(i)->score > temp->score)
			temp = root->children.at(i);
	}
	//eval_tree(root, 1, );
	cout << print(temp->board)<<endl;
	cout << temp->score << endl;
	return temp->board;
}

vector<vector<State>> Game_Tree::alphaBeta(vector<vector<State>> & board, State color, int alpha, int beta, int height)
{
	State our_color, other_color;

	if(color == YELLOW)
	{
		our_color = YELLOW;
		other_color = BLACK;
	}
	else
	{
		our_color = BLACK;
		other_color = YELLOW;
	}

	initiateBoard(board, color);
	findBranch(root, root->node_color);

	for(int i = 0; i < root->children.size(); i ++)
	{
		eval_tree(root->children.at(i), 2, other_color, alpha, beta);
		//eval_tree(root->children.at(i), 2, other_color);
	}

	Node * temp = root->children.at(0);
	for(int i = 1; i < root->children.size(); i ++)
	{
		if(root->children.at(i) == NULL)
			continue; //skip
		if(root->children.at(i)->score > temp->score)
			temp = root->children.at(i);
	}
	cout << print(temp->board)<<endl;
	cout << temp->score << endl;
	return temp->board;
}

void Game_Tree::findBranch(Node* n, State color)
{
	State our_color, other_color;

	if(color == BLACK)
	{
		our_color = BLACK;
		other_color = YELLOW;
	}
	else
	{
		our_color = YELLOW;
		other_color = BLACK;
	}

	for(int i = 0; i < n->board.size(); i ++)
	{
		for(int j = 0; j < n->board.at(i).size(); j ++)
		{
			if(n->board.at(i).at(j) == (State)(color + 2))
			{
				vector<vector<State>> cond = n->board;
				reverse(cond, color, i, j);
				legal(cond, other_color);
			//	cout << print(cond) << endl;
				Node* child = new Node(cond);
				child->node_color = other_color;
				eval_node(child, child->node_color);

				n->children.push_back(child);
			}
			// 			if(n->board.at(i).at(j) == State::LEGAL_BLACK)
			// 			{
			// 				vector<vector<State>> cond = n->board;
			// 				cond.at(i).at(j) = State::BLACK;
			// 				
			// 
			// 				Node* n = new Node(cond);
			// 
			// 				//push back to children vector
			// 				n->children.push_back(n);
			// 			}
			// 
			// 			if(n->board.at(i).at(j) == State::LEGAL_YELLOW)
			// 			{
			// 				vector<vector<State>> cond = n->board;
			// 				cond.at(i).at(j) = State::YELLOW;
			// 
			// 				Node* n = new Node(cond);
			// 
			// 				//push back to children vector
			// 				n->children.push_back(n);
			// 			}
			// 
			// 			if(n->board.at(i).at(j) == State::LEGAL_BOTH)
			// 			{
			// 				vector<vector<State>>cond = n->board;
			// 				cond.at(i).at(j) = State::BLACK;
			// 
			// 				Node* n1 = new Node(cond);
			// 
			// 				cond.at(i).at(j) = State::YELLOW;
			// 
			// 				Node* n2 = new Node(cond);
			// 
			// 				n->children.push_back(n1);
			// 				n->children.push_back(n2);
			// 			}
		}
	}
}

void Game_Tree::buildTree(int height)
{
	_buildTree(root, height, root->node_color);
}

int Game_Tree::numOfBranch()
{
	return _numOfBranch(root);
}

void Game_Tree::_buildTree(Node* n, int height, State color)
{
	findBranch(n, color);

	if(height - 1 > 0)
	{
		State new_color;
		if(color == BLACK)
			new_color = YELLOW;
		else
			new_color = BLACK;

		for(int i = 0; i < n->children.size(); i ++)
			_buildTree(n->children.at(i), height - 1, new_color);
	}
}

int Game_Tree::_numOfBranch(Node* n)
{
	int sum = 0;

	if(n->children.size() == 0)
		return 1;
	else
	{
		for(int i = 0; i < n->children.size(); i ++)
			sum += _numOfBranch(n->children.at(i));
	}

	return sum;
}

int Game_Tree::eval_node(Node* n, State color)
{
	int score = 0;
	for(int i = 0; i < n->board.size(); i ++)
	{
		for(int j = 0; j < n->board.at(i).size(); j ++)
		{
			if(n->board.at(i).at(j) == (State)(color + 2))
				score ++;
		}
	}
	n->score = score;
	return score;

}

int Game_Tree::eval_tree(Node* node, int height, State color)
{
	int max = 0;

	State our_color, other_color;

	if(color == YELLOW)
	{
		our_color = YELLOW;
		other_color = BLACK;
	}
	else
	{
		our_color = BLACK;
		other_color = YELLOW;
	}

	if(height == 0)
	{
		if(our_color == root->node_color)
			return node->score;
		else
			return -(node->score);
	}
	else
	{
		findBranch(node, our_color);

		if(node->children.size() != 0)
		{
			max = eval_tree(node->children.at(0), height - 1, other_color);

			for(int i = 1; i < node->children.size(); i ++)
			{
				int temp = eval_tree(node->children.at(i), height - 1, other_color);

				if(temp > max)
					max = temp;
			}
		}
	}

	if(our_color == root->node_color)
	{
		node->score = node->score + max;
		return node->score;
	}
	else
	{
		node->score = - (node->score) + max;
		return node->score;
	}
}

int Game_Tree::eval_tree(Node* node, int height, State color, int alpha, int beta)
{
	int max = 0;

	State our_color, other_color;

	if(color == YELLOW)
	{
		our_color = YELLOW;
		other_color = BLACK;
	}
	else
	{
		our_color = BLACK;
		other_color = YELLOW;
	}

	if(height == 0)
	{
		if(node->score > beta || node->score < alpha)
		{
			removeFormerTree(node);
			return OUT_OF_RANGE;
		}

		if(our_color == root->node_color)
			return node->score;
		else
			return -(node->score);
	}
	else
	{
		findBranch(node, our_color);

		if(node->children.size() != 0)
		{
			max = eval_tree(node->children.at(0), height - 1, other_color);

			for(int i = 1; i < node->children.size(); i ++)
			{
				int temp = eval_tree(node->children.at(i), height - 1, other_color);

				if(temp > max)
					max = temp;
			}
		}
	}

	if(our_color == root->node_color)
		node->score = node->score + max;
	else
		node->score = - (node->score) + max;

	if(node->score < alpha || node->score > beta)
	{
		removeFormerTree(node);
		return OUT_OF_RANGE;
	}
	else
	{
		return node->score;
	}
}

void Game_Tree::legal(vector<vector<State>>& board, State color)
{
	//Color settings
	State our_color;
	State other_color;

	//direction
	int a, b;

	bool done = false;

	if(color == BLACK)
	{
		our_color = BLACK;
		other_color = YELLOW;
	}
	else
	{
		our_color = YELLOW;
		other_color = BLACK;
	}

	for(int x = 0; x < GRID_SIZE; x++)
	{
		for(int y = 0; y < GRID_SIZE; y ++)
		{
			done = false;

			//if the position has been occupied, then skip
			if(board.at(x).at(y) == YELLOW || board.at(x).at(y) == BLACK)
				continue;
			else
			{
				//Diagonal
				a = x + 1;
				b = y + 1;

				if(a < GRID_SIZE && b < GRID_SIZE)
				{
					if(board.at(a).at(b) == other_color)
					{
						a ++, b ++;

						for(; a < GRID_SIZE && b < GRID_SIZE; a ++, b ++)
						{
							if(board.at(a).at(b) == our_color)
							{
								board.at(x).at(y) = (State)(our_color + 2); // Legal_our_color
								done = true;
								break;
							}
						}
					}
				}

				if(done)
					continue;

				a = x - 1;
				b = y - 1;
				if(a >= 0 && b >= 0)
				{
					if(board.at(a).at(b) == other_color)
					{
						a --, b --;

						for(; a >= 0 && b >= 0; a --, b --)
						{
							if(board.at(a).at(b) == our_color)
							{
								board.at(x).at(y) = (State)(our_color + 2);
								done = true; 
								break;
							}
						}
					}
				}

				if(done)
					continue;

				a = x - 1;
				b = y + 1;

				if(a >= 0 && b < GRID_SIZE)
				{
					if(board.at(a).at(b) == other_color)
					{
						a --, b ++;

						for(; a >= 0 && b < GRID_SIZE; a --, b ++)
						{
							if(board.at(a).at(b) == our_color)
							{
								board.at(x).at(y) = (State)(our_color + 2);
								done = true; 
								break;
							}
						}
					}
				}

				if(done)
					continue;

				a = x + 1;
				b = y - 1;

				if(a < GRID_SIZE && b >= 0)
				{
					if(board.at(a).at(b) == other_color)
					{
						a ++, b --;

						for(; a < GRID_SIZE && b >= 0; a ++, b --)
						{
							if(board.at(a).at(b) == our_color)
							{
								board.at(x).at(y) = (State)(our_color + 2);
								done = true;
								break;
							}
						}
					}
				}

				if(done)
					continue;

				//vertical
				a = x;
				b = y + 1;

				if(b < GRID_SIZE)
				{
					if(board.at(a).at(b) == other_color)
					{
						b ++;

						for(; b < GRID_SIZE; b ++)
						{
							if(board.at(a).at(b) == our_color)
							{
								board.at(x).at(y) = (State)(our_color + 2);
								done = true;
								break;
							}
						}
					}
				}

				if(done)
					continue;

				b = y - 1;
				if(b >= 0)
				{
					if(board.at(a).at(b) == other_color)
					{
						b --;

						for(; b > 0; b --)
						{
							if(board.at(a).at(b) == our_color)
							{
								board.at(x).at(y) = (State)(our_color + 2);
								done = true; 
								break;
							}
						}
					}
				}

				if(done)
					continue;

				//horizontal
				a = x + 1;
				b = y;

				if(a < GRID_SIZE)
				{
					if(board.at(a).at(b) == other_color)
					{
						a  ++;

						for(; a < GRID_SIZE; a ++)
						{
							if(board.at(a).at(b) == our_color)
							{
								board.at(x).at(y) = (State)(our_color + 2);
								done = true; 
								break;
							}
						}
					}
				}

				if(done)
					continue;

				a = x -1;

				if(a >= 0)
				{
					if(board.at(a).at(b) == other_color)
					{
						a --;

						for(; a >= 0; a --)
						{
							if(board.at(a).at(b) == our_color)
							{
								board.at(x).at(y) = (State)(our_color + 2);
								done = true; 
								break;
							}
						}
					}
				}

				if(done)
					continue;
				board.at(x).at(y) = State::EMPTY;
			}
		}
	}

	return ;
}

void Game_Tree::reverse(vector<vector<State>>& board, State color, int x, int y)
{
	//directoin
	int a, b;

	//color setting
	State our_color;
	State other_color	;

	if(color == YELLOW)
	{
		our_color = YELLOW;
		other_color = BLACK;
	}
	else
	{
		our_color = BLACK;
		other_color = YELLOW;
	}

	//Diagonal
	a = x + 1;
	b = y + 1;

	if(a < GRID_SIZE && b < GRID_SIZE)
	{
		if(board.at(a).at(b) == other_color)
		{
			a ++, b ++;
			for(; a < GRID_SIZE && b < GRID_SIZE; a ++, b ++) //need to reverse
			{
				if(board.at(a).at(b) == our_color)
					reverse_one_direction(board, color, x, y, 1, 1);
			}
		}
	}

	a = x - 1;
	b = y - 1;

	if( a >= 0 && b >= 0)
	{
		if(board.at(a).at(b) == other_color)
		{
			a --, b --;
			for(; a >= 0 && b >= 0; a --, b --) //need to reverse
			{
				if(board.at(a).at(b) == our_color)
					reverse_one_direction(board, color, x, y, -1, -1);
			} 
		}
	}

	a = x - 1;
	b = y + 1;

	if(a >= 0 && b < GRID_SIZE)
	{
		if(board.at(a).at(b) == other_color)
		{
			a --, b ++;
			for(; a >= 0 && b < GRID_SIZE; a --, b ++)
			{
				if(board.at(a).at(b) == our_color)
				{
					reverse_one_direction(board, color, x, y, -1, 1);
				}
			}
		}
	}

	a = x + 1;
	b = y - 1;

	if(a < GRID_SIZE && b >= 0)
	{
		if(board.at(a).at(b) == other_color)
		{
			a ++, b --;

			for(; a < GRID_SIZE && b >= 0; a ++, b --)
			{
				if(board.at(a).at(b) == our_color)
				{
					reverse_one_direction(board, color, x, y, 1, -1);
				}
			}
		}
	}

	//vertical
	a = x;
	b = y + 1;

	if(b < GRID_SIZE)
	{
		if(board.at(a).at(b) == other_color)
		{
			b ++;

			for(; b < GRID_SIZE; b ++)
			{
				if(board.at(a).at(b) == our_color)
				{
					reverse_one_direction(board, color, x, y, 0, 1);
				}
			}
		}
	}

	b = y - 1;
	if(b >= 0)
	{
		if(board.at(a).at(b) == other_color)
		{
			b --;

			for(; b > 0; b --)
			{
				if(board.at(a).at(b) == our_color)
				{
					reverse_one_direction(board, color, x, y, 0, -1);
				}
			}
		}
	}

	a = x + 1;
	b = y;

	if(a < GRID_SIZE)
	{
		if(board.at(a).at(b) == other_color)
		{
			a  ++;

			for(; a < GRID_SIZE; a ++)
			{
				if(board.at(a).at(b) == our_color)
				{
					reverse_one_direction(board, color, x, y, 1, 0);
				}
			}
		}
	}

	a = x -1;

	if(a >= 0)
	{
		if(board.at(a).at(b) == other_color)
		{
			a --;

			for(; a >= 0; a --)
			{
				if(board.at(a).at(b) == our_color)
				{
					reverse_one_direction(board, color, x, y, -1, 0);
				}
			}
		}
	}

}

void Game_Tree::reverse_one_direction(vector<vector<State>>& board, State color, int x, int y, int a, int b)
{
	State our_color, other_color;
	if(color == YELLOW)
	{
		our_color = YELLOW;
		other_color = BLACK;
	}
	else
	{
		our_color = BLACK;
		other_color = YELLOW;
	}

	board.at(x).at(y) = color;

	x += a;
	y += b;

	while(board.at(x).at(y) != our_color)
	{
		board.at(x).at(y) = our_color;

		x += a;
		y += b;
	}
}

string Game_Tree::print(vector<vector<State>> board)
{
	string s;

	s = ";  _ _ _ _ _ _ _ _\n";

	for(int i = 0; i < board.size(); i ++)
	{
		s+= ";";
		ostringstream stream;
		stream << s << i;
		s = stream.str();
		s+= "|";
		for (int j = 0; j < board[i].size(); ++j) {
			switch(board[i][j]) {
			case EMPTY:
				s+= "_";
				break;
			case YELLOW:
				s+= "0";
				break;
			case BLACK:
				s+= "X";
				break;
			case LEGAL_BLACK:
				s+= "B";
				break;

			case LEGAL_YELLOW:
				s+= "Y";
				break;
			default:
				s+= "_";
				break;
			}
			s+= "|";
		}
		s+= "\n";
	}
	s+= ";  a b c d e f g h\n\n";
	return s;
}


void Game_Tree::removeFormerTree(Node* node)
{
	if(node != NULL)
	{
		if(node->children.size() != 0)
		{
			for(int i = 0; i < node->children.size(); i ++)
				removeFormerTree(node->children.at(i));
		}

		delete node;
	}

	root = NULL;
}