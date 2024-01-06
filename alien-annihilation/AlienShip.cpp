/*
-------------------------------------------------------------------------

	AlienShip.cpp

-------------------------------------------------------------------------
*/

#include "AlienShip.h"



//!Default constructor
AlienShip::AlienShip()
{
}




/*!Constructor which accepts ten parameters to create a more specific alien ship at the start of a game
\param name a string to set the name of the alien ship
\param radiusFromCentre an integer value to set the radius from the centre of the battlefield 
\param startingAngle an integer value to set the angle with respect to the zero degree angle of the battlefield
\param battlefieldCentre_x an integer value to set the x coordinate about which the alien ship rotates
\param battlefieldCentre_y an integer value to set the y coordinate about which the alien ship rotates
\param red an integer from 0 to 255 to set the red colour component of the alien ship
\param green an integer from 0 to 255 to set the green colour component of the alien ship
\param blue an integer from 0 to 255 to set the blue colour component of the alien ship
*/
AlienShip::AlienShip(string name, int radiusFromCentre, float startingAngle, 
					 int battlefieldCentre_x, int battlefieldCentre_y, int size_x, int size_y, 
					 int red, int green, int blue)
		  :Ship( name, radiusFromCentre, startingAngle, battlefieldCentre_x, battlefieldCentre_y, size_x, size_y )

{
	_colour.red = red;
	_colour.green = green;
	_colour.blue = blue;
	_circleIterator = radiusFromCentre;
}


/*!Constructor which accepts eleven parameters to create an alien ship when loading a saved game
\param name a string to set the name of the alien ship
\param radiusFromCentre an integer value to set the radius from the centre of the battlefield 
\param startingAngle an integer value to set the angle with respect to the zero degree angle of the battlefield
\param battlefieldCentre_x an integer value to set the x coordinate about which the alien ship rotates
\param battlefieldCentre_y an integer value to set the y coordinate about which the alien ship rotates
\param red an integer from 0 to 255 to set the red colour component of the alien ship
\param green an integer from 0 to 255 to set the green colour component of the alien ship
\param blue an integer from 0 to 255 to set the blue colour component of the alien ship
*/
AlienShip::AlienShip(string name, int radiusFromCentre, float startingAngle, 
					 int battlefieldCentre_x, int battlefieldCentre_y, int size_x, int size_y, int red, int green, int blue,int health)
		  :Ship( name, radiusFromCentre, startingAngle, battlefieldCentre_x, battlefieldCentre_y, size_x, size_y, health )

{
	_colour.red = red;
	_colour.green = green;
	_colour.blue = blue;
	_circleIterator = radiusFromCentre;
}









/*! Function to move the alien ship in a clockwise direction around the battlefield. Once a full revolution is complete the function advances the alien ship to the next concentric circle of the battlefield
*/
void AlienShip::MoveCounterClockwise(Battlefield& gameBattlefield)
{
	_currentCoordinates.angleFromCentre = _currentCoordinates.angleFromCentre - _pi/200.0;	// move aliens by fixed angle
//	_currentCoordinates.angleFromCentre = _currentCoordinates.angleFromCentre - gameBattlefield.get_angleBetweenLines(); // move aliens along the lines

	if (_circleIterator < gameBattlefield.get_numberOfCircles())
	{
		if (_currentCoordinates.angleFromCentre <= _pi/2)
		{
			_currentCoordinates.angleFromCentre = 5*_pi/2;
			_circleIterator++;
		}
	}

	if ( _currentCoordinates.angleFromCentre <= _pi/2)
	{
		_currentCoordinates.angleFromCentre=5*_pi/2;				// mention buffer overflow	
	}

	_currentCoordinates.radiusFromCentre = gameBattlefield.get_outerCircleRadius_y()/gameBattlefield.get_numberOfCircles()*_circleIterator;
	_currentCoordinates.x = (gameBattlefield.get_battlefieldCentre_x()) + _currentCoordinates.radiusFromCentre * cos(_currentCoordinates.angleFromCentre);
	_currentCoordinates.y = (gameBattlefield.get_battlefieldCentre_y()) + _currentCoordinates.radiusFromCentre * sin(_currentCoordinates.angleFromCentre);

	return;
}





//!Funtrion to return the number of the circle on which the alien ship is travelling
int AlienShip::get_circleIterator()
{
	return _circleIterator;
}
