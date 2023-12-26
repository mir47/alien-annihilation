/*
-------------------------------------------------------------------------

	PlayerShip.h

-------------------------------------------------------------------------
*/

#ifndef PLAYERSHIP_H
#define PLAYERSHIP_H

#include <iostream>
#include <string>
#include "Ship.h"
#include "Battlefield.h"

using namespace std;

//! Class implementation for a single PlayerShip. Derived class of Ship using public inheritance.
class PlayerShip : public Ship
{
public:
	
	//!Default constructor 
	PlayerShip();

	//!Constructor with parameters
	PlayerShip(string name, int radiusFromCentre, float startingAngle, int battlefieldCentre_x, int battlefieldCentre_y, 
			   int size_x, int size_y);



//	void moveShip();		//from virtual void of Ship class


	//!Function to move the player ship in a clockwise direction 
	void MoveClockwise(Battlefield& gameBattlefield);

	//!Function to move the player ship in a counter clockwise direction
	void MoveCounterClockwise(Battlefield& gameBattlefield);

	//!Function to add to the players current score
	void AddScore(int howMuch);
	//!Returns the current score of the player ship
	int get_score();



private:
	int _numberOfLives;//!<Stores the number of lives the player ship currently has
	int _score; //!<Stores the the score of the player ship
};

#endif