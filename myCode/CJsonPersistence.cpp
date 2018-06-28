/*
 * CJsonPersistence.cpp
 *
 *  Created on: Jan 6, 2018
 *      Author: arjun
 */

#include <iostream>
#include <fstream>
#include<vector>
#include <sstream>
#include <algorithm>
#include "CJsonScanner.h"
#include "CJsonToken.h"
#include "InvalidCharacterException.h"

#include "CJsonPersistence.h"

CJsonPersistence::CJsonPersistence()
{
	m_mediaName = "";
}

CJsonPersistence::~CJsonPersistence()
{
}

void CJsonPersistence::setMediaName(std::string name)
{
	m_mediaName = name;
}

bool CJsonPersistence::writeData(const CWpDatabase& waypointDb,
		const CPoiDatabase& poiDb)
{
	fstream fileStream;
	const string fileName = m_mediaName + ".json";
	std::map<std::string, CWaypoint> allWayPoints;
	string name, description;
	t_poi type;
	double latitude, longitude;

	/*open file to write to*/
	fileStream.open(fileName.c_str(), fstream::out);
	if (fileStream.fail())
	{
		cout << "ERROR: Could not open file " + fileName + " for writing."
				<< endl;
		return false;
	}
	allWayPoints = waypointDb.getPointersToAllWaypoints(); //get all wp the data from the database
	/*Write data to file*/
	fileStream << "{\n\t\"waypoints\": [\n";
	map<string, CWaypoint>::iterator iterator;
	for (iterator = allWayPoints.begin(); iterator != allWayPoints.end();
			iterator++)
	{
		(iterator->second).getAllDataByReference(name, latitude, longitude);
		fileStream
				<< convertParamsToJson(name, convertDoubleToString(latitude),
						convertDoubleToString(longitude),
						iterator == allWayPoints.begin());
	}
	fileStream << "\n\t],\n";

	map<string, CPOI> allCpoi;
	string PoiTypeStrings[5]; //Array used like a map to access POI type as string
	PoiTypeStrings[RESTAURANT] = "RESTAURANT";
	PoiTypeStrings[TOURISTIC] = "SIGHTSEEING";
	PoiTypeStrings[GASSTATION] = "GASSTATION";
	PoiTypeStrings[UNIVERSITY] = "UNIVERSITY";
	PoiTypeStrings[NONE] = "NO_INFORMATION";

	allCpoi = poiDb.getPointersToAllPoi(); //read data from POI database

	/*Write data to file*/
	fileStream << "\t\"pois\": [\n";
	map<string, CPOI>::iterator poiIterator;
	for (poiIterator = allCpoi.begin(); poiIterator != allCpoi.end();
			poiIterator++)
	{
		(poiIterator->second).getAllDataByReference(name, latitude, longitude,
				type, description);
		fileStream
				<< convertParamsToJson(name, convertDoubleToString(latitude),
						convertDoubleToString(longitude),
						poiIterator == allCpoi.begin(), PoiTypeStrings[type],
						description);
	}

	fileStream << "\n\t]\n}";
	fileStream.close(); //close file

	return true;
}

