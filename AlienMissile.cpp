/*
-------------------------------------------------------------------------

	AlienMissile.cpp

-------------------------------------------------------------------------
*/

#include <iostream>
#include "AlienMissile.h"

using namespace std;


/*! Default constructor to create a simple AlienMissile */
AlienMissile::AlienMissile()
{

}
/*! Constructor with parameters for AlienMissile- all of which are passed on to Missile constructor which accepts four parameters
\param int start_radius: the radius at which the alien missile starts
\param float start_angle: the angle at which the alien missile starts
\param int start_x: the x coordinate at which the alien missile starts
\param int start_y: the y coordinate at which the alien missile starts
*/
AlienMissile::AlienMissile(int start_radius, float start_angle, int start_x, int start_y)
					  :Missile(start_radius, start_angle, start_x, start_y)
{

}




/*	Function that updates the coordinates and moves the AlienMissile continuously outward at the angle it was fired along the Battlefield
	\param gameBattlefield: used in checking whether the AlienMissile has reached the outer-most circle
	*/
void AlienMissile::MoveContinuous(Battlefield& gameBattlefield)
{
	_currentCoordinates.radiusFromCentre += 5;
	if (_currentCoordinates.radiusFromCentre > gameBattlefield.get_outerCircleRadius_y())
	{
		set_state(0);
		return;
	}

	_currentCoordinates.x = (gameBattlefield.get_battlefieldCentre_x()) + (_currentCoordinates.radiusFromCentre)*cos(_currentCoordinates.angleFromCentre);
	_currentCoordinates.y = (gameBattlefield.get_battlefieldCentre_y()) + (_currentCoordinates.radiusFromCentre)*sin(_currentCoordinates.angleFromCentre);
	
}