/*
-------------------------------------------------------------------------

	PlayerMissile.cpp

-------------------------------------------------------------------------
*/

#include <iostream>
#include "PlayerMissile.h"

using namespace std;


/*! Default constructor to create a simple PlayerMissile */
PlayerMissile::PlayerMissile()
{

}


/*! Alternate constructor for creating a PlayerMissile having starting coordinates from where it was fired. The constructor from the inhereted Missile class is called, where the private data variables are initialized.
	\param gamePlayerShip instance of PlayerShip whose current coordinates are stored as the starting coordinates of the PlayerMissile.
	*/
PlayerMissile::PlayerMissile(PlayerShip& gamePlayerShip)
			  :Missile(gamePlayerShip.get_radiusFromCentre(), gamePlayerShip.get_angleFromCentre(), 
					   gamePlayerShip.get_coordinate_x(), gamePlayerShip.get_coordinate_y())

{
	_crossCentre = false;
}


/*	Function that updates the coordinates and moves the PlayerMissile in the direction it was fired along the Battlefield circles
	\param gameBattlefield used in checking whether the PlayerMissile has crossed the centre or reached the other side of the Battlefield
	*/
void PlayerMissile::MoveAlongCircles(Battlefield& gameBattlefield)
{
	if (!_crossCentre)
	{
		_currentCoordinates.radiusFromCentre = _currentCoordinates.radiusFromCentre - (gameBattlefield.get_outerCircleRadius_y() / gameBattlefield.get_numberOfCircles());
	}

	else
	{
		_currentCoordinates.radiusFromCentre = _currentCoordinates.radiusFromCentre + (gameBattlefield.get_outerCircleRadius_y() / gameBattlefield.get_numberOfCircles());

		if (_currentCoordinates.radiusFromCentre > _startCoordinates.radiusFromCentre)
		{
			set_state(0);
			return;
		}
	}

	if (_currentCoordinates.radiusFromCentre < 0)
	{
		_crossCentre = true;
		_currentCoordinates.radiusFromCentre = (-1)*_currentCoordinates.radiusFromCentre;
		_currentCoordinates.angleFromCentre = _pi + _currentCoordinates.angleFromCentre;
	}

	_currentCoordinates.x = (gameBattlefield.get_battlefieldCentre_x()) + (_currentCoordinates.radiusFromCentre)*cos(_currentCoordinates.angleFromCentre);
	_currentCoordinates.y = (gameBattlefield.get_battlefieldCentre_y()) + (_currentCoordinates.radiusFromCentre)*sin(_currentCoordinates.angleFromCentre);
	
}


/*	Function that updates the coordinates and moves the PlayerMissile continuously in the direction it was fired along the Battlefield
	\param gameBattlefield used in checking whether the PlayerMissile has crossed the centre or reached the other side of the Battlefield
	*/
void PlayerMissile::MoveContinuous(Battlefield& gameBattlefield)
{
	if (!_crossCentre)
	{
		_currentCoordinates.radiusFromCentre -= 10;
	}

	else
	{
		_currentCoordinates.radiusFromCentre += 10;
		if (_currentCoordinates.radiusFromCentre > _startCoordinates.radiusFromCentre)
		{
			set_state(0);
			return;
		}
	}

	if (_currentCoordinates.radiusFromCentre < 0)
	{
		_crossCentre = true;
		_currentCoordinates.radiusFromCentre = (-1)*_currentCoordinates.radiusFromCentre;
		_currentCoordinates.angleFromCentre = _pi + _currentCoordinates.angleFromCentre;
	}

	_currentCoordinates.x = (gameBattlefield.get_battlefieldCentre_x()) + (_currentCoordinates.radiusFromCentre)*cos(_currentCoordinates.angleFromCentre);
	_currentCoordinates.y = (gameBattlefield.get_battlefieldCentre_y()) + (_currentCoordinates.radiusFromCentre)*sin(_currentCoordinates.angleFromCentre);
	
}