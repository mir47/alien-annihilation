/*
-------------------------------------------------------------------------
	
	Graphics.cpp

-------------------------------------------------------------------------
*/

#include "SDL.h"
#include "SDL2_gfxPrimitives.h"
#include <SDL_ttf.h>
#include "Graphics.h"
#include "PlayerMissile.h"
#include "Game.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 700;

//!Default constructor which initializes all keyboard inputs to false
Graphics::Graphics()
{
	printf("Graphics::constructor called\n");

	for ( int i=0 ; i<323 ; i++ )
	{
		keysHeld[i] = false;		 // all keyboard inputs will be initialized to false
	}

	Initialise(SCREEN_WIDTH, SCREEN_HEIGHT);
}

/*! Constructor which accepts two parameters to set the various properties ot he SDL screen
\param windowWidth an integer which sets the width of the game window
\param windowHeight an integer which sets the height of the game window
*/
Graphics::Graphics(int windowWidth, int windowHeight)
{
	printf("Graphics::constructor with params called\n");

	// old way to set full screen
//	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF  | SDL_FULLSCREEN );
//	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	
	for (int i = 0; i < 323; i++)
	{
		keysHeld[i] = false;		 // all keyboard inputs will be initialized to false
	}

	Initialise(windowWidth, windowHeight);
}

//!Graphics class destructor which quits SDL
Graphics :: ~Graphics()
{
	printf("Graphics::destructor called\n");

	//Destroy window
	if (window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
}

void Graphics::Initialise(int screenWidth, int screenHeight)
{
	printf("Graphics::Initialise called\n");

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		//Create window
		window = SDL_CreateWindow("Alien Annihilation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Create renderer
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (renderer == NULL)
			{
				printf("Renderer could not be setup! SDL_Error: %s\n", SDL_GetError());
			}
		}
	}
}

//! Function to check which keys have been pressed on the keyboard
Keyboard Graphics::CheckKeyboard()
{
	printf("Graphics::CheckKeyboard\n");

	int poll = SDL_PollEvent(&event);

	if (poll)
	{
		printf("Graphics::CheckKeyboard -> SDL_PollEvent\n");

		if (event.type == SDL_QUIT)
		{
			printf("Graphics::CheckKeyboard -> quit\n");
			return key_q;
		}

		if (event.type == SDL_KEYDOWN)
		{
			keysHeld[event.key.keysym.sym] = true;

			if (event.key.keysym.sym == SDLK_SPACE)
				return key_space;
			if (event.key.keysym.sym == SDLK_ESCAPE)
				return key_esc;
			if (event.key.keysym.sym == SDLK_RETURN)
				return key_enter;
			if (event.key.keysym.sym == SDLK_r)
				return key_r;
			if (event.key.keysym.sym == SDLK_q) {
				printf("Graphics::CheckKeyboard -> key q\n");
				return key_q;
			}
			if (event.key.keysym.sym == SDLK_s)
				return key_s;
			if (event.key.keysym.sym == SDLK_l)
				return key_l;
			if (event.key.keysym.sym == SDLK_1)
				return key_1;
			if (event.key.keysym.sym == SDLK_2)
				return key_2;
			if (event.key.keysym.sym == SDLK_3)
				return key_3;
		}

		if (event.type == SDL_KEYUP)
		{
			keysHeld[event.key.keysym.sym] = false;
		}
	}

//	bool left = keysHeld[SDLK_LEFT];
//	printf("Graphics::CheckKeyboard > left=%d\n", left);
//	bool right = keysHeld[SDLK_RIGHT];
//	printf("Graphics::CheckKeyboard > right=%d\n", right);

	//if (keysHeld[SDLK_LEFT])
	//{
	//	printf("Graphics::CheckKeyboard > SDLK_LEFT\n");
	//	return key_left;
	//}
	//else if (keysHeld[SDLK_RIGHT])
	//{
	//	printf("Graphics::CheckKeyboard > SDLK_RIGHT\n");
	//	return key_right;
	//}

	return key_none;
}

