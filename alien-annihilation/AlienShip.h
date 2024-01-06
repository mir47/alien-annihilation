/*
-------------------------------------------------------------------------

	AlienShip.h

-------------------------------------------------------------------------
*/

#ifndef ALIENSHIP_H
#define ALIENSHIP_H

#include "Battlefield.h"
#include "Ship.h"
 
using namespace std;

//! Class implementation for a single AlienShip. Derived class of Ship using public inheritance.
class AlienShip: public Ship
{
public:

	//! Default constructor
	AlienShip();
	
	//! Constructor which accepts ten parameters
	AlienShip(string name, int radiusFromCentre, float startingAngle, int battlefieldCentre_x, int battlefieldCentre_y,
			  int size_x, int size_y, int red, int green, int blue);
	
	//! Constructor which accepts eleven parameters
	AlienShip(string name, int radiusFromCentre, float startingAngle, int battlefieldCentre_x, int battlefieldCentre_y, 
			  int size_x, int size_y, int red, int green, int blue, int health);



	//! Function to move alien ship clockwise
	void MoveClockwise(Battlefield& gameBattlefield);

	//! Function to move alien ship counter clockwise
	void MoveCounterClockwise(Battlefield& gameBattlefield);

	//!Function to return the number of the circle that the alien is on
	int get_circleIterator();


private:

	int _circleIterator; //!<Stores the number of the circle that the alien is on


};
#endif