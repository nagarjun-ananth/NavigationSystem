/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************/

// System Headers
#include <string>
#include <iostream>
using namespace std;

// Own Headers
#include "CWpDatabase.h"
#include "CWaypoint.h"

// Implementation
CWpDatabase::CWpDatabase()
{
}
void CWpDatabase::addWaypoint(CWaypoint const & wp)
{
	CDatabase::addLocation(wp);
}
CWaypoint* CWpDatabase::getPointerToWaypoint(string name)
{
	CWaypoint* pWaypointResult = NULL;
	pWaypointResult = CDatabase::getPointerToLocation(name);
	return pWaypointResult;
}
void CWpDatabase::print()
{
	CDatabase::print();
}

std::map<std::string, CWaypoint> CWpDatabase::getPointersToAllWaypoints() const
{
	return CDatabase::getPointersToAllLocations();
}

void CWpDatabase::addMultipleWayPoints(std::vector<CWaypoint> allWayPoints)
{
	CDatabase::addMultipleLocations(allWayPoints);
}

void CWpDatabase::clearDatabase()
{
	CDatabase::clearDatabase();
}
