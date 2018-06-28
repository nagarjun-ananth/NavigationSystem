/*
 * CTestAddWaypoint.h
 *
 *  Created on: Jan 17, 2018
 *      Author: arjun
 */

#ifndef TEST_CTESTADDWAYPOINT_H_
#define TEST_CTESTADDWAYPOINT_H_

#include <sstream>
#include <iostream>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CJsonPersistence.h"

class CTestAddWaypoint: public CppUnit::TestFixture
{
private:
	CRoute * m_route;
	CWpDatabase * m_wpDatabase;
	CPoiDatabase * m_poiDatabase;
public:
	void setUp()
	{
		m_route = new CRoute();
		m_wpDatabase = new CWpDatabase();
		m_poiDatabase = new CPoiDatabase();
		CJsonPersistence cj;
		cj.setMediaName("test_persistence_valid");
		CPPUNIT_ASSERT(
				cj.readData(*m_wpDatabase, *m_poiDatabase,
						CPersistentStorage::REPLACE));

	}
	void tearDown()
	{
		delete m_route;
		delete m_wpDatabase;
		delete m_poiDatabase;
	}
	void testAddwaypoint()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->addWaypoint("Amsterdam");
		const vector<const CWaypoint *> route = m_route->getRoute();
		CPPUNIT_ASSERT_EQUAL(1, (int )route.size());
		CPPUNIT_ASSERT("Amsterdam" == route[0]->getName());
	}
	void testAddwaypointWithoutDatabaseConnected()
	{
		std::ostringstream oss;
		std::streambuf* orig_buf(std::cout.rdbuf(oss.rdbuf()));
		m_route->addWaypoint("Amsterdam");
		std::cout.rdbuf(orig_buf);
		CPPUNIT_ASSERT(oss.str() == "ERROR:WP database not found\n");
	}

	void testAddwaypointNotFoundInDatabase()
	{
		std::ostringstream oss;
		std::streambuf* orig_buf(std::cout.rdbuf(oss.rdbuf()));
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->addWaypoint("bengaluru");
		std::cout.rdbuf(orig_buf);
		CPPUNIT_ASSERT(
				oss.str()
						== "ERROR: Could not find the Waypoint with name bengaluru. Not in the pool.\n");
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Add waypoint tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestAddWaypoint>(
						"Add waypoint to a route",
						&CTestAddWaypoint::testAddwaypoint));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddWaypoint>(
						"Add waypoint to a route when not connected to database",
						&CTestAddWaypoint::testAddwaypointWithoutDatabaseConnected));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddWaypoint>(
						"Add waypoint to a route when waypoint is not added to database",
						&CTestAddWaypoint::testAddwaypointNotFoundInDatabase));
		return suite;
	}
};

#endif /* TEST_CTESTADDWAYPOINT_H_ */

