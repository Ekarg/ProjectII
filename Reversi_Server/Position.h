
/* 
    File: Position.h

    Authors: Violeta Torres 
            Department of Computer Science
            Texas A&M University
			
    This file contains a class of Positions to be used for the move function  

*/

#include <iostream>
#include <string>
#include <map>
#include<vector>


class Position
{
private: 
	int row;
	int colum; 
	int value;
public: 
	Position(){}  // 
	Position(int r, int c, int v): row(r),colum(c), value(v){}
	int getColum(){return colum;}
	int getRow(){return row; }
	int getValue(){return value; }
};