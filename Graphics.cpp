/*
-------------------------------------------------------------------------
	
	Graphics.cpp

-------------------------------------------------------------------------
*/

#include "SDL.h"
#include "SDL_gfxPrimitives.h"
#include "Graphics.h"
#include "PlayerMissile.h"
#include "Game.h"
#include <iostream>
#include <sstream>

using namespace std;

//!Default constructor which initializes all keyboard inputs to false
Graphics::Graphics()
{
	for ( int i=0 ; i<323 ; i++ )
	{
		keysHeld[i] = false;		 // all keyboard inputs will be initialized to false
	}

}

/*! Constructor which accepts two parameters to set the various properties ot he SDL screen
\param windowWidth an integer which sets the width of the game window
\param windowHeight an integer which sets the height of the game window
*/
Graphics::Graphics (int& windowWidth, int& windowHeight)
{
	WINDOW_WIDTH = windowWidth;
	WINDOW_HEIGHT = windowHeight;
	WINDOW_TITLE = "Alien Annihilation";

	SDL_Init( SDL_INIT_VIDEO );

	// decomment for full screen
//	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF  | SDL_FULLSCREEN );
	screen = SDL_SetVideoMode( WINDOW_WIDTH, WINDOW_HEIGHT, 0, SDL_HWSURFACE | SDL_DOUBLEBUF);
	SDL_WM_SetCaption( WINDOW_TITLE, 0 );
	
	for ( int i=0 ; i<323 ; i++ )
	{
		keysHeld[i] = false;		 // all keyboard inputs will be initialized to false
	}

}
//!Graphics class destructor which quits SDL
Graphics :: ~Graphics()
{
	SDL_Quit();		
}


//! Function to check which keys have been pressed on the keyboard
Keyboard Graphics::CheckKeyboard()
{
	if (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
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
			if (event.key.keysym.sym == SDLK_q)
				return key_q;
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


	if ( keysHeld[SDLK_LEFT] )
	{
		return key_left;
	}
	if ( keysHeld[SDLK_RIGHT] )
	{
		return key_right;
	}


	return key_none;
}






/*! Function that draws all elements on the screen
\param gameBattlefield a Battlefield type
\param gamePlayerShip a PlayerShip type
\param AlienShipVector a vector of type AlienShip
\param PlayerMissilesVector a vector of type PlayerMissile
\param AlienMissilesVector a vector of type AlienMissile
*/
void Graphics::DrawScreen(Battlefield& gameBattlefield, PlayerShip& gamePlayerShip, 
						  vector<AlienShip>& AlienShipVector, vector<PlayerMissile>& PlayerMissilesVector,
						  vector<AlienMissile>& AlienMissilesVector) 
{																					
	ClearScreen();

	for ( int i=0 ; i<50 ; i++ )
	{
		DrawRandomStars();
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
	ClearScreen();	

	for ( int i=0 ; i<50 ; i++ )
	{
		DrawRandomStars();
	}


	boxRGBA(screen, WINDOW_WIDTH/2-200, WINDOW_HEIGHT/2-130,  WINDOW_WIDTH/2+200, WINDOW_HEIGHT/2+130, 
			0, 0, 255, 255);
	boxRGBA(screen, WINDOW_WIDTH/2-190, WINDOW_HEIGHT/2-120,  WINDOW_WIDTH/2+190, WINDOW_HEIGHT/2+120, 
			255, 255, 255, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-85, WINDOW_HEIGHT/2-90, "Alien Annihilation",
			      255, 0, 0, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-25, WINDOW_HEIGHT/2-70, "v1.0",
			      0, 0, 0, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-70, WINDOW_HEIGHT/2-60, "Copyright 2007",
			      0, 0, 0, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-70, WINDOW_HEIGHT/2-40, "Miroslav Minev",
			      0, 0, 0, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-70, WINDOW_HEIGHT/2-30, "Andrew Russell",
			      0, 0, 0, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2-10, "1 = play Level 1: rookie",
			      40, 150, 40, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2+0, "2 = play Level 2: experienced",
			      40, 150, 40, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2+10, "3 = play Level 3: vetran",
			      40, 150, 40, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2+20, "l = load saved game",
			      40, 150, 40, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2+30, "q = quit",
			      40, 150, 40, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2+50, "In-Game keys:",
			      255, 0, 0, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2+70, "Left and Right arrow keys to move",
			      255, 0, 0, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2+80, "Space to shoot",
			      255, 0, 0, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2+90, "Escape to go to Pause menu",
			      255, 0, 0, 255);

	RevealScreen();

}




/*!Function to draw the start menu of the game

*/
void Graphics::DrawPauseMenu()
{
    boxRGBA(screen, WINDOW_WIDTH/2-120, WINDOW_HEIGHT/2-60,  WINDOW_WIDTH/2+120, WINDOW_HEIGHT/2+60, 
			100, 100, 100, 200);

 	stringRGBA(screen, WINDOW_WIDTH/2-25, WINDOW_HEIGHT/2-40, "Paused",
			      255, 255, 255, 255);
 
	stringRGBA(screen, WINDOW_WIDTH/2-80, WINDOW_HEIGHT/2-20, "ESC = resume",
			      255, 255, 255, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-80, WINDOW_HEIGHT/2-10, "r = return to main menu",
			      255, 255, 255, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-80, WINDOW_HEIGHT/2+0, "s = save",
			      255, 255, 255, 255);
	stringRGBA(screen, WINDOW_WIDTH/2-80, WINDOW_HEIGHT/2+10, "q = quit",
			      255, 255, 255, 255);

	RevealScreen();

}




/*!Function to clear the entire screen

*/
void Graphics::ClearScreen()
{
	SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format,0,0,0));
}







