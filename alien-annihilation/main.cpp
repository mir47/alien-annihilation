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
	

//	bool playGame = true;
//	while (playGame)
//	{
//		Game AlienAnnihilation (windowWidth, windowHeight);
//		playGame = AlienAnnihilation.RunGame();
//	}




	printf("Creating game\n");
	Game AlienAnnihilation(windowWidth, windowHeight);
	printf("Running game\n");
	bool playGame = AlienAnnihilation.RunGame();
	if (playGame) {
		printf("playGame true\n");
	}
	else 
	{
		printf("playGame false\n");
	}


	return 0;

}