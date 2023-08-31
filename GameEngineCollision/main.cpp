#include "stdafx.h"
#include "Game.h"

int main()
{
	//Initialize random seed
	srand(static_cast<unsigned>(time(0)));

	//Initialize game
	Game game;

	game.run();

	//End of application
	return 0;
}