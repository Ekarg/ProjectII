/* 
    File: global_const.h

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    *---* DESCRIPTION *---*

*/

#ifndef _GLOBAL_CONST_
#define _GLOBAL_CONST_

#define OUT_OF_RANGE  32767

#define WINDOWWIDTH 480
#define WINDOWLENGTH 640

const int GRID_SIZE = 8;

//for openGL 
#define GRID_WIDTH 1
#define GRID_LENGTH 1

const unsigned int PORT = 4001;

enum State { EMPTY = 0, YELLOW = 1, BLACK = 2, LEGAL_YELLOW = 3, LEGAL_BLACK = 4, LEGAL_BOTH = 5};

#endif








