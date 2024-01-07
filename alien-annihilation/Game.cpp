/*
-------------------------------------------------------------------------

	Game.cpp

-------------------------------------------------------------------------
*/

#include <fstream>
#include <iostream>
#include "Game.h"
#include "Input.h"
#include "Graphics.h"
#include "AlienMissile.h"
#include "Settings.h"

using namespace std;

/*!	Default constructor initializes game with fixed parameters
	*/
Game::Game()
{
	_windowWidth = 800;
	_windowHeight = 600;
	_numberOfLines = 8;
	_numberOfCircles = 3;
	_numberOfAliens = 5;
	_maxMissiles = 10;			// max number of missiles allowed on screen or to be fired by PlayerShip

	_playerSize_x = 7;
	_playerSize_y = 7;
	_alienSize_x = 9;
	_alienSize_y = 2;

}

/*!	Constructor which accepts width and height of the game window to create an object of the game
\param windowWidth : width of game window
\param windowHeight : height of game window
*/
Game::Game(int windowWidth, int windowHeight):_gameGraphics (windowWidth, windowHeight)
{
	_windowWidth = windowWidth;
	_windowHeight = windowHeight;
	_numberOfAliens = 5;
	_maxMissiles = 10;			// max number of missiles allowed on screen or to be fired by PlayerShip

	_playerSize_x = 5;
	_playerSize_y = 5;
	_alienSize_x = 9;
	_alienSize_y = 2;
}

/*!	Function that controls the input logic from the Input class and runs the main game loop
*/
bool Game::RunGame()
{
	printf("Game::RunGame\n");

	bool gameRunning1 = false;
	int randomShootTime;
	string settingsFile = "settings1.txt";
	Action gameAction;
	Action gameStart;
	Input playerInput;

	_loadSuccessful = true;
	gameStart = StartMenu(playerInput);

//	_gameGraphics.BlockScreen();

	switch (gameStart)
	{
		case load:
			_loadSuccessful = Game::CreateSavedAlienShipsVector();

			// Await player to press enter
			gameAction = noAction;
			while (gameAction == noAction)
			{
				gameAction = playerInput.LoadScreen(_gameGraphics);
			}
			gameRunning1 = true;
			break;

		case quit:
			printf("Game::RunGame -> gameStart=quit\n");
			return false;
			break;

		case settings_1:
			Game::CreateAlienShipsVector();
			gameRunning1 = true;
			break;

		case settings_2:
			settingsFile = "settings2.txt";
			Game::CreateAlienShipsVector();
			gameRunning1 = true;
			break;

		case settings_3:
			settingsFile = "settings3.txt";
			Game::CreateAlienShipsVector();
			gameRunning1 = true;
			break;
	}

	Settings gameSettings(settingsFile);
	_numberOfCircles = gameSettings.get_numberOfCircles();
	_numberOfLines = gameSettings.get_numberOfLines();

	if (!_loadSuccessful)
		return true;

	CreateBattlefield();
	CreatePlayerShip();

	while (gameRunning1)
	{
		gameAction = playerInput.InGame(_gameGraphics);
		if (gameAction != noAction)
			gameRunning1 = DoAction(gameAction);

		if (gameAction == pause)
		{
			gameAction = PauseMenu(playerInput);
		
			switch (gameAction)
			{
				case resume:
					break;
	
				case restart:
					return true;
					break;

				case save:
					SaveGame();
					return true;
					break;

				case quit:
					return false;
					break;
			}
		}

		randomShootTime = rand()%100;
		if (randomShootTime < 20 )
		{
			if ( 0 < _vectorAlienShips.size() )
				AlienShoot();
		}

		UpdateAll ();
		CollisionDetect ();
		DisplayGame ();

		if ( CheckGameOver ())
		{
			gameAction = noAction;
			while (gameAction == noAction)
			{
				gameAction = playerInput.EndScreen(_gameGraphics);
			}
			return true;
		}
	}

	return false;
}

/*! Awaits for a possible input that is acceptable for the start menu.
\param playerInput : object that contains function to check the input on the keyboard and return action to be performed
\return : An action that can be performed in the start menu.
*/
Action Game::StartMenu(Input& playerInput)
{
	printf("Game::StartMenu\n");

	Action paused = noAction;
	while (paused == noAction)
	{
		_gameGraphics.DrawStartMenu();
		paused = playerInput.StartMenu(_gameGraphics);
	}
	return paused;
}

