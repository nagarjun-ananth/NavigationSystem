/*
 * CNavigationSystemPersistentStorage.cpp
 *
 *  Created on: Dec 1, 2017
 *      Author: arjun
 */

//System headers
#include "CCSVPersistentStorage.h"

#include <iostream>
#include <fstream>
#include<vector>
#include <sstream>
#include <algorithm>

//Own headers
#include"CWaypoint.h"
#include "CPOI.h"

using namespace std;

CCSVPersistentStorage::CCSVPersistentStorage()
{
}

CCSVPersistentStorage::~CCSVPersistentStorage()
{
}

void CCSVPersistentStorage::setMediaName(std::string name)
{
	m_mediaName = name;
}

bool CCSVPersistentStorage::writeData(const CWpDatabase& waypointDb,
		const CPoiDatabase& poiDb)
{
	fstream fileStream;
	const string wpFileName = m_mediaName + "-wp.txt";
	const string poiFileName = m_mediaName + "-poi.txt";
	std::map<std::string, CWaypoint> allWayPoints;
	string name, description;
	t_poi type;
	double latitude, longitude;

	/*Write WP to the WpDataBase*/

	/*open file*/
	fileStream.open(wpFileName.c_str(), fstream::out);
	if (fileStream.fail())
	{
		cout << "ERROR: Could not open file " + wpFileName + " for writing."
				<< endl;
		return false;
	}

	allWayPoints =  waypointDb.getPointersToAllWaypoints(); //get all the data from the database

	/*Write data to file*/
	map<string, CWaypoint>::iterator iterator;
	for (iterator = allWayPoints.begin();
			iterator != allWayPoints.end(); iterator++)
	{
		stringstream latitudeStream, longitudeStream;
		(iterator->second).getAllDataByReference(name, latitude, longitude);
		latitudeStream << latitude;	//Convert coordinates to string
		longitudeStream << longitude;
		string lineToWrite = name + "," + latitudeStream.str() + ","
				+ longitudeStream.str();
		fileStream << lineToWrite << endl;
	}

	fileStream.close(); //close file

	/*Write to POI file*/

	/*open file*/
	fileStream.open(poiFileName.c_str(), fstream::out);
	if (fileStream.fail())
	{
		cout << "ERROR: Could not open file " + poiFileName + " for writing."
				<< endl;
		return false;
	}

	map<string, CPOI> allCpoi;
	string PoiTypeStrings[5];//Array used like a map to access POI type as string
	PoiTypeStrings[RESTAURANT] = "RESTAURANT";
	PoiTypeStrings[TOURISTIC] = "SIGHTSEEING";
	PoiTypeStrings[GASSTATION] = "GASSTATION";
	PoiTypeStrings[UNIVERSITY] = "UNIVERSITY";
	PoiTypeStrings[NONE] = "NO_INFORMATION";

	allCpoi = poiDb.getPointersToAllPoi(); //read data from POI database

	/*Write data to file*/
	map<string, CPOI>::iterator poiIterator;
	for (poiIterator = allCpoi.begin();
			poiIterator != allCpoi.end(); poiIterator++)
	{
		stringstream latitudeStream, longitudeStream;
		(poiIterator->second).getAllDataByReference(name, latitude, longitude,
				type, description);
		latitudeStream << latitude;	//Convert coordinates to string
		longitudeStream << longitude;
		string lineToWrite = PoiTypeStrings[type] + "," + name + ","
				+ description + "," + latitudeStream.str() + ","
				+ longitudeStream.str();
		fileStream << lineToWrite << endl;
	}

	fileStream.close(); //close file
	return true;
}