/*! Function that draws all elements on the screen
\param gameBattlefield a Battlefield type
\param gamePlayerShip a PlayerShip type
\param AlienShipVector a vector of type AlienShip
\param PlayerMissilesVector a vector of type PlayerMissile
\param AlienMissilesVector a vector of type AlienMissile
*/
void Graphics::DrawScreen(
	Battlefield& gameBattlefield,
	PlayerShip& gamePlayerShip, 
	vector<AlienShip>& AlienShipVector,
	vector<PlayerMissile>& PlayerMissilesVector,
	vector<AlienMissile>& AlienMissilesVector)
{
	printf("Graphics::DrawScreen\n");
	ClearScreen();

	for ( int i=0 ; i<50 ; i++ )
	{
		DrawRandomStar();
	}

	DrawBattlefield(gameBattlefield);
	DrawAlienShips (AlienShipVector);
	DrawPlayerMissiles (PlayerMissilesVector);
	DrawAlienMissiles (AlienMissilesVector);
	DrawPlayerShip (gamePlayerShip);
	DrawPlayerScore (gamePlayerShip);

	RevealScreen();
}

/*!Function to draw the start menu of the game

*/
void Graphics::DrawStartMenu()
{
	printf("Graphics::DrawStartMenu\n");
	ClearScreen();

	for ( int i=0 ; i<50 ; i++ )
	{
		DrawRandomStar();
	}

	// Set render color to red (rect will be rendered in this color)
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

	// Creat rect
	SDL_Rect r;
	r.x = SCREEN_WIDTH / 6;
	r.y = SCREEN_HEIGHT / 3;
	r.w = 4 * (SCREEN_WIDTH / 6);
	r.h = 2 * (SCREEN_HEIGHT / 3) - 50;

	// Render rect
//	SDL_RenderFillRect(renderer, &r);
	SDL_RenderDrawRect(renderer, &r);

	r.x = r.x + 10;
	r.y = r.y + 10;
	r.w = r.w - 20;
	r.h = r.h - 20;
	SDL_RenderDrawRect(renderer, &r);

	int titleX = SCREEN_WIDTH / 4;
	int titleY = 50;

	char s2[] = "Alien Annihilation";
	DrawText(s2, titleX, titleY);
	char s3[] = "v1.0";
	DrawText(s3, titleX, titleY + 30);
	char s4[] = "Copyright 2007";
	DrawText(s4, titleX, titleY + 60);

	char argument4[] = "Andrew Russell";
	DrawText(argument4, titleX, titleY + 110);
	char argument5[] = "Miroslav Minev";
	DrawText(argument5, titleX, titleY + 140);

	int optionsX = titleX - 30;
	int optionsY = SCREEN_HEIGHT / 2 - 50;

	char argument6[] = "1 = play Level 1: rookie";
	DrawText(argument6, optionsX, optionsY);
	char argument7[] = "2 = play Level 2: experienced";
	DrawText(argument7, optionsX, optionsY + 30);
	char argument8[] = "3 = play Level 3: vetran";
	DrawText(argument8, optionsX, optionsY + (2 * 30));
	char argument9[] = "l = load saved game";
	DrawText(argument9, optionsX, optionsY + (3 * 30));
	char argument10[] = "q = quit";
	DrawText(argument10, optionsX, optionsY + (4 * 30));

	char argument11[] = "In-Game keys:";
	DrawText(argument11, optionsX, optionsY + (6 * 30));
	char argument12[] = "Left and Right arrow keys to move";
	DrawText(argument12, optionsX, optionsY + (7 * 30));
	char argument13[] = "Space to shoot";
	DrawText(argument13, optionsX, optionsY + (8 * 30));
	char argument14[] = "Escape to go to Pause menu";
	DrawText(argument14, optionsX, optionsY + (9 * 30));

	RevealScreen();
}