/*!Function to draw the entrie Battlefield
\param gameBattlefield a variable of type Battlefield
*/
void Graphics::DrawBattlefield (Battlefield& gameBattlefield)
{
	DrawCircles (gameBattlefield);
	DrawLines (gameBattlefield);
}





/*!Function to draw the circles of the Battlefield
\param gameBattlefield a variable of type Battlefield
*/
void Graphics::DrawCircles (Battlefield& gameBattlefield)
{
	vector<Circle> vecCircles = gameBattlefield.get_vectorBattlefieldCircles();
	vector<Circle>::iterator circlesVecIter;
	circlesVecIter = vecCircles.begin();

	while (circlesVecIter != vecCircles.end())
	{
		// Draw circle (stored in battlefieldCirclesVector) pointed to by circlesVecIter
		DrawSingleCircle(circlesVecIter->centre_x,	circlesVecIter->centre_y, 
						circlesVecIter->radius_x,	circlesVecIter->radius_y,
						circlesVecIter->colour_red,	circlesVecIter->colour_green,
						circlesVecIter->colour_blue,circlesVecIter->colour_transparency);

		circlesVecIter++;
	}
}




/*!Function to draw the lines of the Battlefield
\param gameBattlefield a variable of type Battlefield
*/
void Graphics::DrawLines (Battlefield& gameBattlefield)
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
void Graphics::DrawPlayerShip (PlayerShip& gamePlayerShip)
{
	DrawFilledEllipse ( gamePlayerShip.get_coordinate_x(),	gamePlayerShip.get_coordinate_y(),
					 gamePlayerShip.get_sizeRadius_x(),		gamePlayerShip.get_sizeRadius_y(),
					 gamePlayerShip.get_colourRed(),		gamePlayerShip.get_colourGreen(), 
					 gamePlayerShip.get_colourBlue(),		gamePlayerShip.get_colourTransparency() );

}


/*!Function to draw the Player ships score
\param gamePlayerShip a variable of type PlayerShip
*/
void Graphics::DrawPlayerScore (PlayerShip& gamePlayerShip)
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

	char score[10];
	strcpy_s(score, out.str().c_str());

	stringRGBA(screen, 30, 30, "score: ", 
			      255, 255, 255, 255);
	stringRGBA(screen, 90, 30, score, 
			      255, 255, 255, 255);
}




