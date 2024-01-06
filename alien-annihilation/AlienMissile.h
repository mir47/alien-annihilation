/*
-------------------------------------------------------------------------

	AlienMissile.h

-------------------------------------------------------------------------
*/

#ifndef ALIENMISSILE_H
#define ALIENMISSILE_H

#include <iostream>
#include "AlienShip.h"
#include "Battlefield.h"
#include "Missile.h" 

using namespace std;

//! Class implementation to create a AlienMissile
/*! AlienMissile is a class that creates alien missiles and contains functions for moving these missiles. AlienMissile is derived from the Missile class.
*/
class AlienMissile : public Missile
{
public:
	//! The default constructor
	AlienMissile();
	//! Constructor which accepts four parameters
	AlienMissile(int start_radius, float start_angle, int start_x, int start_y);

	//! Moves PlayerMissile continuously outward at the angle it was fired
	void MoveContinuous(Battlefield& gameBattlefield);
};

#endif