/*!Function to draw the start menu of the game

*/
void Graphics::DrawPauseMenu()
{
    boxRGBA(renderer, SCREEN_WIDTH /2-120, SCREEN_HEIGHT/2-60, SCREEN_WIDTH /2+120, SCREEN_HEIGHT /2+60, 100, 100, 100, 200);

	char argument1[] = "Paused";
	stringRGBA(renderer, SCREEN_WIDTH /2-25, SCREEN_HEIGHT /2-40, argument1, 255, 255, 255, 255);
 
	char argument2[] = "ESC = resume";
	stringRGBA(renderer, SCREEN_WIDTH /2-80, SCREEN_HEIGHT /2-20, argument2, 255, 255, 255, 255);
	char argument3[] = "r = return to main menu";
	stringRGBA(renderer, SCREEN_WIDTH /2-80, SCREEN_HEIGHT /2-10, argument3, 255, 255, 255, 255);
	char argument4[] = "s = save";
	stringRGBA(renderer, SCREEN_WIDTH /2-80, SCREEN_HEIGHT /2+0, argument4, 255, 255, 255, 255);
	char argument5[] = "q = quit";
	stringRGBA(renderer, SCREEN_WIDTH /2-80, SCREEN_HEIGHT /2+10, argument5, 255, 255, 255, 255);

	RevealScreen();
}

/*!Function to clear the entire screen

*/
void Graphics::ClearScreen()
{
	// Set render color to black (background will be rendered in this color)
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

	// Clear window
	SDL_RenderClear(renderer);
}

/*!Function to draw the entrie Battlefield
\param gameBattlefield a variable of type Battlefield
*/
void Graphics::DrawBattlefield(Battlefield& gameBattlefield)
{
	printf("Graphics::DrawBattlefield\n");

	DrawCircles(gameBattlefield);
	DrawLines(gameBattlefield);
}

/*!Function to draw the circles of the Battlefield
\param gameBattlefield a variable of type Battlefield
*/
void Graphics::DrawCircles(Battlefield& gameBattlefield)
{
	vector<Circle> vecCircles = gameBattlefield.get_vectorBattlefieldCircles();
	vector<Circle>::iterator circlesVecIter;
	circlesVecIter = vecCircles.begin();

	while (circlesVecIter != vecCircles.end())
	{
		// Draw circle (stored in battlefieldCirclesVector) pointed to by circlesVecIter
		DrawSingleCircle(
			circlesVecIter->centre_x,
			circlesVecIter->centre_y,
			circlesVecIter->radius_x,
			circlesVecIter->radius_y,
			circlesVecIter->colour_red,
			circlesVecIter->colour_green,
			circlesVecIter->colour_blue,
			circlesVecIter->colour_transparency
		);

		circlesVecIter++;
	}
}

/*!Function to draw the lines of the Battlefield
\param gameBattlefield a variable of type Battlefield
*/
void Graphics::DrawLines(Battlefield& gameBattlefield)
{
	vector<Line> vecLines = gameBattlefield.get_vectorBattlefieldLines();
	vector<Line>::iterator linesVecIter;
	linesVecIter = vecLines.begin();

	while (linesVecIter != vecLines.end())
	{
		// Draw line (stored in workingBattlefieldLinesVector) pointed to by linesVecIter
		DrawSingleLine(linesVecIter->start_x,		linesVecIter->start_y,
						linesVecIter->end_x,		linesVecIter->end_y,
						linesVecIter->colour_red,	linesVecIter->colour_green,
						linesVecIter->colour_blue,	linesVecIter->colour_transparency);
		linesVecIter++;
	}
}

