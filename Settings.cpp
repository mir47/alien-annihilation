#include "Settings.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;


/*!	Default constructor initialises game with Settings 1
	*/
Settings::Settings()
{
	ifstream inData ("settings1.txt");
	if (inData.is_open())
	{
		while(! inData.eof())
		{
			inData >> _numberOfCircles >> _numberOfLines;
			
		}
		inData.close();
	}
	else cout << "UNABLE TO OPEN FILE" << endl;
}
/* Constructor which accepts a string that describes the settings file to be read in from- an example of this is "settings1.txt"
\param settigs is a string that corresponds to the name of the text file that is to be read in from
*/
Settings::Settings (string settings)
{
	ifstream inData(settings.c_str());
	
	if (inData.is_open())
	{
		while(! inData.eof())
		{
			inData >> _numberOfCircles >> _numberOfLines;
			
		}
		inData.close();
	}
	else cout << "UNABLE TO OPEN FILE" << endl;

	
}
//! Function that returns the number of lines that is read from the settings file and stored in the class Settings data member _numberOfLines 
int Settings::get_numberOfLines(){return _numberOfLines;}
//! Function that returns the number of circles that is read from the settings file and stored in the class Settings data member _numberOfCircles
int Settings::get_numberOfCircles(){return _numberOfCircles;}
