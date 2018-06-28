/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPoiDatabase.h
 * Author          :	Nagarjun Anantha Padmanabha
 * Description     : Implementation of the CPoiDatabase class.
 *
 *
 ****************************************************************************/

// System Headers
#include<iostream>
using namespace std;

// Own Headers
#include "CPoiDatabase.h"

// Implementation
CPoiDatabase::CPoiDatabase()
{
}

void CPoiDatabase::addPoi(const CPOI& poi)
{
	CDatabase::addLocation(poi);
}

CPOI* CPoiDatabase::getPointerToPoi(string name)
{
	CPOI* pPoiResult = NULL;
	pPoiResult = CDatabase::getPointerToLocation(name);
	return pPoiResult;
}

std::map<std::string, CPOI> CPoiDatabase::getPointersToAllPoi() const
{
	return CDatabase::getPointersToAllLocations();
}

void CPoiDatabase::addMultiplePoi(std::vector<CPOI> allPoi)
{
	CDatabase::addMultipleLocations(allPoi);
}

void CPoiDatabase::clearDatabase()
{
	CDatabase::clearDatabase();
}

void CPoiDatabase::print()
{
	CDatabase::print();
}