/*!Function to draw the Player ship
\param gamePlayerShip a variable of type PlayerShip
*/
void Graphics::DrawPlayerShip(PlayerShip& gamePlayerShip)
{
	DrawFilledEllipse(
		gamePlayerShip.get_coordinate_x(),
		gamePlayerShip.get_coordinate_y(),
		gamePlayerShip.get_sizeRadius_x(),
		gamePlayerShip.get_sizeRadius_y(),
		gamePlayerShip.get_colourRed(),
		gamePlayerShip.get_colourGreen(),
		gamePlayerShip.get_colourBlue(),
		gamePlayerShip.get_colourTransparency()
	);
}

/*!Function to draw the Player ships score
\param gamePlayerShip a variable of type PlayerShip
*/
void Graphics::DrawPlayerScore(PlayerShip& gamePlayerShip)
{
	stringstream out;
	if (gamePlayerShip.get_score() >= 0)
	{
		out << gamePlayerShip.get_score();
	}
	else
	{
		out << 0;
	}

	char scoreText[] = "score: ";
	DrawText(scoreText, 30, 30);

	char scoreValue[10];
	strcpy_s(scoreValue, out.str().c_str());
	DrawText(scoreValue, 30, 60);
}

/*!A function to iterate through the vector of the alien ships and drsw each alien to the screen
\param AlienShipVector a vector containing instances of type AlienShip
*/
void Graphics::DrawAlienShips(vector<AlienShip>& AlienShipVector)
{
	vector<AlienShip>::iterator alienShipVecIter;
	alienShipVecIter = AlienShipVector.begin();

	while (alienShipVecIter != AlienShipVector.end())
	{
		if (alienShipVecIter->get_state())
		{
			DrawFilledEllipse ( alienShipVecIter -> get_coordinate_x(),	alienShipVecIter -> get_coordinate_y(),
								alienShipVecIter -> get_sizeRadius_x(),	alienShipVecIter -> get_sizeRadius_y(),
								alienShipVecIter -> get_colourRed(),	alienShipVecIter -> get_colourGreen(), 
								alienShipVecIter -> get_colourBlue(),	alienShipVecIter -> get_colourTransparency() );
		}
		alienShipVecIter++;
	}
}

/*!Function to draw a single circle to the screen
\param centre_x an integer that specifies the centre x coordinate of the circle
\param centre_y an integer that specifies the centre y coordinate of the circle
\param radius_x an integer that specifies the x radius of the circle
\param radius_y an integer that specifies the y radius of the circle
\param red an integer that specifies the red colour component of the circle
\param green an integer that specifies the green colour component of the circle
\param blue an integer that specifies the blue colour component of the circle
\param transparency an integer that specifies the transparency colour component of the circle
*/
void Graphics::DrawSingleCircle(
	int centre_x,
	int centre_y,
	int radius_x,
	int radius_y,
	int red,
	int green,
	int blue,
	int transparency
)
{
	ellipseRGBA(renderer, centre_x, centre_y, radius_x, radius_y, red, green, blue, transparency);
}

/*!Function to draw a single circle to the screen
\param x1 an integer that specifies the start x coordinate of the line
\param y1 an integer that specifies the start y coordinate of the line
\param x2 an integer that specifies the end x coordinate of the line
\param y2 an integer that specifies the end y coordinate of the line
\param red an integer that specifies the red colour component of the line
\param green an integer that specifies the green colour component of the line
\param blue an integer that specifies the blue colour component of the line
\param transparency an integer that specifies the transparency colour component of the line
*/
void Graphics::DrawSingleLine(
	int x1,
	int y1,
	int x2,
	int y2,
	int red,
	int green,
	int blue,
	int transparency
)					 
{
	lineRGBA(renderer, x1, y1, x2, y2, red, green, blue, transparency);
}

