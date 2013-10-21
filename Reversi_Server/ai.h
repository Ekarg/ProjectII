// this is a general interface for all kinds of AI

#ifndef AI_H_
#define AI_H_

#include "stdafx.h"

using namespace std;

class AI
{
public: 
	virtual void current_status(vector<vector<State>> b	);
	virtual vector<vector<State>> next_status ();
};

#endif // 



