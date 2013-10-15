/*
    File: game_state_engine.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains function definitions associated 
	with Gamestate_Engine class in file game_state_engine.h. 

*/

#include <stdio.h>
#include <stdlib.h>
#include <typeinfo>
#include <sstream>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <sstream>
#include "game_state_engine.h"
#include "Position.h"
#include <vector>

Gamestate_Engine::Gamestate_Engine() {
	_board.resize(GRID_SIZE);
	for (int i = 0; i < GRID_SIZE; ++i) {
		_board[i].resize(GRID_SIZE);
		for (int j = 0; j < GRID_SIZE; ++j) {
			_board[i][j] = EMPTY;
		}
	}
	_board[GRID_SIZE/2]     [e] = BLACK;
	_board[GRID_SIZE/2]     [d] = YELLOW;
	_board[(GRID_SIZE/2)-1] [d] = BLACK;
	_board[(GRID_SIZE/2)-1] [e] = YELLOW;
	
	_board[GRID_SIZE/2]     [e+1] = LEGAL_YELLOW;
	_board[GRID_SIZE/2-1]     [d-1] = LEGAL_YELLOW;
	
	_board[GRID_SIZE/2-1]     [e+1] = LEGAL_BLACK;
	_board[GRID_SIZE/2]     [d-1] = LEGAL_BLACK;
	
	_board[GRID_SIZE/2+1]     [e] = LEGAL_YELLOW;
	_board[GRID_SIZE/2+1]     [d] = LEGAL_BLACK;
	
	_board[(GRID_SIZE/2)-2] [d] = LEGAL_YELLOW;
	_board[(GRID_SIZE/2)-2] [e] = LEGAL_BLACK;
		
	//TEST CASE
	//_board[0] [h] = YELLOW;
}
	