bool CJsonPersistence::readData(CWpDatabase& waypointDb, CPoiDatabase& poiDb,
		MergeMode mode)
{
	fstream fileStream;
	const string fileName = m_mediaName + ".json";
	/*open file to read from*/
	fileStream.open(fileName.c_str(), fstream::in);
	if (fileStream.fail())
	{
		cout << "ERROR: Could not open file " + fileName + " for reading."
				<< endl;
		return false;
	}

	/*States representing the state machine used for parsing the JSON data*/
	enum states
	{
		WAITING_FOR_FIRST_TOKEN,
		WAITING_FOR_DB_NAME,
		WAITING_FOR_DB_BEGIN,
		WAITING_FOR_NAME_SEPARATOR,
		WAITING_FOR_ATTRIBUTE_NAME,
		WAITING_FOR_VALUE_SEPARATOR,
		WAITING_FOR_ATTRIBUTE_VALUE,
		WAITING_FOR_OBJECT_BEGIN,
		WAITING_FOR_DB_END
	};

	if (mode == REPLACE)
	{
		waypointDb.clearDatabase();
		poiDb.clearDatabase();
	}

	/*Holds bool values for all attributes of a waypoint or POI
	 *Denotes false if attribute not found or wrong attribute found */
	std::map<string, bool> inputChecker;
	initializeInputChecker(inputChecker);

	APT::CJsonScanner scannerobj = APT::CJsonScanner(fileStream);
	bool DBopened = false;	//Used to check if a DB is being used to write data to
	string DBName = ""; //Name of the DB to which data is to be written
	string currentAttribute = ""; //Name of the current attribute for which the data is being read from the file
	states currentState = WAITING_FOR_FIRST_TOKEN; //Maintains the current state of the state machine
	string name, type, description; //variables used for storing all attributes of a waypoint or a poi
	double latitude, longitude;
	bool input_error = false;	//Used to indicate if there was an input error
	APT::CJsonToken* tokenptr;
	while (1)
	{
		try
		{
			tokenptr = scannerobj.nextToken();
		} catch (InvalidCharacterException &exception)
		{
			/*Invalid character found in the input*/
			cout << exception.what() << endl;
			input_error = true;
			continue;
		}
		/*Input exhausted*/
		if (!tokenptr)
		{
			break;
		}
		APT::CJsonToken token = *(tokenptr);
		APT::CJsonToken::TokenType tokenType = token.getType();
		switch (currentState)
		{
		case WAITING_FOR_FIRST_TOKEN:
			if (tokenType != APT::CJsonToken::BEGIN_OBJECT)
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			currentState = WAITING_FOR_DB_NAME;
			break;
		case WAITING_FOR_DB_NAME:
			if (tokenType == APT::CJsonToken::STRING)
			{
				APT::CJsonStringToken stringToken =
						*(dynamic_cast<APT::CJsonStringToken*>(tokenptr));
				DBName = stringToken.getValue();
				if (!(DBName == "waypoints" || DBName == "pois"))
				{
					cout << "Invalid names for database in line: "
							<< scannerobj.scannedLine()
							<< " . This format is not accepted" << endl;
					return false;
				}
				currentState = WAITING_FOR_NAME_SEPARATOR;
			}
			else if (tokenType != APT::CJsonToken::END_OBJECT)
			{}
			else
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			break;
		case WAITING_FOR_NAME_SEPARATOR:
			if (tokenType == APT::CJsonToken::NAME_SEPARATOR)
			{
				currentState =
						DBopened ?
								WAITING_FOR_ATTRIBUTE_VALUE :
								WAITING_FOR_DB_BEGIN;
			}
			else
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			break;
		case WAITING_FOR_DB_BEGIN:
			if (tokenType == APT::CJsonToken::BEGIN_ARRAY)
			{
				currentState = WAITING_FOR_OBJECT_BEGIN;
				DBopened = true;
			}
			else
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			break;
		case WAITING_FOR_OBJECT_BEGIN:
			if (tokenType == APT::CJsonToken::BEGIN_OBJECT)
			{
				currentState = WAITING_FOR_ATTRIBUTE_NAME;
			}
			else if (tokenType == APT::CJsonToken::END_ARRAY)
			{
				DBName = "";
				DBopened = false;
				currentState = WAITING_FOR_VALUE_SEPARATOR;
			}
			else
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			break;
		case WAITING_FOR_ATTRIBUTE_NAME:
			if (tokenType == APT::CJsonToken::STRING)
			{
				APT::CJsonStringToken stringToken =
						*(dynamic_cast<APT::CJsonStringToken*>(tokenptr));
				currentAttribute = stringToken.getValue();
				currentState = WAITING_FOR_NAME_SEPARATOR;
			}
			else
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			break;
		case WAITING_FOR_ATTRIBUTE_VALUE:
			if (tokenType == APT::CJsonToken::STRING)
			{
				APT::CJsonStringToken stringToken =
						*(dynamic_cast<APT::CJsonStringToken*>(tokenptr));
				string currentValue = stringToken.getValue();
				if (!input_error)
				{
					input_error = !(mapValueToAppropriateStringAttribute(name,
							type, description, currentAttribute, currentValue,
							scannerobj.scannedLine(), inputChecker));
				}
			}
			else if (tokenType == APT::CJsonToken::NUMBER)
			{
				APT::CJsonNumberToken numberToken =
						*(dynamic_cast<APT::CJsonNumberToken*>(tokenptr));
				double currentValue = numberToken.getValue();
				if (!input_error)
				{
					input_error = !(mapValueToAppropriateNumberAttribute(
							latitude, longitude, currentAttribute, currentValue,
							scannerobj.scannedLine(), inputChecker));
				}
			}
			else
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			currentState = WAITING_FOR_VALUE_SEPARATOR;
			break;
		case WAITING_FOR_VALUE_SEPARATOR:
			if (!DBopened)
			{
				currentState = WAITING_FOR_DB_NAME;
			}
			else if (tokenType == APT::CJsonToken::VALUE_SEPARATOR)
			{
				currentState = WAITING_FOR_ATTRIBUTE_NAME;
			}
			else if (tokenType == APT::CJsonToken::END_OBJECT)
			{
				saveAttributesToAppropriateDB(name, latitude, longitude, type,
						description, DBName, waypointDb, poiDb, input_error,
						scannerobj.scannedLine(), inputChecker);
				currentAttribute = name = description = type = "";
				latitude = longitude = 0;
				currentState = WAITING_FOR_DB_END;
			}
			else
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			break;
		case WAITING_FOR_DB_END:
			if (tokenType == APT::CJsonToken::END_ARRAY)
			{
				DBName = "";
				DBopened = false;
				currentState = WAITING_FOR_VALUE_SEPARATOR;
			}
			else if (tokenType == APT::CJsonToken::VALUE_SEPARATOR)
			{
				currentState = WAITING_FOR_OBJECT_BEGIN;
			}
			else
			{
				cout << "Invalid JSON format in line "
						<< scannerobj.scannedLine() << endl;
				return false;
			}
			break;
		}

	}
	return true;
}