/*! Calls playership functions that move the playership or make it shoot.
\param gameAction: Player action to be performed
*/
bool Game::DoAction(Action& gameAction)
{
	switch (gameAction)
	{
		case movePlayerLeft:
			_gamePlayerShip.MoveClockwise(_gameBattlefield);
			break;
		case movePlayerRight:
			_gamePlayerShip.MoveCounterClockwise(_gameBattlefield);
			break;
		case playerShoot:
			PlayerShoot();
			break;
		default:
			break;
	}

	return 1;
}

/*! Awaits for a possible input that is acceptable for the pause menu during gameplay. 
\param playerInput : object that contains function to check the input on the keyboard and return action to be performed
\return : An action that can be performed in the pause menu.
*/
Action Game::PauseMenu(Input& playerInput)
{
	_gameGraphics.DrawPauseMenu();
	Action paused = noAction;
	while (paused == noAction)
	{
		paused = playerInput.PauseMenu(_gameGraphics);
	}
	return paused;

}



/*! This function calls the individual Update functions to check states and update all moving objects on the screen
*/
void Game::UpdateAll()
{
	UpdateAliens();
	UpdatePlayerMissiles();
	UpdateAlienMissiles();
}




/*!	Function that iterates through the vectors of all the interacting objects in the game in a nested fashion and checks if any collisions have occured. If a collision is detected the health of the involved AlienShip or PlayerShip is reduced by a constant factor and the involved Missile is destroyed (i.e. state set to 0). If an AlienShip or PlayerShip's health is 0 then it is destroyed (i.e. state set to 0). This function does not update or erase elements from the vectors.
	*/
void Game::CollisionDetect()
{
	CollisionDetect_PlayerMissiles_AlienShip();
	CollisionDetect_PlayerShip_AlienMissiles();
	CollisionDetect_PlayerMissiles_AlienMissiles();
}



/*!	Function that iterates through the vectors of PlayerMissiles and AlienShips and checks if any collisions have occured. If a collision is detected the health of the involved AlienShip is reduced by a constant factor and the involved Missile is destroyed (i.e. state set to 0). If an AlienShip's health is 0 then it is destroyed (i.e. state set to 0). This function does not update or erase elements from the vectors.
	*/
void Game::CollisionDetect_PlayerMissiles_AlienShip()
{

	vector<AlienShip>::iterator iter_vectorAlienShips;
	iter_vectorAlienShips = _vectorAlienShips.begin();

	while (iter_vectorAlienShips != _vectorAlienShips.end())
	{
		vector<PlayerMissile>::iterator iter_vectorPlayerMissiles;
		iter_vectorPlayerMissiles = _vectorPlayerMissiles.begin();

		while (iter_vectorPlayerMissiles != _vectorPlayerMissiles.end())
		{

			// check if missile centre x coordinate lies within x coordinate of alienship
			if ( (iter_vectorPlayerMissiles->get_coordinate_x() > (iter_vectorAlienShips->get_coordinate_x() - iter_vectorAlienShips->get_sizeRadius_x()))
				&& (iter_vectorPlayerMissiles->get_coordinate_x() < (iter_vectorAlienShips->get_coordinate_x() + iter_vectorAlienShips->get_sizeRadius_x())) )
			{
			
				// check if missile centre y coordinate lies within y coordinate of alienship
				if ( (iter_vectorPlayerMissiles->get_coordinate_y() > (iter_vectorAlienShips->get_coordinate_y() - iter_vectorAlienShips->get_sizeRadius_y()))
					&& (iter_vectorPlayerMissiles->get_coordinate_y() < (iter_vectorAlienShips->get_coordinate_y() + iter_vectorAlienShips->get_sizeRadius_y())) )
				{


					if (iter_vectorAlienShips-> get_health() > 0)
					{
						iter_vectorAlienShips-> ReduceHealth(33);
						_gamePlayerShip.AddScore(20);
					}

					if (iter_vectorAlienShips -> get_health() == 0)
					{
						iter_vectorAlienShips -> DestroyShip();
						_gamePlayerShip.AddScore(50);

					}

					iter_vectorPlayerMissiles -> DestroyMissile();

				} // END - if
			} // END - if

			iter_vectorPlayerMissiles++;
		} // END - while

		iter_vectorAlienShips++;
	} // END - while

}



/*!	Function that iterates through the vectors of AlienMissiles and checks if any collisions have occured with the PlayerShip. If a collision is detected the health of the PlayerShip is reduced by a constant factor and the involved Missile is destroyed (i.e. state set to 0). If an PlayerShip's health is 0 then it is destroyed (i.e. state set to 0). This function does not update or erase elements from the vectors.
	*/
