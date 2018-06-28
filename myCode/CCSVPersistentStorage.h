/*
 * CNavigationSystemPersistentStorage.h
 *
 *  Created on: Dec 1, 2017
 *      Author: arjun
 */

#ifndef CCSVPERSISTENTSTORAGE_H_
#define CCSVPERSISTENTSTORAGE_H_

#include<string>
#include "CPersistentStorage.h"

class CCSVPersistentStorage: public CPersistentStorage
{
private:
	/**
	 * Name of the source for reading data
	 */
	std::string m_mediaName;
public:
	/**
	 * Constructor
	 */
	CCSVPersistentStorage();

	/**
	 * Destructor
	 */
	~CCSVPersistentStorage();

	/**
	 * Setter for m_mediaName
	 * @param name Name to be set.
	 */
	void setMediaName(std::string name);

	/**
	 * Write the data from database into storage of m_mediaName
	 * @param waypointDb The Waypoint database
	 * @param poiDb The POI database
	 * @return bool if the operation was successful or not
	 */
	bool writeData (const CWpDatabase& waypointDb, const CPoiDatabase& poiDb);

	/**
	 * Read data from storage into database
	 * @param waypointDb The Waypoint database
	 * @param poiDb The POI database
	 * @param mode of type MergeMode determines if database is to be cleared or data should be appended to it
	 * @return bool if the operation was successful or not
	 */
	bool readData (CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode);

private:
	/**
	 * Gets the delimiter for a line
	 * @param inputLine The string from which delimiter is to be determined
	 * @return char, the delimiter for the input line
	 */
	char getDelimiter(std::string inputLine);
	/**
	 * Trims the coordinates and check for valid double values
	 * @param longitude_str the latitude in string format
	 * @param longitude_str the longitude in string format
	 * @param latitude Container for latitude in double format
	 * @param longitude Container for longitude in double format
	 * @return bool if the coordinates are valid
	 */
	bool cleanAndValidateGeographicCoordinates(std::string latitude_str,
			std::string longitude_str, double &latitude, double &longitude);
	/**
	 * Displays any error passed to it in a particular format
	 * @param problem brief of the issue occurred
	 * @param lineNumber the line number in which issue occurred
	 * @param lineContent the content of the line where the issue occurred
	 */
	void displayError(std::string problem,
			int lineNumber, std::string lineContent);
};

#endif /* CCSVPERSISTENTSTORAGE_H_ */
