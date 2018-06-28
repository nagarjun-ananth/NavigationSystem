/*
 * CJsonPersistence.h
 *
 *  Created on: Jan 6, 2018
 *      Author: arjun
 */

#ifndef CJSONPERSISTENCE_H_
#define CJSONPERSISTENCE_H_

#include "CPersistentStorage.h"

class CJsonPersistence: public CPersistentStorage
{
private:
	/**
	 * Name of the source for reading data
	 */
	std::string m_mediaName;

	/**
	 * Convert any double value to a string
	 * @param doubleValue the value to be converted to string
	 * @return string converted string value
	 */
	string convertDoubleToString(double doubleValue);

	/**
	 * Convert the given values to a predefined JSON format.
	 * @param name name of waypoint or poi
	 * @param latitude latitude of waypoint or poi
	 * @param longitude longitude of waypoint or poi
	 * @param type type of poi
	 * @param description description of poi
	 * @param isFirstObject is first object of poi or waypoint
	 * @return string converted JSON in the form of a string
	 */
	string convertParamsToJson(string name, string latitude, string longitude,
			bool isFirstObject, string type = "", string description = "");

	/**
	 * Maps input string values from file to proper attribute variables.
	 * @param name name of waypoint or poi
	 * @param currentAttribute The name of the attribute to map value to.
	 * @param currentValue The value to be assigned
	 * @param type type of poi
	 * @param description description of poi
	 * @param lineNumber current number of line of read from JSON file
	 * @param inputChecker map used to checking if valid inputs are provided
	 * @return bool false if an error occurred
	 */
	bool mapValueToAppropriateStringAttribute(string &name, string & type,
			string & description, string currentAttribute, string currentValue,
			int lineNumber, map<string, bool> & inputChecker);

	/**
	 * Maps input number values from file to proper attribute variables.
	 * @param latitude latitude of waypoint or poi
	 * @param currentAttribute The name of the attribute to map value to.
	 * @param currentValue The value to be assigned
	 * @param longitude longitude of waypoint or poi
	 * @param lineNumber current number of line of read from JSON file
	 * @param inputChecker map used to checking if valid inputs are provided
	 * @return bool false if an error occurred
	 */
	bool mapValueToAppropriateNumberAttribute(double & latitude,
			double & longitude, string currentAttribute, double currentValue,
			int lineNumber, map<string, bool> & inputChecker);

	/**
	 * Saves the attributes to waypoint or POI database appropriately.
	 * @param name name of waypoint or poi
	 * @param latitude latitude of waypoint or poi
	 * @param longitude longitude of waypoint or poi
	 * @param type type of poi
	 * @param description description of poi
	 * @param lineNumber current number of line of read from JSON file
	 * @param inputChecker map used to checking if valid inputs are provided
	 * @param input_error denotes if an error had occurred during read
	 * @return bool false if an error occurred
	 */
	void saveAttributesToAppropriateDB(string name, double latitude,
			double longitude, string type, string description, string DBName,
			CWpDatabase& waypointDb, CPoiDatabase& poiDb, bool & input_error,
			int lineNumber, map<string, bool> & inputChecker);

	/**
	 * Initializes the input checker map used for validating inputs from the JSON file
	 * @param inputChecker map containing all attribute names as key and bool as value
	 * to denote if an error occurred for that attribute.
	 */
	void initializeInputChecker(map<string, bool> & inputChecker);
public:
	CJsonPersistence();
	virtual ~CJsonPersistence();
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
	bool writeData(const CWpDatabase& waypointDb, const CPoiDatabase& poiDb);

	/**
	 * Read data from storage into database
	 * @param waypointDb The Waypoint database
	 * @param poiDb The POI database
	 * @param mode of type MergeMode determines if database is to be cleared or data should be appended to it
	 * @return bool if the operation was successful or not
	 */
	bool readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb, MergeMode mode);
};

#endif /* CJSONPERSISTENCE_H_ */
