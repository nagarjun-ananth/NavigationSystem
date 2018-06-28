/*
 * CDatabase.h
 *
 *  Created on: Jan 6, 2018
 *      Author: arjun
 */

#ifndef CDATABASE_H_
#define CDATABASE_H_

/*Header files*/
#include<string>
#include <map>
#include<vector>
#include<iostream>
using namespace std;
template<typename key, typename value>
class CDatabase
{
private:
	/**
	 * Map for given type of key and values. Acts as a template database.
	 */
	std::map<key, value> m_locations;
public:
	/**
	 * Constructor
	 */
	CDatabase()
	{
	}
	;

	/**
	 * This method will add a location to the location database.
	 * If a location of same name is trying to be added, the
	 * it will not be added to the database.
	 * @param location The location instance that has to be added
	 * @return void
	 */
	void addLocation(value const & location);

	/**
	 * This method will provide a pointer to a valid location that exists in the
	 * database based on the name of the location.
	 * @param name Name of the location for which a pointer is to be returned.
	 * @return location *, a valid pointer to the location if it exists in the database else NULL.
	 */
	value* getPointerToLocation(key name);
	/**
	 * Provides a map of location pointers for all location in the database
	 * @return std::map<key, value> A vector that contains the reference to all locations in the database
	 */
	std::map<key, value> getPointersToAllLocations() const;

	/**
	 * Adds multiple locations to the database
	 * @param allLocations A vector containing all waypoints to be added to database
	 */
	void addMultipleLocations(std::vector<value> allLocations);
	/**
	 * Clears the database
	 */
	void clearDatabase();
	/**
	 * Prints all the locations in the database
	 */
	void print();
};

template<typename key, typename value>
void CDatabase<key, value>::addLocation(value const & location)
{
	typename std::pair<typename std::map<key, value>::iterator, bool> ret;
	ret = m_locations.insert(
			std::pair<key, value>(location.getName(), location));

	if (ret.second == false)
	{
		cout << "ERROR: POI with name " << location.getName()
				<< " already exists in the database." << endl;
	}
}

template<typename key, typename value>
value* CDatabase<key, value>::getPointerToLocation(key name)
{
	value* pLocationResult = NULL;
	typename map<key, value>::iterator iterator;
	iterator = m_locations.find(name);
	if (iterator != m_locations.end())
	{
		pLocationResult = &(iterator->second);
	}
	return pLocationResult;
}

template<typename key, typename value>
std::map<key, value> CDatabase<key, value>::getPointersToAllLocations() const
{
	return m_locations;
}

template<typename key, typename value>
void CDatabase<key, value>::addMultipleLocations(
		std::vector<value> allLocations)
{
	typename std::pair<typename std::map<key, value>::iterator, bool> ret;
	typename vector<value>::const_iterator const_iterator;
	for (const_iterator = allLocations.begin();
			const_iterator != allLocations.end(); ++const_iterator)
	{
		ret = m_locations.insert(
				std::pair<key, value>((*const_iterator).getName(),
						(*const_iterator)));

		if (ret.second == false)
		{
			cout << "POI already exists";
		}
	}
}

template<typename key, typename value>
void CDatabase<key, value>::clearDatabase()
{
	m_locations.clear();
}

template<typename key, typename value>
void CDatabase<key, value>::print()
{
	typename map<key, value>::iterator iterator;
	cout << "Printing Database" << endl;
	cout << "=====================" << endl;
	for (iterator = m_locations.begin(); iterator != m_locations.end();
			iterator++)
	{
		cout << (iterator->second) << endl;
	}
}
#endif /* CDATABASE_H_ */
