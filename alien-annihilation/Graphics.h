/*
-------------------------------------------------------------------------
	
	Graphics.h

-------------------------------------------------------------------------
*/

#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <vector>
#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "Battlefield.h"
#include "PlayerShip.h"
#include "PlayerMissile.h"
#include "AlienShip.h"
#include "AlienMissile.h"

/*! An enumeration to represent the three win conditions for understandable transportation
*/
enum WinCondition
{
	PlayerDestroyed = 1,
	AllAliensDestroyed,
	AliensOnOuterCircle
};

/*! An enumeration to represent which key has been pressed on the input
*/
enum Keyboard
{
	key_none = 0,
	key_left = 1,
	key_right,
	key_space,
	key_s,
	key_l,
	key_enter,
	key_esc,
	key_r,
	key_q,
	key_1,
	key_2,
	key_3
};

//! Class implementation for the game's Graphics and display functions
/*! Graphics class contains all the graphical implementation for drawing various SDL primitives on the screen and detecting physical keyboard button pressing.
*/
class Graphics 
{
public:

	//! Default constructor
	Graphics ();
	//! Constructor with parameters
	Graphics (int width, int height);
	//! Destructor
	~Graphics();

	void Initialise(int screenWidth, int screenHeight);

	//! Returns a Keyboard enum depending on which key on the keyboard is pressed
	Keyboard CheckKeyboard();
	//! Calls individual functions to draw all the objects in the game
	void DrawScreen(Battlefield& gameBattlefield, PlayerShip& gamePlayerShip, vector<AlienShip>& AlienShipVector, 
					vector<PlayerMissile>& PlayerMissilesVector, vector<AlienMissile>& AlienMissilesVector);
	//! Draws the user interface of the start menu
	void DrawStartMenu();
	//! Draws the user interface of the menu shown when the game is paused
	void DrawPauseMenu();
	//! Draws a certain graphic depending on which of the 3 win conditions has occured
	void DrawGameOver(Battlefield& gameBattlefield, WinCondition gameEnd);
	//! Draws a specific graphic when the game is over (condition: all aliens are destroyed, player wins)
	void DrawEnd_AllAliensDestroyed();
	//! Draws a specific graphic when the game is over (condition: one of the aliens has reached the outer circle, player loses)
	void DrawEnd_AliensOnOuterCircle();
	//! Draws a specific graphic when the game is over (condition: playership is destroyed, player loses)
	void DrawEnd_PlayerDestroyed();

	//! Draws a specific graphic if an error occurs when attempting to load a level
	void DrawLoadError();
	//! Draws a specific graphic if level is loaded successfully
	void DrawLoadCorrect();

private:
		// Private member functions
	//! Draws a single circle on the screen depending on what parameters are passed to it
	void DrawSingleCircle(int centre_x, int centre_y, int radius_x, int radius_y,
						  int red, int green, int blue, int transparency);
	//! Draws a single line on the screen depending on what parameters are passed to it
	void DrawSingleLine(int x1, int y1, int x2, int y2,
						int red, int green, int blue, int transparency);
	//! Draws a filled ellipse on the screen depending on what parameters are passed to it
	void DrawFilledEllipse(int centre_x, int centre_y, int radius_x, int radius_y,
						   int red, int green, int blue, int transparency);
	void DrawText(char* text, int x, int y);

	//! Clears the current screen that is being displayed
	void ClearScreen();
	//! Reveals the newly drawn screen
	void RevealScreen();
	//! This function calls functions to draw the Battlefield lines and circles
	void DrawBattlefield (Battlefield& gameBattlefield);
	//! Iterates through the vector of circles and calls a function to draw each one to the screen
	void DrawCircles (Battlefield& gameBattlefield);
	//! Iterates through the vector of lines and calls a function to draw each one to the screen
	void DrawLines (Battlefield& gameBattlefield);
	//! Calls a function to draw the PlayerShip
	void DrawPlayerShip (PlayerShip& gamePlayerShip);
	//! Iterates through the vector of AlienShips and calls a function to draw each one to the screen
	void DrawAlienShips (vector<AlienShip>& AlienShipVector);
	//! Iterates through the vector of PlayerMissiles and calls a function to draw each one to the screen
	void DrawPlayerMissiles (vector<PlayerMissile>& PlayerMissilesVector);
	//! Iterates through the vector of AlienMissiles and calls a function to draw each one to the screen
	void DrawAlienMissiles (vector<AlienMissile>& AlienMissilesVector);
	//! Converts the player score from an integer to a string and draws it on the screen
	void DrawPlayerScore (PlayerShip& gamePlayerShip);

	//! Function to draw a star at a random x and y position on the screen (within the screen size limits)
	void DrawRandomStars();

		// Private data members
	SDL_Window* window; // The window we will be rendering to
//	SDL_Surface* screen; //!< stores a pointer to the SDL_Surface that all graphics will be drawn to
	// SDL surface vs renderer: https://gamedev.stackexchange.com/questions/180077/in-sdl-what-is-the-difference-between-using-a-surfaces-and-a-renderer
	// TLDR: renderer runs on GPU, surface runs on CPU, so use render.
	SDL_Renderer* renderer;
	SDL_Event event; //!< event is an object of SDL_Event class, used for sensing keyboard events

	const char* WINDOW_TITLE; //!< stores the name that appears at the title bar of the window
	int WINDOW_WIDTH; //!< stores the window's width
    int WINDOW_HEIGHT; //!< stores the window's height
	
	bool keysHeld[323]; //!< an array of all the keys on the keyboard

};

#endif
