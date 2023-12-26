/*
-------------------------------------------------------------------------

	Missile.h

-------------------------------------------------------------------------
*/
  
#ifndef MISSILE_H
#define MISSILE_H

#include <iostream>
#include "PlayerShip.h"
#include "Ship.h"

using namespace std;


//! Class implementation to create a Missile
/*!	The class creates a missile in the shape of an ellipse. It has numerous functions to allow for the movement of a missile and to access the private attributes of the missile object
*/
class Missile
{
public:
	//! The default constructor
	Missile();
	//! Constructor with parameters
	Missile(int start_radius, float start_angle, int start_x, int start_y);

	//! Virtual function ensures derived classes employ this function
//	virtual void Move();

	//! Sets the missile state
	void set_state(bool newState);
	//! Destroys the missile
	void DestroyMissile();

	//! Return the stored value of pi
	float get_pi();

	//! Return the state
	bool get_state();

	//! Return the radius from which the missile was created
	int get_startingRadiusFromCentre();
	//! Return the angle from which the missile was created
	float get_startingAngleFromCentre();
	//! Return the x coordinate from which the missile was created
	int get_startingCoordinate_x();
	//! Return the y coordinate from which the missile was created
	int get_startingCoordinate_y();

	//! Return the current radius
	int get_radiusFromCentre();
	//! Return the current angle
	float get_angleFromCentre();
	//! Return the current x coordinate
	int get_coordinate_x();
	//! Return the current y coordinate
	int get_coordinate_y();

	//! Return the x radius of the ellipse size
	int get_sizeRadius_x();
	//! Return the y radius of the ellipse size
	int get_sizeRadius_y();

	//! Return the value of red colour component
	int get_colourRed();
	//! Return the value of green colour component
	int get_colourGreen();
	//! Return the value of blue colour component
	int get_colourBlue();
	//! Return the value of transparency component
	int get_colourTransparency();

protected:
	float _pi; //!< Stores the value of pi
	bool _state; //!< Stores the boolean state of the missile: 1 or 0 (alive or dead)

	Coordinates _startCoordinates; //!< Stores the starting coordinates in a struct
	Coordinates _currentCoordinates; //!< Stores the current coordinates in a struct
	EllipseSize _ellipseSize; //!< Stores the x and y radius sizes of the missile ellipse
	Colour _colour; //!< Stores the four colour components
};

#endif