bool Gamestate_Engine::move(std::string square_id) {
	//do work
	// Returns false if invalid, otherwise update _board to reflect move made
	// Simplistic parsing of two character move command should be done here
	// Insert move to played_moves for use with undo/redo
	// Input square_id is the chosen destination for moved piece 
	// Check is_play(); if false, game-over
	std::vector<Position>check; 
	std::vector<Position>first;
	std::vector<Position>diagonals;
	int row;
	int colum;
	int change = 0;
	int checkcolor=0;
	bool valid =  false; 
	bool vertical = false; 
	bool diagonal = false; 
	bool horizontal = false ;
	bool final = false; 
	//parse the command? 
	//square_id parse depending on which one i  the a or b 
	
	bool player = get_color();
	int playernum;
	
	if(player == true)
	{
	playernum = YELLOW ; // player is YELLOW
	checkcolor = BLACK;
	}
	if(player == false)
	{
	playernum == BLACK; 
	checkcolor = YELLOW;
	}

//________________________________________________
 // pasrsed string_id  the number is in row the letter is in colum
    stoi_loc(square_id,row, colum); 
//______________________________________________
 
 _board[row][colum] = (State) playernum;
 
 // check if it spot is not already taken 
 if(_board[row].at(colum)==0)
 {
 //first test is there another color beside this position 
 // look and see if there is another color besides yours around you; 
// there gots to be a color oposite to yours besides you 
		check.push_back(Position(row,colum,_board[row].at(colum-1)));
		check.push_back(Position(row,colum+1,_board[row].at(colum+1)));
		check.push_back(Position(row-1,colum-1,_board[row-1].at(colum-1)));
		check.push_back(Position(row-1,colum+1,_board[row-1].at(colum+1)));
		check.push_back(Position(row-1,colum,_board[row-1].at(colum)));
		check.push_back(Position(row+1,colum-1,_board[row+1].at(colum-1)));
		check.push_back(Position(row+1,colum+1,_board[row+1].at(colum+1)));
		check.push_back(Position(row+1,colum,_board[row+1].at(colum)));

//go through to see if it can find an opposite color 		
	for(int w = 0; w < check.size(); w++)
	{
	int k = check[w].getValue(); 
				if(k==checkcolor)// depending on the player the 2 can be a 1 or 2? 
				{
					std::cout<<"there is an opposite color besides you"<<std::endl; 
					std::cout<<checkcolor<<std::endl; 
					valid = true; 
					first.push_back(check[w]); 

				}
	}
    
	check.clear();
				if(valid == true)
				{
				//_board[row].at(colum)=playernum;


						for(int u = 0; u < first.size(); u++)
						{
						int rows = first[u].getRow();
						int colums = first[u].getColum(); 
						//check if there is a horizontal
							if(row==rows)
							{
								for(int s = 0; _board[row].size(); s++)
								{
									if(_board[row][s] == playernum && s != colum)
									{
									printf("valid move");
									horizontal = true; 
									change = s; 
									break; 
									}
								}
								if(colum>change)
								{

									for(int t = colum; t>change; t-- )
									{
									_board[row][t]=(State)playernum;
									}
								}

								if(colum<change)
								{
									for(int t = colum; t<change; t++ )
									{
									_board[row][t]=(State)playernum;
									}
								
								}	
								
							}
							else
							{
							printf("no Horizontal");
							}
						// check if there is a vertical	
							if(colum == colums)
							{
								for(int f = 0; f < _board.size(); f++)
								{
									if(_board[f][g]==playernum && m !=f)
									{
									printf("valid move"); 
									vertical = true; 
									change = f; 
									break; 
									}
								}
								if(row>change)
								{
									for(int q=row; q>change; q--)
									{
										_board[q][colum]=(State)player;
									}
								}

								if(row<change)
								{
									for(int q = row; q<= change; q++)
									{
									_board[q][colum]=(State)playernum;
									}
								}
							}
							else
							{
							printf("no Vertical");
							}
				
				// diagonal
							if(row != 0) // if the slot is not at the top
							{
								if(rows == row-1 && colums == colum-1)
								{
								diagonals.push_back(Position(rows,colums,_board[rows][colums]));
								int d = colum-2; // going current position left 
								
									for(int y = row-2; y <= 0; y--) // going current position up 
									{
										if(d<0 || y<0) break;
										
										if(_board[y][d] == playernum)
										{
										printf("valid");
										diagonal = true; 
										break; 
										}
										diagonals.push_back(Position(y,d,_board[y][d]));
										d--;
									}
									if(diagonal = true)
									{
										for(int i = 0; i< diagonals.size(); i++)
										{
											int r = diagonals[i].getRow(); 
											int c =diagonals[i].getColum();
											_board[r][c]=(State)playernum;

										}
									diagonals.clear();
									}
									else
									{
									diagonals.clear(); 
									}
								}
								else printf("no diagonal"); 
							//-----------------upper right diagonal--------------	
								if(rows == row-1 && colums == colum+1)
								{
									diagonals.push_back(Position(rows,colums,_board[rows][colums]));
									int j = colum+2; 
									for (int b=m-2; b<= 0; b--)
									{
										if(j==8||b<0) break; 
									
										if(_board[b][j]==playernum)
										{	
										diagonal= true;
										break; 
										}
									diagonals.push_back(Position(b,j,_board[b][j]));
									j++;
									}
								
								if(diagonal == true)
								{
									for(int i = 0; i< diagonals.size(); i++)
									{
										int r = diagonals[i].getRow(); 
										int c =diagonals[i].getColum();
										_board[r][c]=(State)playernum;

									}
								diagonals.clear();
								}
								else
								{
								diagonals.clear();
								}
								}
								else printf("no diagonal");
					//----------------lower left diagonal -------------------	
								if(rows == row+1 && colums == colum-1)
								{
								diagonals.push_back(Position(rows,colums,_board[rows][colums]));
									int l = colum-2;
									for(int c = m+2; c < 8; c++)
									{

										if(c==8||l<0)
										{
											break;
										}
									if(_board[c][l]==playernum)
										{
										printf("valid");
										diagonal=true;
										break; 
										}
									diagonals.push_back(Position(c,l,_board[c][l]));
									l--;
									}
									if(diagonal = true)
									{
										for(int i = 0; i< diagonals.size(); i++)
										{
											int r= diagonals[i].getRow(); 
											int c =diagonals[i].getColum();
											_board[r][c]=(State)playernum;

										}
								diagonals.clear();
									}
									else
									{
									diagonals.clear(); 
									}
									
								}
								else printf("no diagonal");
						//-----------lower right diagonal---------------------------		
								if(rows ==m+1 && colums ==g+1)
								{
								diagonals.push_back(Position(rows,colums,_board[rows][colums])); 
								int x= colum+2; 

								for(int c = row+2; c < 8; c++)
								{
								if(x==8||c==8)
								{
								break; 
								}

								if(_board[c][x]==playernum)
									{
									printf("valid");
									diagonal = true;
									break; 
									}
								diagonals.push_back(Position(c,x,_board[c][x]));
								x++;
								}
								
									if(diagonal = true)
									{
										for(int i = 0; i< diagonals.size(); i++)
										{
											int r = diagonals[i].getRow(); 
											int c =diagonals[i].getColum();
											_board[r][c]=(State)playernum;

										}
								diagonals.clear();
									}
									else
									{
									diagonals.clear();
									}
								}
								else printf("no diagonal");
								
							}
							else printf("no diagonal");
						//------------------upper left and upper right------------	
							if(row == 0)
							{
							//----------left---------------------
								if(rows == row+1 && colums == colum+1)
								{
									diagonals.push_back(Position(rows, colums, _board[rows][colums])); 
									int p = colum+2; 
									for(int v = row+2; v < 8; v++)
									{
										if(p>8) break;
											if(_board[v][p]==playernum)
											{
											printf("valid");
											diagonal = true; 
											break;
											}
											diagonals.push_back(Position(v,p,_board[v][p]));
											p++;
										
									}
									
									if(diagonal == true)
									{
											for(int i = 0; i< diagonals.size(); i++)
											{
												int r = diagonals[i].getRow(); 
												int c =diagonals[i].getColum();
												_board[r][c]=(State)playernum;

											}
									diagonals.clear();
									}

									else
									{
									diagonals.clear(); 
									}
								}
								else printf("no diagonal");
								//----------- right-----------------
								if(rows == row+1 && colums == colum-1)
								{
									diagonals.push_back(Position(rows,colums,_board[rows][colums]));
									int n = colum-2; 
									for(int v = m+2; v < 8; v++)
									{
											if(v==8||n<0)
											{
											break;
											}
										if(_board[v][n]==playernum)
										{
										printf("valid"); 
										diagonal = true;
										break; 
										}
										diagonals.push_back(Position(v,n,_board[v][n])); 
									 n--; 
									}
									
									if(diagonal == true)
									{
											for(int i = 0; i< diagonals.size(); i++)
											{
												int r = diagonals[i].getRow(); 
												int c =diagonals[i].getColum();
												_board[r][c]=(State)playernum;

											}
									diagonals.clear();
									}

									else
									{
									diagonals.clear(); 
									}
								
								}
								else printf("no diagonal");
							
							}
								if(diagonal == true || vertical == true || horizontal == true)
								{
								printf("legal move");
								final = true; 
								}
						
						}
						
												

				}
				
				else 
				{
				printf("invalid move");
				 final = false; 
				}
 }
 else
 {
printf("ERROR : spot %i %i is already taken ",row,colum);
final = false; 
 }
 
	
	return final;
}
bool Gamestate_Engine::unmove(std::string square_id) {
	//do work
	return true;
}

