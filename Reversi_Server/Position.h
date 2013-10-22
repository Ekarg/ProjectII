
/* 
    File: Position.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    This file contains a class of Positions to be used for the move function  

*/

#include <iostream>
#include <string>
#include <map>
#include<vector>
#include "global_const.h"

class Position
{
private: 
	int row;
	int colum; 
	State value;
public: 
	Position(){}  // 
	Position(int r, int c, State v): row(r),colum(c), value(v){}
	int getColum(){return colum;}
	int getRow(){return row; }
	State getValue(){return value; }
};