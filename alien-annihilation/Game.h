/*
-------------------------------------------------------------------------
	
	Game.h

-------------------------------------------------------------------------
*/
 
#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <fstream>
#include "Graphics.h"
#include "Battlefield.h"
#include "PlayerShip.h"
#include "PlayerMissile.h"
#include "AlienShip.h"
#include "AlienMissile.h"
#include "Input.h"

using namespace std;

//! Class implementation that contains the logic functions of the Game
/*! Game is a class that contains all the logic in the game including inputs, outputs and actions
*/
class Game
{
public:
	//! The default constructor
	Game();
	//! Constructor with parameters
	Game(int windowWidth, int windowHeight);

	


//	Game( pass level file to this constructor );

	bool RunGame();

	//! Reads in different levels from text file
	void ReadLevelFile();
	//! Performs player action
	bool DoAction(Action& gameAction);
	//! Reads in input for the start menu
	Action StartMenu(Input& playerInput);
	//! Reads in input for the pause menu
	Action PauseMenu(Input& playerInput);

	//! Calls individual Update functions of all moving objects
	void UpdateAll();

	//! Compares coordinates of all objects in the game
	void CollisionDetect();
	//! Checks for collision between PlayerMissiles and AlienShip
	void CollisionDetect_PlayerMissiles_AlienShip();
	//! Checks for collision between PlayerShip and AlienMissiles
	void CollisionDetect_PlayerShip_AlienMissiles();
	//! Checks for collision between PlayerMissiles and AlienMissiles
	void CollisionDetect_PlayerMissiles_AlienMissiles();
	//! Checks the three game over conditions
	bool CheckGameOver();
	//! Outputs all objects to Graphics class to be drawn
	void DisplayGame();

	
	//! Funtion to save a current game before quiting 
	void SaveGame();


private:
		// functions
	//! Creates background of lines and circles
	void CreateBattlefield();
	//! Creates a PlayerShip that inherets from Ship
	void CreatePlayerShip();
	//! Creates a vector of AlienShips
	void CreateAlienShipsVector();
	//! Reads in Alien coordinates from text file and creates a vector of AlienShips
	bool CreateSavedAlienShipsVector();

	//! Creates a PlayerMissile
	void PlayerShoot();
	//! Creates an AlienMissile
	void AlienShoot();


	//! Iterates through vector of AlienShips and updates coordinates and states
	void UpdateAliens();
	//! Iterates through vector of PlayerMissiles and updates coordinates and states
	void UpdatePlayerMissiles();
	//! Iterates through vector of AlienMissiles and updates coordinates and states
	void UpdateAlienMissiles();
	

	// classes
	Battlefield _gameBattlefield;//!< Object that stores lines and circles for Battlefield
	Graphics _gameGraphics;//!< Object 
	PlayerShip _gamePlayerShip;//!< Playership object 
	

	// vectors
	vector<PlayerMissile> _vectorPlayerMissiles;//!< Vector that stores all the player missiles in play
	vector<AlienMissile> _vectorAlienMissiles;//!< Vector that stores all the alien missiles in play
	vector<AlienShip> _vectorAlienShips;//!< Vector that stores all the player ships in play

	// data members		- from level file.txt
	int _windowWidth;//!< stores integer width of the game window
	int _windowHeight;//!< stores integer height of the game window
	int _numberOfLines;//!< stores number of lines for battlefield that is read in from text file			
	int _numberOfCircles;//!< stores number of circles for battlefield that is read in from text file		
	int _numberOfAliens;//!< stores number of aliens (to start or currently on screen) for future implementation
	int _maxMissiles;//!< stores max number of missiles allowed (on screen or to be fired by PlayerShip) for future implementation			
	int _playerSize_x;//!< stores x radius of ellipse size of PlayerShip
	int _playerSize_y;//!< stores y radius of ellipse size of PlayerShip
	int _alienSize_x;//!< stores x radius of ellipse size of AlienShip
	int _alienSize_y;//!< stores y radius of ellipse size of AlienShip

	bool _loadSuccessful;//!< flag for successful saved game loading

};



#endif