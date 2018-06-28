/*
 * CTestAddPoi.h
 *
 *  Created on: Jan 18, 2018
 *      Author: arjun
 */

#ifndef TEST_CTESTADDPOI_H_
#define TEST_CTESTADDPOI_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <iostream>
#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CJsonPersistence.h"

class CTestAddPoi: public CppUnit::TestFixture
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
	/*Positive test case for addPoi*/
	void testAddPoi()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);

		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");

		m_route->addPoi("Sitte", "Amsterdam");

		const vector<const CWaypoint *> route = m_route->getRoute();
		CPPUNIT_ASSERT_EQUAL(3, (int )route.size());
		CPPUNIT_ASSERT("Amsterdam" == route[0]->getName());
		CPPUNIT_ASSERT("Sitte" == route[1]->getName());
		CPPUNIT_ASSERT("Darmstadt" == route[2]->getName());

	}

	/*Testing addPoi when the route is not connected to POI database*/
	void testAddPoiWithoutPoiDatabase()
	{
		std::ostringstream oss;
		std::streambuf* orig_buf(std::cout.rdbuf(oss.rdbuf()));
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");

		m_route->addPoi("Sitte", "Amsterdam");

		std::cout.rdbuf(orig_buf);
		CPPUNIT_ASSERT(oss.str() == "ERROR: POI Database not found\n");
	}

	/*Testing addPoi when the poi is present in the database*/
	void testAddPoiWithoutPoiInPool()
	{
		std::ostringstream oss;
		std::streambuf* orig_buf(std::cout.rdbuf(oss.rdbuf()));
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");

		m_route->addPoi("Frankenstein", "Amsterdam");

		std::cout.rdbuf(orig_buf);
		CPPUNIT_ASSERT(
				oss.str()
						== "ERROR: Could not find POI with name Frankenstein. Not in the pool.\n");
	}

	/*Testing addPoi when route is not connected to wp database*/
	void testAddPoiWithoutWpDatabase()
	{
		m_route->connectToPoiDatabase(m_poiDatabase);

		m_route->addPoi("Sitte", "Amsterdam");
		const vector<const CWaypoint *> route = m_route->getRoute();

		CPPUNIT_ASSERT_EQUAL(1, (int )route.size());
		CPPUNIT_ASSERT("Sitte" == route[0]->getName());

	}

	/*Testing addPoi when waypoint does not exist in the database*/
	void testAddPoiWithoutWpInDatabase()
	{
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");
		m_route->addPoi("Sitte", "Amsterdam");

		m_route->addPoi("RWTH Aachen", "Bengaluru");
		const vector<const CWaypoint *> route = m_route->getRoute();

		CPPUNIT_ASSERT_EQUAL(4, (int )route.size());
		CPPUNIT_ASSERT("RWTH Aachen" == route[3]->getName());
		CPPUNIT_ASSERT("Bengaluru" != route[2]->getName());
	}

	/*Testing addPoi when waypoint does not exist in the route*/
	void testAddPoiWithoutWpInRoute()
	{
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");
		m_route->addPoi("Sitte", "Amsterdam");

		m_route->addPoi("RWTH Aachen", "Berlin");
		const vector<const CWaypoint *> route = m_route->getRoute();

		CPPUNIT_ASSERT(m_wpDatabase->getPointerToWaypoint("Berlin"));
		CPPUNIT_ASSERT_EQUAL(4, (int )route.size());
		CPPUNIT_ASSERT("RWTH Aachen" == route[3]->getName());
		CPPUNIT_ASSERT("Berlin" != route[2]->getName());
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Add POI tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Positive test case for addPoi",
						&CTestAddPoi::testAddPoi));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Testing addPoi when the route is not connected to POI database",
						&CTestAddPoi::testAddPoiWithoutPoiDatabase));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Testing addPoi when the poi is present in the database",
						&CTestAddPoi::testAddPoiWithoutPoiInPool));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Testing addPoi when route is not connected to wp database",
						&CTestAddPoi::testAddPoiWithoutWpDatabase));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Testing addPoi when waypoint does not exist in the database",
						&CTestAddPoi::testAddPoiWithoutWpInDatabase));
		suite->addTest(
				new CppUnit::TestCaller<CTestAddPoi>(
						"Testing addPoi when waypoint does not exist in the route",
						&CTestAddPoi::testAddPoiWithoutWpInRoute));
		return suite;
	}
};
#endif /* TEST_CTESTADDPOI_H_ */
