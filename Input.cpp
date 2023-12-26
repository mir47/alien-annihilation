
#include <iostream>
#include "Input.h"
#include "Graphics.h"

using namespace std;


/*! Default constructor to create an instance of Input
*/
Input::Input()
{

}

/*! Checks for applicable keyboard inputs while the game is being played. Keyboard inputs are sensed from the Graphics class.
	\param gameGraphics : Object of Graphics that contains function for physically ckecking which key was pressed on the keyboard
	\return Action : an enumeration for what action needs to be performed depending on what key was pressed
*/
Action Input::InGame(Graphics& gameGraphics)
{
	Keyboard keyPressed = gameGraphics.CheckKeyboard();

	if (keyPressed != key_none)
	{
		switch (keyPressed)
		{										
			case key_left:
				return movePlayerLeft;
				break;

			case key_right:	
				return movePlayerRight;
				break;

			case key_space:
				return playerShoot;
				break;

			case key_esc:
				return pause;
 				break;
		}
	}

	return noAction;
}



/*! Checks for applicable keyboard inputs at the start menu. Keyboard inputs are sensed from the Graphics class.
	\param gameGraphics : Object of Graphics that contains function for physically ckecking which key was pressed on the keyboard
	\return Action : an enumeration for what action needs to be performed depending on what key was pressed
*/
Action Input::StartMenu(Graphics& gameGraphics)
{
	Keyboard keyPressed = gameGraphics.CheckKeyboard();

	if (keyPressed != key_none)
	{
		switch (keyPressed)
		{
			case key_l:
				return load;
				break;

			case key_q:
				return quit;
				break;

			case key_1:
				return settings_1;
				break;

			case key_2:
				return settings_2;
				break;

			case key_3:
				return settings_3;
				break;

		}

	}

	return noAction;

}




/*! Checks for applicable keyboard inputs at the pause menu. 
	\param gameGraphics : Object of Graphics that contains function for physically ckecking which key was pressed on the keyboard
	\return Action : an enumeration for what action needs to be performed depending on what key was pressed
*/
Action Input::PauseMenu(Graphics& gameGraphics)
{
	Keyboard keyPressed = gameGraphics.CheckKeyboard();

	if (keyPressed != key_none)
	{
		switch (keyPressed)
		{
			case key_esc:
				return resume;
 				break;

			case key_r:
				return restart;
				break;

			case key_s:
				return save;
				break;

			case key_q:
				return quit;
				break;

		}

	}

	return noAction;

}



/*! Checks for applicable keyboard inputs at the GAME OVER screen. 
	\param gameGraphics : Object of Graphics that contains function for physically ckecking which key was pressed on the keyboard
	\return Action : an enumeration for what action needs to be performed depending on what key was pressed
*/
Action Input::EndScreen(Graphics& gameGraphics)
{
	Keyboard keyPressed = gameGraphics.CheckKeyboard();

	if (keyPressed != key_none)
	{
		switch (keyPressed)
		{
			case key_enter:
				return restart;
				break;
		}

	}

	return noAction;

}


/*! Checks for applicable keyboard inputs at the screen shown after a game is loaded. 
	\param gameGraphics : Object of Graphics that contains function for physically ckecking which key was pressed on the keyboard
	\return Action : an enumeration for what action needs to be performed depending on what key was pressed
*/
Action Input::LoadScreen(Graphics& gameGraphics)
{
	Keyboard keyPressed = gameGraphics.CheckKeyboard();

	if (keyPressed != key_none)
	{
		switch (keyPressed)
		{
			case key_enter:
				return 	resume;
				break;
		}

	}

	return noAction;

}