/*!Function to draw a single filled ellipse to the screen
\param centre_x an integer that specifies the centre x coordinate of the circle
\param centre_y an integer that specifies the centre y coordinate of the circle
\param radius_x an integer that specifies the x radius of the circle
\param radius_y an integer that specifies the y radius of the circle
\param red an integer that specifies the red colour component of the circle
\param green an integer that specifies the green colour component of the circle
\param blue an integer that specifies the blue colour component of the circle
\param transparency an integer that specifies the transparency colour component of the circle
*/
void Graphics::DrawFilledEllipse(
	int centre_x,
	int centre_y,
	int radius_x,
	int radius_y,
	int red,
	int green,
	int blue,
	int transparency
)
{
	filledEllipseRGBA(renderer, centre_x, centre_y, radius_x, radius_y, red, green, blue, transparency);
}

void Graphics::DrawText(char* text, int x, int y)
{
	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
	}
	else {
		TTF_Font* font = TTF_OpenFont("assets/white-rabbit.ttf", 24);
		if (font == NULL)
		{
			printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
		}
		else
		{
			SDL_Color White = { 255, 255, 255 };
			SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, White);
			if (textSurface == NULL)
			{
				printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
			}
			else
			{
				SDL_Rect textRect;
				int width = textSurface->w;
				int height = textSurface->h;
				textRect.x = x;
				textRect.y = y;
				textRect.w = width;
				textRect.h = height;

				SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
				if (textTexture == NULL)
				{
					printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
				}
				else
				{
					SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
				}

				SDL_FreeSurface(textSurface);
				if (textTexture != NULL)
				{
					SDL_DestroyTexture(textTexture);
				}
			}
			TTF_CloseFont(font);
		}
	}
}

/*!Draw objects on screen

*/
void Graphics::RevealScreen()
{
	SDL_RenderPresent(renderer);
	SDL_Delay(100);
}

void Graphics::BlockScreen()
{
	printf("Graphics::BlockScreen\n");

	// Hack to get window to stay up
	SDL_Event e;
	bool quit = false;
	while (quit == false)
	{
		while (SDL_PollEvent(&e))
		{
//			printf("in SDL_PollEvent\n");
			if (e.type == SDL_QUIT) {
				printf("event SDL_QUIT\n");
				quit = true;
			}
		}
	}
}

/*!A function to iterate through the vector of the player missiles and drsw each missile to the screen
\param PlayerMissilesVector a vector containing instances of type PlayerMissile
*/
void Graphics::DrawPlayerMissiles(vector<PlayerMissile>& PlayerMissilesVector)
{
	vector<PlayerMissile>::iterator PlayerMissilesVecIter;
	PlayerMissilesVecIter = PlayerMissilesVector.begin();

	while ( PlayerMissilesVecIter != PlayerMissilesVector.end() )
	{
		if (PlayerMissilesVecIter->get_state())
		{
			DrawFilledEllipse (	PlayerMissilesVecIter->get_coordinate_x(), PlayerMissilesVecIter->get_coordinate_y(),
								PlayerMissilesVecIter->get_sizeRadius_x(), PlayerMissilesVecIter->get_sizeRadius_y(),
								PlayerMissilesVecIter->get_colourRed(),	   PlayerMissilesVecIter->get_colourGreen(),
								PlayerMissilesVecIter->get_colourBlue(),   PlayerMissilesVecIter->get_colourTransparency());
							// since the missiles are circles, exactly like the ships
		}
		PlayerMissilesVecIter++;
	}
}

/*!A function to iterate through the vector of the alien missiles and drsw each missile to the screen
\param AlienMissilesVector a vector containing instances of type AlienMissile
*/
void Graphics::DrawAlienMissiles(vector<AlienMissile>& AlienMissilesVector)
{
	vector<AlienMissile>::iterator AlienMissilesVecIter;
	AlienMissilesVecIter = AlienMissilesVector.begin();

	while ( AlienMissilesVecIter != AlienMissilesVector.end() )
	{
		{
			DrawFilledEllipse (	AlienMissilesVecIter->get_coordinate_x(), AlienMissilesVecIter->get_coordinate_y(),
								AlienMissilesVecIter->get_sizeRadius_x(), AlienMissilesVecIter->get_sizeRadius_y(),
								255,0,
								0, 255);
		}
		AlienMissilesVecIter++;
	}
}

