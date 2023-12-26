/*
-------------------------------------------------------------------------

	PlayerShip.cpp

-------------------------------------------------------------------------
*/

#include <iostream>
#include <string>
#include "PlayerShip.h"
#include "Ship.h"

using namespace std;


//!Default constructor
PlayerShip::PlayerShip()
{
}



/*!Constructor which accepts seven parameters to create a more specific player ship
\param name a string to set the name of the ship
\param radiusFromCentre an integer value to set the starting radius of the ship position from the centre point of the battlefield
\param startingAngle a float value to set starting angle of the ship position with respect to the zero degree angle of the battlefield
\param battlefieldCentre_x an integer value to set the value of the centre x coordinate about which the ship will revolve
\param battlefieldCentre_y an integer value to set the value of the centre y coordinate about which the ship will revolve
\param size_x an integer to set the x radius of the size of the ship
\param size_y an integer to set the y radius of the size of the ship
*/
PlayerShip::PlayerShip(string name, int radiusFromCentre, float startingAngle, int battlefieldCentre_x, int battlefieldCentre_y, 
			   int size_x, int size_y)
	:Ship( name, radiusFromCentre, startingAngle, battlefieldCentre_x, battlefieldCentre_y, size_x, size_y)
{
	_score = 0;
}






//!Function to move the playership in a clockwise direction along the outer-most circle
void PlayerShip::MoveClockwise(Battlefield& gameBattlefield)
{
	_currentCoordinates.angleFromCentre = _currentCoordinates.angleFromCentre + _pi/40;
//	_currentCoordinates.angleFromCentre = _currentCoordinates.angleFromCentre + gameBattlefield.get_angleBetweenLines();


	if (_currentCoordinates.angleFromCentre >= _pi*2)
		_currentCoordinates.angleFromCentre = 0;							// mention buffer overflow


	_currentCoordinates.x = _battlefieldCentre_x + _currentCoordinates.radiusFromCentre * cos(_currentCoordinates.angleFromCentre);
	_currentCoordinates.y = _battlefieldCentre_y + _currentCoordinates.radiusFromCentre * sin(_currentCoordinates.angleFromCentre);

}




//!Function to move the playership in a counter clockwise direction along the outer-most circle
void PlayerShip::MoveCounterClockwise(Battlefield& gameBattlefield)
{
	_currentCoordinates.angleFromCentre = _currentCoordinates.angleFromCentre - _pi/40;
//	_currentCoordinates.angleFromCentre = _currentCoordinates.angleFromCentre - gameBattlefield.get_angleBetweenLines();


	if (_currentCoordinates.angleFromCentre <= 0)
		_currentCoordinates.angleFromCentre = _pi*2;


	_currentCoordinates.x = _battlefieldCentre_x + _currentCoordinates.radiusFromCentre * cos(_currentCoordinates.angleFromCentre);
	_currentCoordinates.y = _battlefieldCentre_y + _currentCoordinates.radiusFromCentre * sin(_currentCoordinates.angleFromCentre);

}



/* Function to add to the player score by the value of integer that is passed to it
\param howMuch an integer that is added to the current total score
*/
void PlayerShip::AddScore(int howMuch)
{
	if (_score >= 0)
	{
		_score += howMuch;
	}
}


//! Returns the value of the current score
int PlayerShip::get_score()
{
	return _score;
}
