

#include "Game_Client.h"

using namespace std;





Game_Client::Game_Client() {
	_e = Gamestate_Engine();

	player_color = YELLOW;

	myboard.resize(GRID_SIZE);
	for(int i = 0; i < GRID_SIZE; i ++)
	{
		myboard.at(i).resize(GRID_SIZE);

		for(int j = 0; j < GRID_SIZE; j ++)
		{
			myboard.at(i).at(7 - j).is_hovered = false;
			myboard.at(i).at(7 - j).my_state = _e._board.at(i).at(j);
			myboard.at(i).at(7 - j).pos.x = i;
			myboard.at(i).at(7 - j).pos.y = j;
			myboard.at(i).at(7 - j).is_updated = false;
		}
	}
}

void Game_Client::update()
{
	for(int i = 0; i < GRID_SIZE; i ++)
	{
		for(int j = 0; j < GRID_SIZE; j ++)
		{
			myboard.at(i).at(j).is_hovered = false;
		}
	}
}















