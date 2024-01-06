/*
-------------------------------------------------------------------------
	
	Battlefield.cpp

-------------------------------------------------------------------------
*/

#include <iostream>
#include <cmath>
#include <math.h>
#include "Battlefield.h"

using namespace std;

/*! Default Battlefield constructor to create a simple battlefield. The number of circles and number of lines that the Battlefield will comprise of are set to predetermined values  */
Battlefield::Battlefield():		
	_pi (3.14159),

	_battlefieldWidth  (600),
	_battlefieldHeight (600),

	_battlefieldCentre_x (_battlefieldWidth/2-1),
	_battlefieldCentre_y (_battlefieldHeight/2-1),

	_outerCircleRadius_x (200),
	_outerCircleRadius_y (200), 

	_numberOfCircles (40),
	_numberOfLines (120),

	_circleColour_red (255),
	_circleColour_green (255),
	_circleColour_blue (255),
	_circleColour_transparency (20),

	_lineColour_red (255),
	_lineColour_green (255),
	_lineColour_blue (255),
	_lineColour_transparency (10),

	_angleBetweenLines (_pi*2/_numberOfLines)	// will give four line crosshair ie. 4 lines 90deg apart,
												// if _numberOfLines = 4.


{

	CreateBattlefieldCirclesVector();
	CreateBattlefieldLinesVector();
}




// parameters: numberOfCircles numberOfLines read in from text level file

/*!Constructor which accepts four parameters to create a more specific battlefield
\param WINDOW_WIDTH an integer value to set the width of the window
\param WINDOW_HEIGHT an integer value to set the height of the window 
\param numberOfCircles an integer value to set the number of circles of the battlefield
\param numberOfLines an integer value to set the number of lines of the battlefield
*/
Battlefield::Battlefield(int& WINDOW_WIDTH, int& WINDOW_HEIGHT, int& numberOfCircles, int& numberOfLines)
{	
	_pi = 3.14159;

	_battlefieldWidth =  WINDOW_WIDTH;
	_battlefieldHeight = WINDOW_HEIGHT;

	_battlefieldCentre_x =_battlefieldWidth/2-1;
	_battlefieldCentre_y =_battlefieldHeight/2-1;

	
	_outerCircleRadius_x =300;		
	_outerCircleRadius_y =300;		

	_numberOfCircles =numberOfCircles;
	_numberOfLines =numberOfLines;

	_circleColour_red =0;
	_circleColour_green =50;
	_circleColour_blue =0;
	_circleColour_transparency =100;

	_lineColour_red =0;
	_lineColour_green =50;
	_lineColour_blue = 0;
	_lineColour_transparency = 100;

	_angleBetweenLines = 2*_pi/_numberOfLines;



//	_angleBetweenLines = 2*_pi/_numberOfLines;

	CreateBattlefieldCirclesVector();
	CreateBattlefieldLinesVector();
}




/*! Function to create the vector of circles that make up the battlefield
*/
void Battlefield::CreateBattlefieldCirclesVector()
{
	_vectorBattlefieldCircles.clear();
	Circle tempCircle;
	tempCircle.centre_x = _battlefieldCentre_x;
	tempCircle.centre_y = _battlefieldCentre_y;
	tempCircle.colour_red = _circleColour_red;
	tempCircle.colour_green = _circleColour_green;
	tempCircle.colour_blue = _circleColour_blue;
	tempCircle.colour_transparency = _circleColour_transparency;

	for (int i=1 ; i<=_numberOfCircles ; i++) 
	{
		tempCircle.radius_x = _outerCircleRadius_x*i/_numberOfCircles;
		tempCircle.radius_y = _outerCircleRadius_y*i/_numberOfCircles;

		_vectorBattlefieldCircles.push_back(tempCircle);
	}
}



/*! Function to create the vector of lines that make up the battlefield
*/
void Battlefield::CreateBattlefieldLinesVector()
{
	_vectorBattlefieldLines.clear();
	Line tempLine;
	tempLine.start_x = _battlefieldCentre_x;
	tempLine.start_y = _battlefieldCentre_y;
	tempLine.colour_red = _lineColour_red;
	tempLine.colour_green = _lineColour_green;
	tempLine.colour_blue = _lineColour_blue;
	tempLine.colour_transparency = _lineColour_transparency;
	
	for (double i=0.0 ; i<2*_pi; i=i+_angleBetweenLines) 
	{
		tempLine.end_x = _battlefieldCentre_x + _outerCircleRadius_y*cos(i);
		tempLine.end_y = _battlefieldCentre_y + _outerCircleRadius_y*sin(i);

		_vectorBattlefieldLines.push_back(tempLine);

	}
}


//! Accessor function that returns the value of pi
float Battlefield::get_pi() {return _pi;}

//! Accessor function that returns the width of the battlefield
int Battlefield::get_battlefieldWidth() {return _battlefieldWidth;}

//! Accessor function that returns the height of the battlefield
int Battlefield::get_battlefieldHeight() {return _battlefieldHeight;}

//! Accessor function that returns the x coordinate the centre of the battlefield
int Battlefield::get_battlefieldCentre_x() {return _battlefieldCentre_x;}

//! Accessor function that returns the y coordinate the centre of the battlefield
int Battlefield::get_battlefieldCentre_y() {return _battlefieldCentre_y;}

//! Accessor function that returns the x radius of the outer-most circle of the battlefield
int Battlefield::get_outerCircleRadius_x() {return _outerCircleRadius_x;}

