/* 
    File: store_moves.cpp

    Authors: Grace Coffman, Sidian Wu, Alejandro Vega, Violeta Torres, Wesley Tang
            Department of Computer Science
            Texas A&M University
			
    *---* DESCRIPTION *---*

*/

/* 
	messy way of storing all possible moves to check move validity when user enters one, don't know how a tokenizer will help
	we still need to check the validity of the moves.  
*/

#include <iostream> 
#include <vector>
#include <string>
#include <sstream>
using namespace std;

string convert(int input)
 {
	int Number = input;       // number to be converted to a string
	string Result;          // string which will contain the result
	ostringstream convert;   // stream used for the conversion
	convert << Number;      // insert the textual representation of 'Number' in the characters in the stream
	Result = convert.str();
	return Result; 
}
 
int main ()
{
	vector<string> moves; 
	int x = 97; //letters a - h
	int y = 0; //numbers 1 - 7
	
	for(int i = 0; x <= 104; i++)
	{
		for(int j = 0; y <=7 ; j++)
		{
				string temp = "";
				char a = (char)x;
				//cout << a << endl;
				temp += a;
				//cout << y << endl;
				temp += convert(y);
				cout << temp << endl;
				moves.push_back(temp);
				y++;
		}
		 if(y = 7)
		 {
			y = 0;
			x++;
		 }
	
	}

	return 0;
	


}