void Game::CollisionDetect_PlayerShip_AlienMissiles()
{
	vector<AlienMissile>::iterator iter_vectorAlienMissiles;
	iter_vectorAlienMissiles = _vectorAlienMissiles.begin();

	while (iter_vectorAlienMissiles != _vectorAlienMissiles.end())
	{
		if ( (iter_vectorAlienMissiles->get_coordinate_x() > (_gamePlayerShip.get_coordinate_x() - _gamePlayerShip.get_sizeRadius_x()))
				&& (iter_vectorAlienMissiles->get_coordinate_x() < (_gamePlayerShip.get_coordinate_x() + _gamePlayerShip.get_sizeRadius_x())) )
			{
			
				if ( (iter_vectorAlienMissiles->get_coordinate_y() > (_gamePlayerShip.get_coordinate_y() - _gamePlayerShip.get_sizeRadius_y()))
					&& (iter_vectorAlienMissiles->get_coordinate_y() < (_gamePlayerShip.get_coordinate_y() + _gamePlayerShip.get_sizeRadius_y())) )
				{


					if (_gamePlayerShip.get_health() > 0)
					{
						_gamePlayerShip.ReduceHealth(33);
						_gamePlayerShip.AddScore(-100);
					}

					if (_gamePlayerShip.get_health() == 0)
					{
						_gamePlayerShip.DestroyShip();
					}

					iter_vectorAlienMissiles -> DestroyMissile();

				} 
			} 

		iter_vectorAlienMissiles++;
	} 

}

/*!	Function that iterates through the vectors of PlayerMissiles and AlienMissiles and checks if any collisions have occured. If a collision is detected the involved Missiles are destroyed (i.e. state set to 0). This function does not update or erase elements from the vectors.
	*/
void Game::CollisionDetect_PlayerMissiles_AlienMissiles()
{
	vector<AlienMissile>::iterator iter_vectorAlienMissiles;
	iter_vectorAlienMissiles = _vectorAlienMissiles.begin();

	while (iter_vectorAlienMissiles != _vectorAlienMissiles.end())
	{
		vector<PlayerMissile>::iterator iter_vectorPlayerMissiles;
		iter_vectorPlayerMissiles = _vectorPlayerMissiles.begin();

		while (iter_vectorPlayerMissiles != _vectorPlayerMissiles.end())
		{

			// check if PlayerMissile centre x coordinate lies within x coordinate of alienMissile
			if ( (iter_vectorPlayerMissiles->get_coordinate_x() > (iter_vectorAlienMissiles->get_coordinate_x() - iter_vectorAlienMissiles->get_sizeRadius_x()))
				&& (iter_vectorPlayerMissiles->get_coordinate_x() < (iter_vectorAlienMissiles->get_coordinate_x() + iter_vectorAlienMissiles->get_sizeRadius_x())) )
			{
			
				// check if PlayerMissile centre y coordinate lies within y coordinate of alienMissile
				if ( (iter_vectorPlayerMissiles->get_coordinate_y() > (iter_vectorAlienMissiles->get_coordinate_y() - iter_vectorAlienMissiles->get_sizeRadius_y()))
					&& (iter_vectorPlayerMissiles->get_coordinate_y() < (iter_vectorAlienMissiles->get_coordinate_y() + iter_vectorAlienMissiles->get_sizeRadius_y())) )
				{

					iter_vectorAlienMissiles -> DestroyMissile();
					iter_vectorPlayerMissiles -> DestroyMissile();

				} // END - if
			} // END - if

			iter_vectorPlayerMissiles++;
		} // END - while

		iter_vectorAlienMissiles++;
	} // END - while

}





/*! Function that checks the three game over conditions:
	1. If all the aliens are destroyed (player wins)
	2. If one of the aliens is on the outer circle where the playership is (player loses)
	3. If the playership is destroyed (player loses)
\return boolean : 1 if any of the game over conditions are met, 0 if not
*/
bool Game::CheckGameOver()
{

	if (_vectorAlienShips.empty())
	{
		_gameGraphics.DrawGameOver(_gameBattlefield, AllAliensDestroyed);
		return 1;
	}

	vector<AlienShip>::iterator iter_vectorAlienShips;
	iter_vectorAlienShips = _vectorAlienShips.begin();

	while ( iter_vectorAlienShips != _vectorAlienShips.end() )
	{
		if ( iter_vectorAlienShips->get_circleIterator() == _gameBattlefield.get_numberOfCircles() )
		{
			_gameGraphics.DrawGameOver(_gameBattlefield, AliensOnOuterCircle); 
			return 1;
		}
		iter_vectorAlienShips++;
		
	}

	if ( _gamePlayerShip.get_health() == 0)
	{
		_gameGraphics.DrawGameOver(_gameBattlefield, PlayerDestroyed); 
		return 1;

	}

	return 0;

}


