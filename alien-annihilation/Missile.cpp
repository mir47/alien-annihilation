/*
-------------------------------------------------------------------------

	Missile.cpp

-------------------------------------------------------------------------
*/

#include <iostream>
#include "Missile.h"
#include "PlayerShip.h"
#include "Ship.h"

using namespace std;


/*! Default constructor to create a simple Missile starting from an arbitrary position */
Missile::Missile()
{
	
	_pi = 3.14159;
	_state = 1;

	_startCoordinates.radiusFromCentre = 100;
	_startCoordinates.angleFromCentre = 100;
	_startCoordinates.x = 100;
	_startCoordinates.y = 100;

	_currentCoordinates.radiusFromCentre = _startCoordinates.radiusFromCentre;
	_currentCoordinates.angleFromCentre = _startCoordinates.angleFromCentre;
	_currentCoordinates.x = _startCoordinates.x;
	_currentCoordinates.y = _startCoordinates.y;

	_ellipseSize.radius_x = 2;
	_ellipseSize.radius_y = 2;

	_colour.red = 255;
	_colour.green = 255;
	_colour.blue = 255;
	_colour.transparency = 200;
}

/*! Alternate constructor for creating a Missile having starting coordinates from where it was fired
	\param start_radius	an integer value for the starting radius
	\param start_angle a float value for the starting angle
	\param start_x an integer value for the starting x coordinate
	\param start_y an integer value for the starting y coordinate
	*/
Missile::Missile (int start_radius, float start_angle, int start_x, int start_y)
{
	_pi = 3.14159;
	_state = 1;

	_startCoordinates.radiusFromCentre = start_radius;
	_startCoordinates.angleFromCentre = start_angle;
	_startCoordinates.x = start_x;
	_startCoordinates.y = start_y;

	_currentCoordinates.radiusFromCentre = _startCoordinates.radiusFromCentre;
	_currentCoordinates.angleFromCentre = _startCoordinates.angleFromCentre;
	_currentCoordinates.x = _startCoordinates.x;
	_currentCoordinates.y = _startCoordinates.y;

	_ellipseSize.radius_x = 2;
	_ellipseSize.radius_y = 2;

	_colour.red = 200;
	_colour.green = 200;
	_colour.blue = 200;
	_colour.transparency = 255;
}


/*! Mutator function to alter the state of the Missile object
	\param newState a 1 or 0 representing alive or dead
	*/
void Missile::set_state (bool newState)
{
	_state = newState;
}

/*! Function that sets the state to 0 i.e. destroys missile */
void Missile::DestroyMissile()
{
	_state = 0;
}


/*! Accessor function to return the value of pi */
float Missile::get_pi() {return _pi;}

/*! Accessor function to return the state of the missile */
bool Missile::get_state() {return _state;}


/*! Accessor function to return the radius (from the centre of the Battlefield) from which the missile was created */
int Missile::get_startingRadiusFromCentre() {return _startCoordinates.radiusFromCentre;}
/*! Accessor function to return the angle (from the 0 degree reference of the Battlefield) from which the missile was created */
float Missile::get_startingAngleFromCentre() {return _startCoordinates.angleFromCentre;}
/*! Accessor function to return the x coordinate from which the Missile started */
int Missile::get_startingCoordinate_x() {return _startCoordinates.x;}
/*! Accessor function to return the y coordinate from which the Missile started */
int Missile::get_startingCoordinate_y() {return _startCoordinates.y;}


/*! Accessor function to return the current radius (from the centre of the Battlefield) */
int Missile::get_radiusFromCentre() {return _currentCoordinates.radiusFromCentre;}
/*! Accessor function to return the current angle (from the 0 degree reference of the Battlefield) */
float Missile::get_angleFromCentre() {return _currentCoordinates.angleFromCentre;}
/*! Accessor function to return the current x coordinate */
int Missile::get_coordinate_x() {return _currentCoordinates.x;}
/*! Accessor function to return the current y coordinate */
int Missile::get_coordinate_y() {return _currentCoordinates.y;}


/*! Accessor function to return the x radius of the Missile ellipse size */
int Missile::get_sizeRadius_x() {return _ellipseSize.radius_x;}
/*! Accessor function to return the y radius of the Missile ellipse size */
int Missile::get_sizeRadius_y() {return _ellipseSize.radius_y;}


/*! Accessor function to return the value of the red colour component (ranges from 0 to 255) */
int Missile::get_colourRed() {return _colour.red;}
/*! Accessor function to return the value of the green colour component (ranges from 0 to 255) */
int Missile::get_colourGreen() {return _colour.green;}
/*! Accessor function to return the value of the blue colour component (ranges from 0 to 255) */
int Missile::get_colourBlue() {return _colour.blue;}
/*! Accessor function to return the value of the transparency component (ranges from 0 to 255) */
int Missile::get_colourTransparency() {return _colour.transparency;}
