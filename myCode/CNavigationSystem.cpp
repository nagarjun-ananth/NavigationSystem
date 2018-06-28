/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CNavigationSystem.h
 * Author          : Nagarjun Anantha Padmanabha
 * Description     :	Implementation of the CNavigationSystem class.
 * 					Route, Database and GPS sensor are instantiated and used
 * 					here.
 *
 *
 ****************************************************************************/

// System Headers
#include <string>
#include<iostream>

using namespace std;

// Own Headers
#include "CNavigationSystem.h"
#include "CCSVPersistentStorage.h"
#include"CPOI.h"

// Implementation

CNavigationSystem::CNavigationSystem()
{
	/*Connect the route instance to the POI database instance*/
	m_route.connectToPoiDatabase(&m_PoiDatabase);
	m_route.connectToWpDatabase(&m_WpDatabase);

	/*Uncomment code to test database not found exception*/
//	m_route.connectToPoiDatabase(NULL);
//	m_route.connectToWpDatabase(NULL);
}

void CNavigationSystem::enterRoute()
{
	//add waypoints to the route
	m_route.addWaypoint("Amsterdam");
	m_route.addWaypoint("Berlin");
	m_route.addWaypoint("Darmstadt");
	m_route.addWaypoint("Berlin");

	/*Uncomment below code to test Waypoint not in the pool exception*/
//	m_route.addWaypoint("Bengaluru");
	/* Add points of interest to the route.
	 * Comment the below lines to test No POIs found in the route exception
	 */
	m_route.addPoi("Mensa HDA", "Amsterdam");
	m_route.addPoi("Sitte", "Berlin");
	m_route.addPoi("RWTH Aachen", "Darmstadt");

	/*Uncomment below code to test POI not in the pool exception*/
//	m_route.addPoi("CTR Dosa Center", "Berlin");
}

void CNavigationSystem::printRoute()
{
	m_route.print();
}

void CNavigationSystem::printDistanceCurPosNextPoi()
{
	double minDistance;
	CPOI nextPOI;
	CWaypoint currentPosition = m_GPSSensor.getCurrentPosition();
	minDistance = m_route.getDistanceNextPoi(currentPosition, nextPOI);
	if (minDistance == -1)
	{
		cout << "No points of interest present in the route!!" << endl;
	}
	else
	{
		cout << "Distance to next POI = " << minDistance << " Km" << endl;
		cout << nextPOI << endl;
	}
}



void CNavigationSystem::run()
{
	CCSVPersistentStorage navigationSystemStorage;
	navigationSystemStorage.setMediaName("navigationSystem");
	//Read from file to database
	navigationSystemStorage.readData(m_WpDatabase, m_PoiDatabase,
			CPersistentStorage::REPLACE);

	enterRoute();
	printRoute();
	printDistanceCurPosNextPoi();

	//write database to files
	navigationSystemStorage.writeData(m_WpDatabase, m_PoiDatabase);


	//test cases for overloaded operators
//	testCrouteCopyConstructor();
//	testCRouteOverloadedAssignmentOperator();
//	testCRouteOverloadedAdditionAssignmentOperator();
//	testCRouteOverloadedAdditionOperator();
}

void CNavigationSystem::testCrouteCopyConstructor()
{
	cout << "============Test for CRoute Copy Constructor============="<< endl;
	CRoute copyOfRoute(m_route);
	//Alter the new route to test deep copy of copy constructor
	copyOfRoute.addPoi("Sitte", "Amsterdam");
	cout << "ORIGINAL ROUTE: " << endl << "================="<<endl;
	printRoute();
	cout << "DEEP COPY OF ROUTE"<< endl << "=================" << endl;
	copyOfRoute.print();
}

void CNavigationSystem::testCRouteOverloadedAssignmentOperator()
{
	cout << "============Test for CRoute Assignment operator============="<< endl;
	CRoute copyOfRoute;
	copyOfRoute = m_route;
	//Alter the new route to test deep copy of overloaded assignment operator
	copyOfRoute.addPoi("Sitte", "Amsterdam");
	cout << "ORIGINAL ROUTE: " << endl << "================="<<endl;
	printRoute();
	cout << "DEEP COPY OF ROUTE BY ASSIGNMENT"<< endl << "=================" << endl;
	copyOfRoute.print();
}

void CNavigationSystem::testCRouteOverloadedAdditionAssignmentOperator()
{
	cout << "============Test for CRoute Addition assignment operator============="<< endl;
	cout << "Case when the given name matches both waypoint and POI" << endl;
	m_route += "Heidelberg University";
	printRoute();
	cout << "Case when the given name matches only the waypoint" << endl;
	m_route += "Tokyo";
	printRoute();
	cout << "Case when the given name matches only the POI" << endl;
	m_route += "Nandi Hills";
	printRoute();
}

void CNavigationSystem::testCRouteOverloadedAdditionOperator()
{
	cout << "============Test for CRoute addition operator============="<< endl;
	cout << "Case when two routes are successfully concatenated" << endl;
	CRoute firstRoute;
	firstRoute.connectToPoiDatabase(&m_PoiDatabase);
	firstRoute.connectToWpDatabase(&m_WpDatabase);
	firstRoute.addWaypoint("Tokyo");
	CRoute concatRoute = m_route + firstRoute;
	concatRoute.print();

	cout << "Case when two routes are connected to different databases" << endl;
	CRoute secondRoute;
	CPoiDatabase newPoiDatabase;
	secondRoute.connectToPoiDatabase(&newPoiDatabase);
	secondRoute.connectToWpDatabase(&m_WpDatabase);
	secondRoute.addWaypoint("Tokyo");
	CRoute concatRoute2 = m_route + secondRoute;
	concatRoute2.print();
}