bool Gamestate_Engine::is_play() {
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			if ( is_legal_yellow(itos_loc(i, j)) || is_legal_black(itos_loc(i, j)) ) {
				return true;
			}
		}
	}
	return false;
}

bool Gamestate_Engine::undo_move() {
	//do work
	return true;
}

bool Gamestate_Engine::redo_move() {
	//do work
	return true;
}

bool Gamestate_Engine::is_legal_yellow(std::string square_id) {
	int x, y;
	stoi_loc(square_id, x, y);
	//std::cout << _board[x][y];
	if ( (_board[x][y] == LEGAL_YELLOW) || (_board[x][y] == LEGAL_BOTH) ) {
		return true;
	}
	return false;
}

bool Gamestate_Engine::is_legal_black(std::string square_id) {
	int x, y;
	stoi_loc(square_id, x, y);
	//std::cout << _board[x][y];
	if ( (_board[x][y] == LEGAL_BLACK) || (_board[x][y] == LEGAL_BOTH) ) {
		return true;
	}
	return false;
}

std::string Gamestate_Engine::print() {
	system("clear");
	// System call to clear screen 
	std::string s;
	s = ";  _ _ _ _ _ _ _ _\n";
	for (int i = 0; i < _board.size(); ++i) {
		s+= ";";
		//taken from stackoverflow forum
		std::ostringstream stream;
		stream << s << i;
		s = stream.str();
		s+= "|";
		for (int j = 0; j < _board[i].size(); ++j) {
			switch(_board[i][j]) {
				case EMPTY:
					s+= "_";
					break;
				case YELLOW:
					s+= "0";
					break;
				case BLACK:
					s+= "X";
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

std::string Gamestate_Engine::get_board() {
	std::stringstream ss;
	std::string s = "";
	for (int i = 0; i < GRID_SIZE; ++i) {
		for (int j = 0; j < GRID_SIZE; ++j) {
			ss << (int)_board[i][j];
			char a;
			ss >> a;
			s += a;
			s += " ";
		}
		s += "\n";
	}
	return s;
}

std::string Gamestate_Engine::itos_loc(int x, int y) {
	std::string s = "";
	if ( (x >= GRID_SIZE) || (y >= GRID_SIZE) ) {
		printf("ERROR : itos_loc(x, y) | x || y >= GRID_SIZE;\n");
		return s;
	}
	std::stringstream ss;
	ss << x;
	ss >> s;
	//Quick and dirty: Never ever ever ever do this.
	s += (char)(y+97);
	//Quick and dirty: Never ever ever ever do this.
	return s;
}

void Gamestate_Engine::stoi_loc(std::string s, int &x, int &y) {
	if (s.size() != 2) {
		printf("ERROR : stoi_loc(s, x, y) | s.size() != 2;\n");
		return;
	}
	std::string s_2 = "";
	s_2 += s[1];		// s_2 = y;
	s.erase(s.end()-1); // s = x;
	x = atoi(s.c_str());
	//Quick and dirty: Never ever ever ever do this.
	y = ((int)s_2[0]) - 97;
	//Quick and dirty: Never ever ever ever do this.
	if ( (x < 0) || (y < 0) || (x >= GRID_SIZE) || (y >= GRID_SIZE) ) {
		printf("ERROR : stoi_loc(s, x, y) | x and/or y out of bounds;\n");
		std::cout<<x<<" "<<y<<" "<<s<<std::endl;
	}
}

void Gamestate_Engine::set_color(std::string color)
{
	if(color == "YELLOW")
	{	
		player_color = true;
	}
	if(color == "BLACK")
	{
		player_color = false;
	}
}

int Gamestate_Engine::get_color() 
{
	return player_color;
}
