/*!A function to draw the game over condition to the screen
\param gameBattlefield an instance of type Battlefield
\param gameEnd an instance of type WinCondition
*/
void Graphics::DrawGameOver(Battlefield& gameBattlefield,  WinCondition gameEnd)
{
	switch (gameEnd)
	{
		case AllAliensDestroyed:
			DrawEnd_AllAliensDestroyed();
			break;

		case AliensOnOuterCircle:
			DrawEnd_AliensOnOuterCircle();
			break;

		case PlayerDestroyed:
			DrawEnd_PlayerDestroyed();
			break;
	}

	RevealScreen();
}

/*!A function to draw the game over condition which correspond to the case where all the aliens are destroyed*/
void Graphics::DrawEnd_AllAliensDestroyed()
{
	boxRGBA(renderer, SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 60, SCREEN_WIDTH / 2 + 190, SCREEN_HEIGHT / 2 + 60, 0, 255, 0, 150);

	char argument1[] = "You Win! - all alien ships heve been destroyed";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 20, argument1, 255, 255, 255, 255);

	char argument2[] = "Press enter to continue";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 20, argument2, 255, 255, 255, 255);
}

/*!A function to draw the game over condition which correspond to the case where the aliens have reached the player base*/
void Graphics::DrawEnd_AliensOnOuterCircle()
{
	boxRGBA(renderer, SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 60, SCREEN_WIDTH / 2 + 190, SCREEN_HEIGHT / 2 + 60, 255, 0, 0, 150);

	char argument1[] = "GAME OVER - the aliens have invaded your base";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 180, SCREEN_HEIGHT / 2 - 20, argument1, 255, 255, 255, 255);

	char argument2[] = "Press enter to continue";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 20, argument2, 255, 255, 255, 255);
}

/*!A function to draw the game over condition which correspond to the case where the player ship is destroyed*/
void Graphics::DrawEnd_PlayerDestroyed()
{
	boxRGBA(renderer, SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 60, SCREEN_WIDTH / 2 + 190, SCREEN_HEIGHT / 2 + 60, 255, 0, 0, 150);

	char argument1[] = "GAME OVER - you have been destroyed";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 140, SCREEN_HEIGHT / 2 - 20, argument1, 255, 255, 255, 255);

	char argument2[] = "Press enter to continue";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 20, argument2, 255, 255, 255, 255);
}

/*!A function to draw the condition which correspond to the case where a game has not been succesfully loaded*/
void Graphics::DrawLoadError()
{
	boxRGBA(renderer, SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 60, SCREEN_WIDTH / 2 + 190, SCREEN_HEIGHT / 2 + 60, 255, 0, 0, 255);

	char argument1[] = "No saved games";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 20, argument1, 255, 255, 255, 255);

	char argument2[] = "Press enter to continue";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 20, argument2, 255, 255, 255, 255);

	RevealScreen();
}

/*!A function to draw the condition which correspond to the case where a game has been succesfully loaded*/
void Graphics::DrawLoadCorrect()
{
	boxRGBA(renderer, SCREEN_WIDTH / 2 - 190, SCREEN_HEIGHT / 2 - 60, SCREEN_WIDTH / 2 + 190, SCREEN_HEIGHT / 2 + 60, 0, 255, 0, 255);

	char argument1[] = "Saved game loaded";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 70, SCREEN_HEIGHT / 2 - 20, argument1, 255, 255, 255, 255);

	char argument2[] = "Press enter to play";
	stringRGBA(renderer, SCREEN_WIDTH / 2 - 90, SCREEN_HEIGHT / 2 + 20, argument2, 255, 255, 255, 255);

	RevealScreen();
}

//!A function to draw random stars on the screen
void Graphics::DrawRandomStar()
{
	int x = rand()%SCREEN_WIDTH;
	int y = rand()%SCREEN_HEIGHT;
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawPoint(renderer, x, y);
}