/*! Function that passes all the objects to a function of the Graphics class to be drawn on the Graphics screen
	*/
void Game::DisplayGame()
{
	_gameGraphics.DrawScreen( _gameBattlefield, _gamePlayerShip, _vectorAlienShips, _vectorPlayerMissiles, _vectorAlienMissiles);
}


/*! Function that saves AlienShip polar coordinates and health to a text file
	*/
void Game::SaveGame()
{
	ofstream savedGame;
	savedGame.open ("savedGame.txt");
	vector<AlienShip>::iterator iter_vectorAlienShips;
	iter_vectorAlienShips = _vectorAlienShips.begin();

	while ( iter_vectorAlienShips != _vectorAlienShips.end() )
	{
		savedGame << iter_vectorAlienShips ->get_angleFromCentre() << endl;
		savedGame << iter_vectorAlienShips ->get_circleIterator() << endl;
		
		savedGame << iter_vectorAlienShips ->get_health()<<endl;
		
		iter_vectorAlienShips++;
	}

	savedGame.close();
}



/*
-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------
	PRIVATE MEMBER FUNCTIONS
-------------------------------------------------------------------------------------------------------------------
-------------------------------------------------------------------------------------------------------------------
*/



/*! Function that resests all the variables in the Battlefield object. A default Battlefield is created when the private data members are declared when an object of Game is declared. This function is to be called after the number of lines and number of circles are read in from the level text file. It creates new vectors of circles and lines.
	*/
void Game::CreateBattlefield()
{
	_gameBattlefield.set_battlefieldWidth( _windowWidth);
	_gameBattlefield.set_battlefieldHeight( _windowHeight);
	_gameBattlefield.set_battlefieldCentre_x();
	_gameBattlefield.set_battlefieldCentre_y();
	_gameBattlefield.set_outerCircleRadius_x(300);
	_gameBattlefield.set_outerCircleRadius_y(300);
	_gameBattlefield.set_numberOfCircles(_numberOfCircles);
	_gameBattlefield.set_numberOfLines(_numberOfLines);
	_gameBattlefield.set_circleColour_red(0);
	_gameBattlefield.set_circleColour_green(50);
	_gameBattlefield.set_circleColour_blue(0);
	_gameBattlefield.set_circleColour_transparency(200);
	_gameBattlefield.set_lineColour_red(0);
	_gameBattlefield.set_lineColour_green(50);
	_gameBattlefield.set_lineColour_blue(0);
	_gameBattlefield.set_lineColour_transparency(200);
	_gameBattlefield.set_angleBetweenLines();

	_gameBattlefield.CreateBattlefieldCirclesVector();
	_gameBattlefield.CreateBattlefieldLinesVector();

}



/*! Function that creates the gamePlayerShip
	*/
void Game::CreatePlayerShip()
{
	float startingAngle = 3.14159/2;	// bottom of battlefield

	PlayerShip tempPlayerShip ("Player1", _gameBattlefield.get_outerCircleRadius_y(), startingAngle, 
							_gameBattlefield.get_battlefieldCentre_x(), _gameBattlefield.get_battlefieldCentre_y(), 
							_playerSize_x, _playerSize_y );
	_gamePlayerShip = tempPlayerShip;
}



/*! Function that creates a vector of alien ships for when a new level is created
	*/
void Game::CreateAlienShipsVector()
{
	_vectorAlienShips.clear();

	float startingAngle = 3.14159/2;
	for (int circleiterator = 1 ; circleiterator <= 5 ; circleiterator++ )
	{
		for (int i=1 ; i<=10 ; i++ )		//number of aliens per circle
		{

			AlienShip tempAlienShip ("Alien", circleiterator, startingAngle, 
									_gameBattlefield.get_battlefieldCentre_x(), _gameBattlefield.get_battlefieldCentre_y(),
									_alienSize_x, _alienSize_y,
									0, 50+5*i, 10+20*i );

			_vectorAlienShips.push_back(tempAlienShip);

			startingAngle = startingAngle + 3.14159/8;
		}
		
		startingAngle = 3.14159/2;
	}
}


