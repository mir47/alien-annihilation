#ifndef INPUT_H
#define INPUT_H

#include <iostream>
#include "Graphics.h"

using namespace std;


/*! Action is an enumeration containing the action to be performed depending on the user input at various stages in the game.
	This enum is used to clean up the transportation of the action to be performed for user inputs.
*/
enum Action
{
	noAction = 0,
	movePlayerLeft = 1,
	movePlayerRight,
	playerShoot,
	start,
	pause,
	resume,
	restart,
	save,
	load,
	quit,
	settings_1,
	settings_2,
	settings_3

};

//! Class implementation for Input
/*! Class that checks the keyboard inputs by the user at the various stages in the game
*/
class Input
{
public:
	//! Default constructor
	Input();

	//! Checks for applicable keyboard inputs while a level is in play
	Action InGame(Graphics& gameGraphics);

	//! Checks for applicable keyboard inputs at the start menu
	Action StartMenu(Graphics& gameGraphics);

	//! Checks for applicable keyboard inputs at the game pause menu
	Action PauseMenu(Graphics& gameGraphics);

	//! Checks for applicable keyboard inputs at the end (GAME OVER) screen
	Action EndScreen(Graphics& gameGraphics);

	//! Checks for applicable keyboard inputs while after a level is loaded
	Action LoadScreen(Graphics& gameGraphics);

};




#endif