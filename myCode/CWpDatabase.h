/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        :
* Author          :
* Description     :
*
*
****************************************************************************/

#ifndef CWPDATABASE_H
#define CWPDATABASE_H
#include "CWaypoint.h"
#include <map>
#include<vector>
#include "CDatabase.h"
class CWpDatabase: public CDatabase<std::string, CWaypoint>
{
private:
	/**
	 * Map of Waypoints
	 */
//	std::map<std::string, CWaypoint> m_Waypoint;
public:
	/**
	 * Constructor
	 */
	CWpDatabase();

	/**
	 * This method will add a waypoint to the waypoint database.
	 * If a waypoint of same name is trying to be added, the
	 * it will not be added to the database.
	 * @param waypoint The CWaypoint instance that has to be added
	 * @return void
	 */
	void addWaypoint(CWaypoint const & wp);

	/**
	 * Adds multiple waypoints to the database
	 * @param allWayPoints A vector containing all waypoints to be added to database
	 */
    void addMultipleWayPoints(std::vector<CWaypoint> allWayPoints);

	/**
	 * This method will provide a pointer to a valid Waypoint that exists in the
	 * database based on the name of the Waypoint.
	 * @param name Name of the waypoint for which a pointer is to be returned.
	 * @return CWaypoint *, a valid pointer to the Waypoint if it exists in the database else NULL.
	 */
    CWaypoint* getPointerToWaypoint(std::string name);

	/**
	 * Prints all the waypoints in the database
	 */
    void print();

	/**
	 * Provides a vector of CWaypoint pointers for all waypoints in the database
	 * @param allWayPoints A vector to contain the reference to all waypoints in the database
	 */
    std::map<std::string, CWaypoint> getPointersToAllWaypoints() const;

	/**
	 * Clears the database
	 */
	void clearDatabase();
};
/********************
**  CLASS END
*********************/
#endif /* CWPDATABASE_H */
