/*
-------------------------------------------------------------------------
	
	Battlefield.h

-------------------------------------------------------------------------
*/

#ifndef BATTLEFIELD_H
#define BATTLEFIELD_H

#include <iostream> 
#include <cmath>		
#include <math.h>
#include <vector>

using namespace std;


//! Struct implementation of Line
/*! A struct to store all the properties of a single Line on the Battlefield
*/
struct Line 
{ 
	int start_x;//!< Stores the value of starting x coordinate of the line
	int start_y;//!< Stores the value of starting y coordinate of the line
	int end_x;//!< Stores the value of ending x coordinate of the line
	int end_y;//!< Stores the value of ending x coordinate of the line
	int colour_red;//!< Stores the value of the red colour component of the line
	int colour_green;//!< Stores the value of the green colour component of the line
	int colour_blue;//!< Stores the value of the blue colour component of the line
	int colour_transparency;//!< Stores the value of the transparancy colour component of the line
};


//! Structure implementation of Circle
/*! A struct to store all the properties of a single Circle on the Battlefield 
*/
struct Circle 
{	
	int centre_x;//!< Stores the centre x coordinate of the ellipse
	int centre_y;//!< Stores the centre y coordinate of the ellipse
	int radius_x;//!< Stores the x radius of the ellipse
	int radius_y;//!< Stores the y radius of the ellipse
	int colour_red; //!< Stores the red colour component of the ellipse
	int colour_green;//!< Stores the green colour component of the ellipse
	int colour_blue;//!< Stores the blue colour component of the ellipse
	int colour_transparency; //!< Stores the transparency colour component of the ellipse
};





//! Class implementation to store properties of a Battlefield
class Battlefield
{
public:

	//! Default constructor
	Battlefield();

	//! Constructor which accepts four parameters for Battlefield implementation
	Battlefield(int& WINDOW_WIDTH, int& WINDOW_HEIGHT, int& numberOfCircles, int& numberOfLines);

	//! Destructor
	~Battlefield(){ cout << "BF destructor called" << endl;};

	//! Set the width of the Battlefield window
	void set_battlefieldWidth(int WINDOW_WIDTH);

	//! Set the height of the Battlefield window
	void set_battlefieldHeight(int WINDOW_HEIGHT);

	//! Set the centre x coordinate of the Battlefield
	void set_battlefieldCentre_x();

	//! Set the centre y coordinate of the Battlefield
	void set_battlefieldCentre_y();

	//! Set the x radius of the outer-most circle of the Battlefield
	void set_outerCircleRadius_x(int outerCircleRadius_x);

	//! Set the y radius of the outer-most circle of the Battlefield
	void set_outerCircleRadius_y(int outerCircleRadius_y);

	//! Set the number of circles that the Battlefield will comprise of
	void set_numberOfCircles(int numberOfCircles);

	//! Set the number of lines that the Battlefield will comprise of
	void set_numberOfLines(int numberOfLines);

	//! Set the red colour component of the a particular circle on the Battlefield
	void set_circleColour_red(int red);
	
	//! Set the green colour component of the a particular circle on the Battlefield
	void set_circleColour_green(int green);
	
	//! Set the blue colour component of the a particular circle on the Battlefield
	void set_circleColour_blue(int blue);
	
	//! Set the transparency colour component of the a particular circle on the Battlefield
	void set_circleColour_transparency(int trans);
	
	//! Set the red colour component of the a particular line on the Battlefield
	void set_lineColour_red(int red);
	
	//! Set the green colour component of the a particular line on the Battlefield
	void set_lineColour_green(int green);
	
	//! Set the blue colour component of the a particular line on the Battlefield
	void set_lineColour_blue(int blue);
	
	//! Set the transparency colour component of the a particular line on the Battlefield
	void set_lineColour_transparency(int trans);
	
	//! Set the angle between each line that makes up the Battlefield
	void set_angleBetweenLines();




	//! Returns value of pi
	float get_pi();

	//! Returns the width of the battlefield 
	int get_battlefieldWidth();

	//! Returns the height of the battlefield
	int get_battlefieldHeight();

	//! Returns the x coordinate value of the centre of the battlefield
	int get_battlefieldCentre_x();

	//! Returns the y coordinate value of the centre of the battlefield
	int get_battlefieldCentre_y();

	//! Returns the x radius of the outer-most circle of the battlefield
	int get_outerCircleRadius_x();

	//! Returns the y radius of the outer-most circle of the battlefield
	int get_outerCircleRadius_y();

	//! Returns the number of circles that make up the battlefield
	int get_numberOfCircles();

	//! Returns the number of lines that make up the battlefield
	int get_numberOfLines();

	//! Returns the value of the red component of the circles
	int	get_circleColour_red();

	//! Returns the value of the red component of the circles
	int	get_circleColour_green();

	//! Returns the value of the blue component of the circles
	int	get_circleColour_blue();

	//! Returns the value of the transparency component of the circles
	int	get_circleColour_transparency();

	//! Returns the value of the red component of the lines
	int	get_lineColour_red();

	//! Returns the value of the red component of the lines
	int	get_lineColour_green();

	//! Returns the value of the blue component of the lines
	int	get_lineColour_blue();

	//! Returns the value of the transparency component of the lines
	int	get_lineColour_transparency();

	//! Returns value of the angle between each line in the battlefield
	float get_angleBetweenLines();

	//! Returns the vector of the circles that make up the battlefield
	vector<Circle> get_vectorBattlefieldCircles();

	//! Returns the vector of the lines that make up the battlefield
	vector<Line> get_vectorBattlefieldLines();

	//! Returns the battlefield vector of circles 
	void CreateBattlefieldCirclesVector();

	//! Returns the battlefield vector of circles 
	void CreateBattlefieldLinesVector();



private:
	
	float _pi; //!< Stores the value of pi 

	int _battlefieldWidth; //!< Stores the value of the ballefield width 
	int _battlefieldHeight;//!< Stores the value of the ballefield height 

	int _battlefieldCentre_x; //!< Stores the value of the ballefield centre x coordinate  
	int _battlefieldCentre_y; //!< Stores the value of the ballefield centre y coordinate

	int _outerCircleRadius_x; //!< Stores the x radius of the outer-most circle
	int _outerCircleRadius_y;//!< Stores the y radius of the outer-most circle

	int _numberOfCircles;//!< Stores the number of circles that make up the battlefield
	int	_numberOfLines;//!< Stores the number of lines that make up the battlefield

	int	_circleColour_red;//!< Stores the red colour component of the circles that make up the battlefield
	int	_circleColour_green;//!< Stores the green colour component of the circles that make up the battlefield
	int	_circleColour_blue;//!< Stores the blue colour component of the circles that make up the battlefield
	int	_circleColour_transparency;//!< Stores the transparency colour component of the circles that make up the battlefield

	int	_lineColour_red;//!< Stores the red colour component of the lines that make up the battlefield
	int	_lineColour_green;//!< Stores the green colour component of the lines that make up the battlefield
	int	_lineColour_blue;//!< Stores the blue colour component of the lines that make up the battlefield
	int	_lineColour_transparency;//!< Stores the transparency colour component of the lines that make up the battlefield

	float _angleBetweenLines; //!< Stores the value of the angle between each line in the battlefield 

	vector<Circle> _vectorBattlefieldCircles; //!< Stores the vector of circles that make up the battlefield
	vector<Line> _vectorBattlefieldLines; //!< Stores the vector of lines that make up the battlefield


};

#endif