/*! Function that creates a PlayerMissile when the player shoots
	*/
void Game::PlayerShoot()
{
	PlayerMissile tempPlayerMissile(_gamePlayerShip);
	_vectorPlayerMissiles.push_back(tempPlayerMissile);
}




/*! Function that creates an AlienMissile when an AlienShip shoots and adds it to the vector of AlienMissiles
	*/
void Game::AlienShoot()
{
	int randomAlienShoot = rand()%_vectorAlienShips.size();

	AlienShip* ptr_vectorAlienShips;

	ptr_vectorAlienShips  = &_vectorAlienShips[randomAlienShoot];

	AlienMissile tempAlienMissile(ptr_vectorAlienShips->get_radiusFromCentre(), ptr_vectorAlienShips->get_angleFromCentre(), 
						ptr_vectorAlienShips->get_coordinate_x(), ptr_vectorAlienShips->get_coordinate_y());
	_vectorAlienMissiles.push_back(tempAlienMissile);

}






/*! Iterates through the vector of AlienShips and calls their functions to move them if their state is 'alive' (1), else if its state is 'dead' erase it from the vector
	*/
void Game::UpdateAliens()
{
	vector<AlienShip>::iterator iter_vectorAlienShips;
	iter_vectorAlienShips = _vectorAlienShips.begin();

	while (iter_vectorAlienShips != _vectorAlienShips.end() )
	{
		if (iter_vectorAlienShips->get_state())
		{
			iter_vectorAlienShips -> MoveCounterClockwise(_gameBattlefield);
			iter_vectorAlienShips++;
		}
		else
		{
			iter_vectorAlienShips = _vectorAlienShips.erase(iter_vectorAlienShips);
			
		}
	}

}

/*!	Function to iterate through vector of PlayerMissiles and call each PlayerMissile "Move" function if its state is 1 (alive) else erase it from the vector
	*/
void Game::UpdatePlayerMissiles()
{
	vector<PlayerMissile>::iterator iter_vectorPlayerMissiles;
	iter_vectorPlayerMissiles = _vectorPlayerMissiles.begin();

	while (iter_vectorPlayerMissiles != _vectorPlayerMissiles.end())
	{
		if (iter_vectorPlayerMissiles -> get_state())
		{
			iter_vectorPlayerMissiles ->MoveContinuous(_gameBattlefield);
			iter_vectorPlayerMissiles++;
		}
		else
		{
			iter_vectorPlayerMissiles = _vectorPlayerMissiles.erase(iter_vectorPlayerMissiles);
			_gamePlayerShip.AddScore(-1);
		}
	}
}

/*!	Function to iterate through vector of AlienMissiles and call each AlienMissile "Move" function if its state is 1 (alive) else erase it from the vector
	*/
void Game::UpdateAlienMissiles()
{
	vector<AlienMissile>::iterator iter_vectorAlienMissiles;
	iter_vectorAlienMissiles = _vectorAlienMissiles.begin();

	while (iter_vectorAlienMissiles != _vectorAlienMissiles.end())
	{
		if (iter_vectorAlienMissiles -> get_state())
		{
			iter_vectorAlienMissiles ->MoveContinuous(_gameBattlefield);
			iter_vectorAlienMissiles++;
		}
		else
		{
			iter_vectorAlienMissiles = _vectorAlienMissiles.erase(iter_vectorAlienMissiles);
		}
	}
}

/*! Function that creates a vector of alien ships from the saved coordinates and healths, for when a level is loaded from the text file
	*/
bool Game::CreateSavedAlienShipsVector()
{
	printf("Game::CreateSavedAlienShipsVector\n");

	_vectorAlienShips.clear();

	float savedAngle;
	int savedCircleIterator;
	int savedHealth;
	
	ifstream loadGame("savedGame.txt");
	if (loadGame.is_open())
	{
		while (!loadGame.eof())
		{
			loadGame >> savedAngle;
			loadGame >> savedCircleIterator;
			loadGame>>savedHealth;

			AlienShip tempAlienShip ("Alien", savedCircleIterator, savedAngle, 
							_gameBattlefield.get_battlefieldCentre_x(), _gameBattlefield.get_battlefieldCentre_y(),
							_alienSize_x, _alienSize_y,
							0, 50+5, 10+20, savedHealth );

			_vectorAlienShips.push_back(tempAlienShip);	
		}
		loadGame.close();
		_gameGraphics.DrawLoadCorrect();
		return 1;
	}
	else 
	{
		_gameGraphics.DrawLoadError();
		return 0;
	}
}
