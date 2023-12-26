/*
-------------------------------------------------------------------------

	Ship.cpp

-------------------------------------------------------------------------
*/

#include <iostream>
#include <cmath>
#include <math.h>
#include "Ship.h"

using namespace std;


/*! Default Ship constructor to create a simple ship */
Ship::Ship()
{
	_pi = 3.14159;
	_name = "Default Name";
	_state = 1;
	_health = 100;

	_startingCoordinates.radiusFromCentre = 100;
	_startingCoordinates.angleFromCentre = _pi/2;
	_startingCoordinates.x = 10;	//
	_startingCoordinates.y = 10;	// Note: x and y not linked to angle and radius

	_currentCoordinates.angleFromCentre = _startingCoordinates.angleFromCentre;
	_currentCoordinates.radiusFromCentre = _startingCoordinates.radiusFromCentre;
	_currentCoordinates.x = _startingCoordinates.x;
	_currentCoordinates.y = _startingCoordinates.y;

	_ellipseSize.radius_x = 5;
	_ellipseSize.radius_y = 5;

	_colour.red = 255;
	_colour.green = 255;
	_colour.blue = 255;
	_colour.transparency = 100;
}







/*!Constructor which accepts seven parameters to create a more specific ship
\param name a string to set the name of the ship
\param radiusFromCentre an integer value to set the starting radius of the ship position from the centre point of the battlefield
\param startingAngle a float value to set starting angle of the ship position with respect to the zero degree angle of the battlefield
\param battlefieldCentre_x an integer value to set the value of the centre x coordinate about which the ship will revolve
\param battlefieldCentre_y an integer value to set the value of the centre y coordinate about which the ship will revolve
\param size_x an integer to set the x radius of the size of the ship
\param size_y an integer to set the y radius of the size of the ship
*/
Ship::Ship(string name, int radiusFromCentre, float startingAngle, int battlefieldCentre_x, int battlefieldCentre_y, 
		   int size_x, int size_y)
{
	_pi = 3.14159;
	_name = name;
	_state = 1;
	_health = 99;

	_battlefieldCentre_x = battlefieldCentre_x;
	_battlefieldCentre_y = battlefieldCentre_y;

	_startingCoordinates.radiusFromCentre = radiusFromCentre;
	_startingCoordinates.angleFromCentre = startingAngle;
	_startingCoordinates.x = battlefieldCentre_x + (_startingCoordinates.radiusFromCentre)*cos(_startingCoordinates.angleFromCentre);
	_startingCoordinates.y = battlefieldCentre_y + (_startingCoordinates.radiusFromCentre)*sin(_startingCoordinates.angleFromCentre);

	_currentCoordinates.radiusFromCentre = _startingCoordinates.radiusFromCentre;
	_currentCoordinates.angleFromCentre = _startingCoordinates.angleFromCentre;
	_currentCoordinates.x = _startingCoordinates.x;
	_currentCoordinates.y = _startingCoordinates.y;


	_ellipseSize.radius_x = size_x;
	_ellipseSize.radius_y = size_y;
	_colour.red = 255;
	_colour.green = 255;
	_colour.blue = 0;
	_colour.transparency = 255;

}


