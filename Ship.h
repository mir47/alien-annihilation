/*
-------------------------------------------------------------------------

	Ship.h

-------------------------------------------------------------------------
*/

#ifndef SHIP_H
#define SHIP_H

#include <iostream>
#include <string>

using namespace std;



//! structure implementation of Coordinates
/*! A struct to store both cartisian and polar coordinates
*/
struct Coordinates 
{
	int radiusFromCentre;//!<Stores radius from the centre point of the battlefield
	float angleFromCentre;//!<Stores the angle with respect to the centre point of the battlefield
	int x;//!<Stores the x coordinate value
	int y;//!<Stores the y coordinate value

};


//! structure implementation of EllipseSize
/*! A struct to store the size of an ellipse
*/
struct EllipseSize 
{
	int radius_x;//!<Stores the x radius of the ellipse
	int radius_y;//!<Stores the y radius of the ellipse
};


//! structure implementation of Colour
/*! A struct to store four colour components
*/
struct Colour 
{
	int red;//!<Stores the red colour component
	int green;//!<Stores the green colour component 
	int blue;//!<Stores the blue colour component 
	int transparency;//!<Stores the transparency component 
};


//! Class implementation for a single Ship 
/*! Class that AlienShip and PlayerShip inherit from
*/
class Ship
{
public:

	//! Default constructor
	Ship();


	//! Constructor with parameters
	Ship(string name, int radiusFromCentre, float startingAngle, int battlefieldCentre_x, int battlefieldCentre_y, 
		 int size_x, int size_y);

	Ship(string name, int radiusFromCentre, float startingAngle, int battlefieldCentre_x, int battlefieldCentre_y, 
		 int size_x, int size_y, int health);

	//! Function to reduce the health value of a ship
	void ReduceHealth(int reduceAmount);

	//! Function to destroy a ship
	void DestroyShip();


//	virtual void MoveShip();


// Accessor functions:
	
	//! Returns value of pi
	float get_pi();

	//! Returns the name of the ship
	string get_name();
	
	//! Returns the state of the ship
	bool get_state();

	//! Returns the health level of the ship
	int get_health();

	//! Returns the starting radius of the ship
	int get_startingRadiusFromCentre();

	//! Returns the starting angle of the ship
	float get_startingAngleFromCentre();

	//! Returns the starting x coordinate of the ship
	int get_startingCoordinate_x();

	//! Returns the starting y coordinate of the ship
	int get_startingCoordinate_y();
	
	//! Returns the current radius of the ship
	int get_radiusFromCentre();

	//! Returns the current angle of the ship
	float get_angleFromCentre();
	
	//! Returns the current x coordinate of the ship
	int get_coordinate_x();
	
	//! Returns the current y coordinate of the ship
	int get_coordinate_y();
	
	//! Returns the x radius of the size of the ship
	int get_sizeRadius_x();

	//! Returns the y radius of the size of the ship
	int get_sizeRadius_y();
	
	//! Returns the red colour component of the ship
	int get_colourRed();

	//! Returns the green colour component of the ship
	int get_colourGreen();

	//! Returns the blue colour component of the ship
	int get_colourBlue();

	//! Returns the transparency colour component of the ship
	int get_colourTransparency();



protected:

	float _pi;//!< Stores the value of pi 


	string _name;//!< Stores the name of the ship 

	bool _state;//!< Stores state of the ship  

	int _health;//!< Stores health of the ship  



	int _battlefieldCentre_x; //!< Stores the centre x coordinate of the battlefield  
	int _battlefieldCentre_y; //!< Stores the centre y coordinate of the battlefield

// structs -----------------------------
	Coordinates _startingCoordinates;//!< Stores the starting coordinates of the ship
	Coordinates _currentCoordinates;//!< Stores the current coordinates of the ship
	EllipseSize _ellipseSize; //!< Stores the x and y radii of the ship ellipse				
	Colour _colour; //!< Stores the colours of the ship

};

#endif