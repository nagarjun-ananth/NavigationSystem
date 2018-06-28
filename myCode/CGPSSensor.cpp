/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CGPSSensor.cpp
 * Author          :	Nagarjun Anantha Padmanabha
 * Description     :	This contains the implementation of the class CGPS Sensor
 * 					which will be used by the CNavigationSystem.
 *
 *
 ****************************************************************************/

// System Headers
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

// Own Headers
#include "CGPSSensor.h"

// Implementation

CGPSSensor::CGPSSensor()
{
}

CWaypoint CGPSSensor::getCurrentPosition()
{
	CWaypoint currentPosition;
	string input = "";
	bool invalidInput = true;
	double latitude, longitude;
	cout << "GPS Sensor" << endl;

	/* The following approach is used to ensure that no value other than
	 * a double is accepted for latitude and longitude. The alternative
	 * approaches may still allow a value like "9pcs" as valid double value.
	 * This below approach takes care of all such scenarios.
	 * Feeds input stream to the double variable and checks for any
	 * leftovers to determine if the input consisted of any non numeric characters,
	 * except for '.' and 'e'(exponent).
	 */

	/*Check for valid double value for latitude to be entered by the user.*/
	while (invalidInput)
	{
		cout << "Enter the latitude : " << endl;
		getline(cin, input);
		stringstream myStream(input);
		myStream >> latitude;
		if (!myStream.eof())
			cout
					<< "ERROR: Invalid latitude value. Please enter a valid value :"
					<< endl;
		else
		{
			invalidInput = false;
		}
	}

	/* Check for valid double value for longitude to be entered by the user. */
	invalidInput = true;
	while (invalidInput)
	{
		cout << "Enter the longitude : " << endl;
		getline(cin, input);
		stringstream myStream(input);
		myStream >> longitude;
		if (!myStream.eof())
			cout
					<< "ERROR: Invalid longitude value. Please enter a valid value :"
					<< endl;
		else
		{
			invalidInput = false;
		}
	}

	currentPosition = CWaypoint("Current Position", latitude, longitude);
	return currentPosition;
}
