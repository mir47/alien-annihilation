/*
-------------------------------------------------------------------------

	main.cpp

-------------------------------------------------------------------------
*/

#include <iostream>
#include "Game.h"

using namespace std;


int main(int argc, char **argv)
{

	int windowWidth = 800;
	int windowHeight = 700;
	

	bool playGame = true;
	while (playGame)
	{
		Game AlienAnnihilation (windowWidth, windowHeight);
		playGame = AlienAnnihilation.RunGame();

	}

	


	return 0;

}