//! Accessor function that returns the y radius of the outer-most circle of the battlefield
int Battlefield::get_outerCircleRadius_y() {return _outerCircleRadius_y;}

//! Accessor function that returns the number of circles that make up the battlefield
int Battlefield::get_numberOfCircles() {return _numberOfCircles;}

//! Accessor function that returns the number of lines that make up the battlefield
int Battlefield::get_numberOfLines() {return _numberOfLines;}

//! Accessor function that returns the red colour component of the circles (ranges from 0 to 255)
int	Battlefield::get_circleColour_red() {return _circleColour_red;}

//! Accessor function that returns the green colour component of the circles (ranges from 0 to 255)
int	Battlefield::get_circleColour_green() {return _circleColour_green;}

//! Accessor function that returns the blue colour component of the circles (ranges from 0 to 255)
int	Battlefield::get_circleColour_blue() {return _circleColour_blue;}

//! Accessor function that returns the transparency component of the circles (ranges from 0 to 255)
int	Battlefield::get_circleColour_transparency() {return _circleColour_transparency;}

//! Accessor function that returns the red colour component of the lines (ranges from 0 to 255)
int	Battlefield::get_lineColour_red() {return _lineColour_red;}

//! Accessor function that returns the green colour component of the lines (ranges from 0 to 255)
int	Battlefield::get_lineColour_green() {return _lineColour_green;}

//! Accessor function that returns the blue colour component of the lines (ranges from 0 to 255)
int	Battlefield::get_lineColour_blue() {return _lineColour_blue;}

//! Accessor function that returns the transparency component of the lines (ranges from 0 to 255)
int	Battlefield::get_lineColour_transparency() {return _lineColour_transparency;}

//! Accessor function that returns value of the angle between each line in the battlefield
float Battlefield::get_angleBetweenLines() {return _angleBetweenLines;}

//! Accessor function that returns the vector of the circles that make up the battlefield
vector<Circle> Battlefield::get_vectorBattlefieldCircles() {return _vectorBattlefieldCircles;}

//! Accessor function that returns the vector of the lines that make up the battlefield
vector<Line> Battlefield::get_vectorBattlefieldLines() {return _vectorBattlefieldLines;}

/*
 This function sets the width of the Battlefield window
 \param windowWidth: this is the value that the width of the Battlefield window is set to
*/
void Battlefield::set_battlefieldWidth(int windowWidth)
{	_battlefieldWidth = windowWidth; }

/*
 This function sets the height of the Battlefield window
 \param windowHeight: this is the value that the height of the Battlefield window is set to
*/
void Battlefield::set_battlefieldHeight(int windowHeight)
{	_battlefieldHeight = windowHeight; }

/*
 This function sets the centre x coordinate of the Battlefield
*/
void Battlefield::set_battlefieldCentre_x()
{	_battlefieldCentre_x =_battlefieldWidth/2-1; }

/*
 This function sets the centre y coordinate of the Battlefield
*/
void Battlefield::set_battlefieldCentre_y()
{	_battlefieldCentre_y =_battlefieldHeight/2-1; }

/*
 This function sets the x radius of outer-most circle of the Battlefield
*/
void Battlefield::set_outerCircleRadius_x(int outerCircleRadius_x)
{	_outerCircleRadius_x = outerCircleRadius_x; }

/*
 This function sets the y radius of outer-most circle of the Battlefield
*/
void Battlefield::set_outerCircleRadius_y(int outerCircleRadius_y)
{	_outerCircleRadius_y = outerCircleRadius_y; }

/*
 This function sets the number of circles that the Battlefield comprises of
*/
void Battlefield::set_numberOfCircles(int numberOfCircles)
{	_numberOfCircles =numberOfCircles; }

/*
 This function sets the number of lines that the Battlefield comprises of
*/
void Battlefield::set_numberOfLines(int numberOfLines)
{	_numberOfLines =numberOfLines; }

/*
 This function sets the red colour component of a circle on the Battlefield
*/
void Battlefield::set_circleColour_red(int red)
{	_circleColour_red = red; }

/*
 This function sets the green colour component of a circle on the Battlefield
*/
void Battlefield::set_circleColour_green(int green)
{	_circleColour_green = green; }

/*
 This function sets the blue colour component of a circle on the Battlefield
*/
void Battlefield::set_circleColour_blue(int blue)
{	_circleColour_blue = blue; }

/*
 This function sets the transparency colour component of a circle on the Battlefield
*/
void Battlefield::set_circleColour_transparency(int trans)
{	_circleColour_transparency = trans; }

/*
 This function sets the red colour component of a line on the Battlefield
*/
void Battlefield::set_lineColour_red(int red)
{	_lineColour_red = red; }

/*
 This function sets the green colour component of a line on the Battlefield
*/
void Battlefield::set_lineColour_green(int green)
{	_lineColour_green = green; }

/*
 This function sets the blue colour component of a line on the Battlefield
*/
void Battlefield::set_lineColour_blue(int blue)
{	_lineColour_blue = blue; }

/*
 This function sets the transparency colour component of a line on the Battlefield
*/
void Battlefield::set_lineColour_transparency(int trans)
{	_lineColour_transparency = trans; }

/*
 This function sets the angle between the lines that make up the Battlefield 
*/
void Battlefield::set_angleBetweenLines()
{	_angleBetweenLines = 2*_pi/_numberOfLines; }





