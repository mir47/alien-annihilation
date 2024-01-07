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
//	int windowWidth = 800;
//	int windowHeight = 700;
//
//	bool playGame = true;
//	while (playGame)
//	{
//		Game AlienAnnihilation (windowWidth, windowHeight);
//		playGame = AlienAnnihilation.RunGame();
//	}

	printf("main > Creating game\n");
	Game AlienAnnihilation;
	printf("main > Running game\n");
	bool gameRunning = true;
	while (gameRunning) {
		printf("game running...\n");
		gameRunning = AlienAnnihilation.RunGame();
	}
	printf("game stopped\n");

	return 0;
}