string CJsonPersistence::convertDoubleToString(double doubleValue)
{
	stringstream doubleInStream;
	doubleInStream << doubleValue;
	return doubleInStream.str();
}

string CJsonPersistence::convertParamsToJson(string name, string latitude,
		string longitude, bool isFirstObject, string type, string description)
{
	string jsonString = isFirstObject ? "\t\t{\n\t\t\t" : ",\n\t\t{\n\t\t\t";
	jsonString += "\"name\": \"" + name + "\",";
	jsonString += "\n\t\t\t\"latitude\": " + latitude + ",";
	jsonString += "\n\t\t\t\"longitude\": " + longitude;
	if (!type.empty())
	{
		jsonString += ",\n\t\t\t\"type\": \"" + type + "\",";
		jsonString += "\n\t\t\t\"description\": \"" + description + "\"";
	}
	jsonString += "\n\t\t}";
	return jsonString;

}

bool CJsonPersistence::mapValueToAppropriateStringAttribute(string& name,
		string& type, string& description, string currentAttribute,
		string currentValue, int lineNumber, map<string, bool> & inputChecker)
{
	if (currentAttribute == "name")
	{
		name = currentValue;
		inputChecker[currentAttribute] = true;
	}
	else if (currentAttribute == "description")
	{
		description = currentValue;
		inputChecker[currentAttribute] = true;
	}
	else if (currentAttribute == "type")
	{
		type = currentValue;
		inputChecker[currentAttribute] = true;
	}
	else
	{
		cout << "Invalid input in line " << lineNumber << endl;
		return false;
	}
	return true;
}

bool CJsonPersistence::mapValueToAppropriateNumberAttribute(double& latitude,
		double& longitude, string currentAttribute, double currentValue,
		int lineNumber, map<string, bool> & inputChecker)
{
	if (currentAttribute == "latitude")
	{
		latitude = currentValue;
		inputChecker[currentAttribute] = true;
	}
	else if (currentAttribute == "longitude")
	{
		longitude = currentValue;
		inputChecker[currentAttribute] = true;
	}
	else
	{
		cout << "Invalid input in line " << lineNumber << endl;
		return false;
	}
	return true;
}

void CJsonPersistence::saveAttributesToAppropriateDB(string name,
		double latitude, double longitude, string type, string description,
		string DBName, CWpDatabase& waypointDb, CPoiDatabase& poiDb,
		bool & input_error, int lineNumber, map<string, bool> & inputChecker)
{
	if (input_error)
	{
		input_error = false;
		initializeInputChecker(inputChecker);
		return;
	}
	if (DBName == "waypoints")
	{
		if (inputChecker["name"] && inputChecker["latitude"]
				&& inputChecker["longitude"])
		{
			waypointDb.addWaypoint(CWaypoint(name, latitude, longitude));
		}
		else
		{
			cout
					<< "Invalid number of attributes for waypoint or illegal attributes names for waypoint in line "
					<< lineNumber << endl;
		}
		initializeInputChecker(inputChecker);
	}
	else if (DBName == "pois")
	{
		if (!(inputChecker["name"] && inputChecker["latitude"]
				&& inputChecker["longitude"] && inputChecker["type"]
				&& inputChecker["description"]))
		{
			cout
					<< "Invalid number of attributes for POI or illegal attributes names for POI in line "
					<< lineNumber << endl;
			initializeInputChecker(inputChecker);
			return;
		}
		initializeInputChecker(inputChecker);
		map<string, t_poi> PoiTypeMap; //map used to fetch t_poi values for corresponding string
		PoiTypeMap.insert(pair<string, t_poi>("RESTAURANT", RESTAURANT));
		PoiTypeMap.insert(pair<string, t_poi>("SIGHTSEEING", TOURISTIC));
		PoiTypeMap.insert(pair<string, t_poi>("GASSTATION", GASSTATION));
		PoiTypeMap.insert(pair<string, t_poi>("UNIVERSITY", UNIVERSITY));
		PoiTypeMap.insert(pair<string, t_poi>("NO_INFORMATION", NONE));

		if (PoiTypeMap.find(type) == PoiTypeMap.end())
		{
			cout << "Invalid type for POI in line : " << lineNumber << endl;
			return;
		}
		poiDb.addPoi(
				CPOI(PoiTypeMap[type], name, description, latitude, longitude));
	}
}

void CJsonPersistence::initializeInputChecker(map<string, bool> & inputChecker)
{
	inputChecker["name"] = false;
	inputChecker["latitude"] = false;
	inputChecker["longitude"] = false;
	inputChecker["type"] = false;
	inputChecker["description"] = false;
}
