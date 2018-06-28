/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CNavigationSystem.h
 * Author          : Nagarjun Anantha Padmanabha
 * Description     : Header file for NavigationSystem class. Contains only
 * 					 the class declaration.
 *
 *
 ****************************************************************************/

#ifndef CNAVIGATIONSYSTEM_H
#define CNAVIGATIONSYSTEM_H

/*Header files*/
#include "CGPSSensor.h"
#include "CRoute.h"
#include "CPoiDatabase.h"

/**
 * The Navigation System class represents a system that consists of a GPS
 * sensor, a Route with waypoints and points of interests and a points of
 * interest Database. It can provide the closest POI to the current
 * location with distance and other POI related details.
 */
class CNavigationSystem
{
private:
	/**
	 * The GPS Sensor
	 * @link aggregationByValue
	 * @clientCardinality 1
	 * @supplierCardinality 1
	 */
	CGPSSensor m_GPSSensor;

	/**
	 * A route for navigation.
	 * @link aggregationByValue
	 * @clientCardinality 1
	 * @supplierCardinality 1
	 */
	CRoute m_route;

	/**
	 * A database of several points of interests.
	 * @link aggregationByValue
	 * @supplierCardinality 1
	 * @clientCardinality 1
	 */
	CPoiDatabase m_PoiDatabase;
	/**
	 * A database of several waypoints.
	 * @link aggregationByValue
	 * @clientCardinality 1
	 * @supplierCardinality 1
	 */
	CWpDatabase m_WpDatabase;

public:

	/**
	 * Constructor
	 */
	CNavigationSystem();

private:
	/**
	 * This method will print the distance between the current position to
	 * the closest point of interest along with the POI details.
	 *
	 * @return void
	 */
	void printDistanceCurPosNextPoi();

	/**
	 * This method will print the entire route with all the waypoints and
	 * points of interest.
	 *
	 * @return void
	 */
	void printRoute();

	/**
	 * This method will allow to create a route/trip with waypoints and
	 * points of interest.
	 *
	 * @return void
	 */
	void enterRoute();

	/**
	 * Test for copy constructor of CRoute
	 */
	void testCrouteCopyConstructor();

	/**
	 * Test for the overloaded assignment operator of CRoute
	 */
	void testCRouteOverloadedAssignmentOperator();

	/**
	 * Test for the overloaded addition assignment operator of CRoute
	 */
	void testCRouteOverloadedAdditionAssignmentOperator();

	/**
	 * Test for overloaded addition operator of CRoute
	 */
	void testCRouteOverloadedAdditionOperator();

public:


	/**
	 * This method will contain calls to a set of methods that need to be
	 * invoked for functioning of navigation system.
	 *
	 * @return void
	 */
	void run();

};
/********************
 **  CLASS END
 *********************/
#endif /* CNAVIGATIONSYSTEM_H */
