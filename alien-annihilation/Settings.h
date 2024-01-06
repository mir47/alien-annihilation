#ifndef SETTINGS_H
#define SETTINGS_H

#include <fstream>

using namespace std;

//! Class implementation of Settings
/*! Settings is a class that controls the settings of the game
*/
class Settings
{
public:

	//! Default constructor
	Settings ();
	//! Constructor with one parameter
	Settings (string settings); //Settings is from 1-3

	//! Returns the number of lines
	int get_numberOfLines();
	//! Returns the number of circles
	int get_numberOfCircles();


private:
	int _numberOfLines;//!<Stores the number of lines
	int _numberOfCircles;//!<Stores the number of circles
	ifstream inData;//!<Stores the data read in from the file
};
#endif