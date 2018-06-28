/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CRoute.h
* Author          :	Nagarjun Anantha Padmanabha
* Description     :	Header file for the class CRoute. Contains only the
* 					class declaration.
*
*
****************************************************************************/

#ifndef CROUTE_H
#define CROUTE_H

/*Header files*/
#include<string>
#include<list>
#include <memory>
#include "CPOI.h"
#include "CWaypoint.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"

/**
 * CRoute class represents a geographical route with several waypoints and
 * points of interest.
 */
class CRoute
{
private:
	/**
	 * Pointer directing to the POI database
	 * @clientCardinality 0..*
	 * 
	 */
	CPoiDatabase* m_pPoiDatabase;
	/**
	 * Pointer directing to the waypoint database
	 * @clientCardinality 0..*
	 *
	 */
	CWpDatabase* m_pWpDatabase;
	/**
	 * A double linked list of CWaypoint pointer potentially pointing
	 * to CWaypoint or CPOI instances in the database.
	 * @link aggregation
	 * @clientCardinality 1
	 *
	 */
    std::list<CWaypoint *> m_path;
public:
	/**
	 * Constructor
	 */
	CRoute();

	/**
	 * Copy Constructor
	 * @param origin Original CRoute instance to be copied from.
	 */
	CRoute(CRoute const & origin);

	/**
	 * This method will connect the CRoute object to a POI database with a
	 * pointer to the database.
	 * @param pPoiDB A pointer to the database to connect to.
	 * @return void
	 */
	void connectToPoiDatabase(CPoiDatabase * pPoiDB);

	/**
	 * This method will add a pointer of a CWaypoint instance
	 * to the list of waypoints and POIs in the CRoute instance.
	 * If connection to the database does not exist, then returns without performing any tasks.
	 * @param name The name of the CWaypoint to be added to the CRoute instance.
	 * @return void
	 */
	void addWaypoint(std::string name);

	/**
	 * This method will add a pointer of a CPOI instance to the
	 * list of waypoints and POIs in the CRoute instance after
	 * the last of the specified waypoint. If specified waypoint does not exist,
	 * then the POI is added at the end.
	 * If connection to the database does not exist, then returns without performing any tasks.
	 * @param namePoi Name of the CPOI object that should be associated with the CRoute instance.
	 * @param name The name of the CWaypoint after which the POI is to be added to the CRoute instance.
	 * @return void
	 */
	void addPoi(std::string namePoi, std::string afterWp);

	/**
	 * This method will return the shortest distance between the given CWaypoint position and
	 * any of the POI's available for the route.
	 * @param wp Waypoint for which the distance has to be calculated.
	 * @param poi CPOI instance passed by reference through which the closest CPOI object data
	 *  is returned back
	 * @return double, distance in kilometers between the wp and closest CPOI object.
	 *  Returns -1 if no POIs are present in the route.
	 */
	double getDistanceNextPoi(CWaypoint const & wp, CPOI & poi);

	/**
	 * This method will print a CRoute with all its waypoints and points of interest.
	 * @return void
	 */
	void print();
	/**
	 * This method will connect the CRoute object to a waypoint database with a
	 * pointer to the database.
	 * @param pWpDB A pointer to the database to connect to.
	 * @return void
	 */
	void connectToWpDatabase(CWpDatabase* pWpDB);

    /**
     * Overloads the assignment operator for CRoute class
     * @param rhs The right hand side of assignment operator of type CRoute
     * @return CRoute& The reference to the new route
     */
	CRoute & operator = (CRoute const &rhs);
	/**
	 * Overloads the += operator for CRoute class. Adds a waypoint and/or POI
	 * to the route.
	 * @param rhs A string containing name of waypoint or POI to be added
	 * @return CRoute& The reference to the modified route
	 */
    CRoute & operator +=(string rhs);

	/**
	 * Overloads the + operator for CRoute class. Concatenates two routes if they
	 * connected to the same database.
	 * @param rhs A CRoute to be concatenated
	 * @return CRoute The resultant CRoute instance
	 */
    CRoute operator+ (CRoute const &rhs);

    const vector<const CWaypoint*> getRoute();

	/**
	 * Destructor
	 */
	~CRoute();
};
/********************
 **  CLASS END
 *********************/
#endif /* CROUTE_H */