bool CCSVPersistentStorage::readData(CWpDatabase& waypointDb,
		CPoiDatabase& poiDb, MergeMode mode)
{
	if (mode == REPLACE)
	{
		waypointDb.clearDatabase();
		poiDb.clearDatabase();
	}

	fstream fileStream;
	string inputLine;
	const string wpFileName = m_mediaName + "-wp.txt";
	const string poiFileName = m_mediaName + "-poi.txt";
	vector<CWaypoint> allWayPoints;
	int lineCount = 0;

	cout << "Reading Waypoint file" << endl;
	cout << "=====================" << endl;
	/*Open Waypoint CSV file*/
	fileStream.open(wpFileName.c_str(), fstream::in);
	if (fileStream.fail())
	{
		cout << "ERROR: Could not open file " + wpFileName + " for reading."
				<< endl;
		return false;
	}

	/*Read data from Waypoint CSV file*/
	while (getline(fileStream, inputLine))
	{
		stringstream inputStream(inputLine);
		string item, name;
		double latitude, longitude;
		vector<string> tokens;
		char delimiter = getDelimiter(inputLine);
		lineCount++;
		while (getline(inputStream, item, delimiter))
		{
			tokens.push_back(item);
		}
		if (tokens.size() != 3)
		{
			if (tokens.size() < 3)
				displayError("Too few fields", lineCount, inputLine);
			else
				displayError("Too many fields", lineCount, inputLine);
			continue;
		}
		name = tokens[0];
		if (!cleanAndValidateGeographicCoordinates(tokens[1], tokens[2],
				latitude, longitude))
		{
			displayError("Invalid latitude or longitude values", lineCount,
					inputLine);
			continue;
		}
		allWayPoints.push_back(CWaypoint(name, latitude, longitude));
	}
	waypointDb.addMultipleWayPoints(allWayPoints); //write to database
	fileStream.close();	//Close file

	cout << "Reading POI file" << endl;
	cout << "================" << endl;
	/*open POI CSV file*/
	fileStream.open(poiFileName.c_str(), fstream::in);
	if (fileStream.fail())
	{
		cout << "ERROR: Could not open file " + poiFileName + " for reading."
				<< endl;
		return false;
	}
	vector<CPOI> allPoi;
	map<string, t_poi> PoiTypeMap;//map used to fetch t_poi values for corresponding string
	PoiTypeMap.insert(pair<string, t_poi>("RESTAURANT", RESTAURANT));
	PoiTypeMap.insert(pair<string, t_poi>("SIGHTSEEING", TOURISTIC));
	PoiTypeMap.insert(pair<string, t_poi>("GASSTATION", GASSTATION));
	PoiTypeMap.insert(pair<string, t_poi>("UNIVERSITY", UNIVERSITY));
	PoiTypeMap.insert(pair<string, t_poi>("NO_INFORMATION", NONE));
	lineCount = 0;

	//Read data from POI CSV file
	while (getline(fileStream, inputLine))
	{
		stringstream input_stream(inputLine);
		string item, name, description;
		t_poi type;
		double latitude, longitude;

		vector<string> tokens;
		lineCount++;
		char delimiter = getDelimiter(inputLine);
		while (getline(input_stream, item, delimiter))
		{
			tokens.push_back(item);
		}
		if (tokens.size() != 5)
		{
			if (tokens.size() < 5)
				displayError("Too few fields", lineCount, inputLine);
			else
				displayError("Too many fields", lineCount, inputLine);
			continue;
		}

		if (PoiTypeMap.find(tokens[0]) == PoiTypeMap.end())
		{
			displayError("Invalid type for POI", lineCount, inputLine);
			continue;
		}
		type = PoiTypeMap[tokens[0]];
		name = tokens[1];
		description = tokens[2];
		if (!cleanAndValidateGeographicCoordinates(tokens[3], tokens[4],
				latitude, longitude))
		{
			displayError("Invalid latitude or longitude values", lineCount,
					inputLine);
			continue;
		}
		allPoi.push_back(CPOI(type, name, description, latitude, longitude));
	}
	poiDb.addMultiplePoi(allPoi);	//write all POI to database
	fileStream.close();
	return true;
}

char CCSVPersistentStorage::getDelimiter(string inputLine)
{
	if (inputLine.find(";") < inputLine.find(","))
	{
		return ';';
	}
	return ',';
}

bool CCSVPersistentStorage::cleanAndValidateGeographicCoordinates(
		string latitude_str, string longitude_str, double &latitude,
		double &longitude)
{
	/*Remove any trailing spaces in latitude and longitude string from file
	 * The insertion operator next takes care of the leading spaces*/
	latitude_str = latitude_str.substr(0,
			latitude_str.find_last_not_of(" ") + 1);
	longitude_str = longitude_str.substr(0,
			longitude_str.find_last_not_of(" ") + 1);
	stringstream latitude_stream(latitude_str);
	stringstream longitude_stream(longitude_str);
	latitude_stream >> latitude;
	longitude_stream >> longitude;

	/*If !eof, then the data from file was not a number*/
	if (!latitude_stream.eof() || !longitude_stream.eof())
	{
		return false;
	}
	return true;
}

void CCSVPersistentStorage::displayError(string problem, int lineNumber,
		string lineContent)
{
	cout << "ERROR: " + problem + " in line " << lineNumber
			<< " : " + lineContent << endl;
}