/*!Constructor which accepts eight parameters to create a more specific ship
\param name a string to set the name of the ship
\param radiusFromCentre an integer value to set the starting radius of the ship position from the centre point of the battlefield
\param startingAngle a float value to set starting angle of the ship position with respect to the zero degree angle of the battlefield
\param battlefieldCentre_x an integer value to set the value of the centre x coordinate about which the ship will revolve
\param battlefieldCentre_y an integer value to set the value of the centre y coordinate about which the ship will revolve
\param size_x an integer to set the x radius of the size of the ship
\param size_y an integer to set the y radius of the size of the ship
\param health an integer to set the health value of the ship
*/
Ship::Ship(string name, int radiusFromCentre, float startingAngle, int battlefieldCentre_x, int battlefieldCentre_y,
		   int size_x, int size_y, int health)
{
	_pi = 3.14159;
	_name = name;
	_state = 1;
	_health = health;

	_battlefieldCentre_x = battlefieldCentre_x;
	_battlefieldCentre_y = battlefieldCentre_y;

	_startingCoordinates.radiusFromCentre = radiusFromCentre;
	_startingCoordinates.angleFromCentre = startingAngle;
	_startingCoordinates.x = battlefieldCentre_x + (_startingCoordinates.radiusFromCentre)*cos(_startingCoordinates.angleFromCentre);
	_startingCoordinates.y = battlefieldCentre_y + (_startingCoordinates.radiusFromCentre)*sin(_startingCoordinates.angleFromCentre);

	_currentCoordinates.radiusFromCentre = _startingCoordinates.radiusFromCentre;
	_currentCoordinates.angleFromCentre = _startingCoordinates.angleFromCentre;
	_currentCoordinates.x = _startingCoordinates.x;
	_currentCoordinates.y = _startingCoordinates.y;


	_ellipseSize.radius_x = size_x;
	_ellipseSize.radius_y = size_y;
	_colour.red = 255;
	_colour.green = 255;
	_colour.blue = 0;
	_colour.transparency = 255;

}

/*! Function to reduce the health of the ship by a certain amount. The colour of the ship reflects its health status.
/param reduceAmount the health of the ship is reduced by this integer value
*/
void Ship::ReduceHealth(int reduceAmount)
{

  	_health = _health - reduceAmount;


	if (_health == 66)
	{
		_colour.red += 0;
		_colour.green += 100;
		_colour.blue += 0;
	}

	if (_health ==33)
	{
		_colour.red += 200;
		_colour.green += 0;
		_colour.blue += 0;
	}
}


/*!Function to destroy the ship. The state of the ship is set to zero/false 
*/
void Ship::DestroyShip()
{
	_state = 0;
}




//!Accessor function that returns the value of pi
float Ship::get_pi() {return _pi;}

//!Accessor function that returns the name of the ship
string Ship::get_name() {return _name;}

//!Accessor function that returns the state of the ship
bool Ship::get_state() {return _state;}

//!Accessor function that returns the health level of the ship
int Ship::get_health() {return _health;}

//!Accessor function that returns the starting radius of the ship
int Ship::get_startingRadiusFromCentre() {return _startingCoordinates.radiusFromCentre;}

//!Accessor function that returns the starting angle of the ship
float Ship::get_startingAngleFromCentre() {return _startingCoordinates.angleFromCentre;}

//!Accessor function that returns the starting x coordinate of the ship
int Ship::get_startingCoordinate_x() {return _startingCoordinates.x;}

//!Accessor function that returns the starting y coordinate of the ship
int Ship::get_startingCoordinate_y() {return _startingCoordinates.y;}

//!Accessor function that returns the current radius of the ship from the centre point of the battlefield
int Ship::get_radiusFromCentre() {return _currentCoordinates.radiusFromCentre;}

//!Accessor function that returns the current angle of the ship with respect to the zero degree angle of the battlefield
float Ship::get_angleFromCentre() {return _currentCoordinates.angleFromCentre;}

//!Accessor function that returns the current x coordinate of the ship
int Ship::get_coordinate_x() {return _currentCoordinates.x;}

//!Accessor function that returns the current y coordinate of the ship
int Ship::get_coordinate_y() {return _currentCoordinates.y;}

//!Accessor function that returns the x radius of the size of the ship
int Ship::get_sizeRadius_x() {return _ellipseSize.radius_x;}

//!Accessor function that returns the y radius of the size of the ship
int Ship::get_sizeRadius_y() {return _ellipseSize.radius_y;}

//!Accessor function that returns the red colour component of the ship
int Ship::get_colourRed() {return _colour.red;}

//!Accessor function that returns the green colour component of the ship
int Ship::get_colourGreen() {return _colour.green;}

//!Accessor function that returns the blue colour component of the ship
int Ship::get_colourBlue() {return _colour.blue;}

//!Accessor function that returns the transparency colour component of the ship
int Ship::get_colourTransparency() {return _colour.transparency;}