/*!A function to iterate through the vector of the alien ships and drsw each alien to the screen
\param AlienShipVector a vector containing instances of type AlienShip
*/
void Graphics::DrawAlienShips (vector<AlienShip>& AlienShipVector)
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
void Graphics::DrawSingleCircle(int centre_x, int centre_y, int radius_x, int radius_y,
						  int red, int green, int blue, int transparency)						   
{
	ellipseRGBA(screen,
				centre_x, centre_y,
			    radius_x, radius_y,
				red, green, blue, transparency);
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
void Graphics::DrawSingleLine(int x1, int y1, int x2, int y2,
						int red, int green, int blue, int transparency)					 
{
	lineRGBA(screen, 
	 		 x1, y1,
             x2, y2,
             red, green, blue, transparency);
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
void Graphics::DrawFilledEllipse(int centre_x, int centre_y, int radius_x, int radius_y,
						int red, int green, int blue, int transparency)
{

	filledEllipseRGBA(screen,
	                  centre_x, centre_y,
					  radius_x, radius_y,
					  red, green, blue, transparency);	

}




/*!Function to reveal the screen

*/
void Graphics::RevealScreen()
{
	SDL_Flip(screen);
}





/*!A function to iterate through the vector of the player missiles and drsw each missile to the screen
\param PlayerMissilesVector a vector containing instances of type PlayerMissile
*/
void Graphics::DrawPlayerMissiles (vector<PlayerMissile>& PlayerMissilesVector)
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
void Graphics::DrawAlienMissiles (vector<AlienMissile>& AlienMissilesVector)
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
	boxRGBA(screen, WINDOW_WIDTH/2-190, WINDOW_HEIGHT/2-60,  WINDOW_WIDTH/2+190, WINDOW_HEIGHT/2+60, 
			0, 255, 0, 150);

	stringRGBA(screen, WINDOW_WIDTH/2-180, WINDOW_HEIGHT/2-20, "You Win! - all alien ships heve been destroyed",
			      255, 255, 255, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-90, WINDOW_HEIGHT/2+20, "Press enter to continue",
			      255, 255, 255, 255);

}

/*!A function to draw the game over condition which correspond to the case where the aliens have reached the player base*/
void Graphics::DrawEnd_AliensOnOuterCircle()
{
	boxRGBA(screen, WINDOW_WIDTH/2-190, WINDOW_HEIGHT/2-60,  WINDOW_WIDTH/2+190, WINDOW_HEIGHT/2+60, 
			255, 0, 0, 150);

	stringRGBA(screen, WINDOW_WIDTH/2-180, WINDOW_HEIGHT/2-20, "GAME OVER - the aliens have invaded your base",
			      255, 255, 255, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-90, WINDOW_HEIGHT/2+20, "Press enter to continue",
			      255, 255, 255, 255);

}


/*!A function to draw the game over condition which correspond to the case where the player ship is destroyed*/
void Graphics::DrawEnd_PlayerDestroyed()
{
	boxRGBA(screen, WINDOW_WIDTH/2-190, WINDOW_HEIGHT/2-60,  WINDOW_WIDTH/2+190, WINDOW_HEIGHT/2+60, 
			255, 0, 0, 150);

	stringRGBA(screen, WINDOW_WIDTH/2-140, WINDOW_HEIGHT/2-20, "GAME OVER - you have been destroyed",
			255, 255, 255, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-90, WINDOW_HEIGHT/2+20, "Press enter to continue",
		    255, 255, 255, 255);
}


/*!A function to draw the condition which correspond to the case where a game has not been succesfully loaded*/
void Graphics::DrawLoadError()
{
	boxRGBA(screen, WINDOW_WIDTH/2-190, WINDOW_HEIGHT/2-60,  WINDOW_WIDTH/2+190, WINDOW_HEIGHT/2+60, 
			255, 0, 0, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-70, WINDOW_HEIGHT/2-20, "No saved games",
			255, 255, 255, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-90, WINDOW_HEIGHT/2+20, "Press enter to continue",
		    255, 255, 255, 255);

	RevealScreen();


}

/*!A function to draw the condition which correspond to the case where a game has been succesfully loaded*/
void Graphics::DrawLoadCorrect()
{
	boxRGBA(screen, WINDOW_WIDTH/2-190, WINDOW_HEIGHT/2-60,  WINDOW_WIDTH/2+190, WINDOW_HEIGHT/2+60, 
			0, 255, 0, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-70, WINDOW_HEIGHT/2-20, "Saved game loaded",
			255, 255, 255, 255);

	stringRGBA(screen, WINDOW_WIDTH/2-90, WINDOW_HEIGHT/2+20, "Press enter to play",
		    255, 255, 255, 255);

	RevealScreen();


}



//!A function to draw random stars on the screen
void Graphics::DrawRandomStars()
{
	int x = rand()%WINDOW_WIDTH;
	int y = rand()%WINDOW_HEIGHT;
	pixelRGBA(screen, x, y, 255, 255, 255, 180);

}