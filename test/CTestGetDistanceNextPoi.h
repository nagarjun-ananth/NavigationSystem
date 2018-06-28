/*
 * testGetDistanceNextPoi.h
 *
 *  Created on: Jan 18, 2018
 *      Author: arjun
 */

#ifndef TEST_TESTGETDISTANCENEXTPOI_H_
#define TEST_TESTGETDISTANCENEXTPOI_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <iostream>
#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CJsonPersistence.h"

class CTestGetDistanceNextPoi: public CppUnit::TestFixture
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
	void testGetDistanceNextPoi()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->addPoi("Sitte", "darmstadt");
		m_route->addPoi("Mathildenhöhe", "darmstadt");
		m_route->addPoi("RWTH Aachen", "darmstadt");
		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");

		const CWaypoint* wp = m_wpDatabase->getPointerToWaypoint("Amsterdam");
		CPOI poi;
		double d = m_route->getDistanceNextPoi(*wp, poi);
		CPPUNIT_ASSERT_EQUAL(194.64360100751136, d);
		CPPUNIT_ASSERT("RWTH Aachen" == poi.getName());
	}
	void testGetDistanceNextPoiWithEmptyRoute()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);
		const CWaypoint* wp = m_wpDatabase->getPointerToWaypoint("Amsterdam");
		CPOI poi;
		double d = m_route->getDistanceNextPoi(*wp, poi);
		CPPUNIT_ASSERT(-1 == d);
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Get distance tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestGetDistanceNextPoi>(
						"Get distance to the next poi",
						&CTestGetDistanceNextPoi::testGetDistanceNextPoi));
		suite->addTest(
				new CppUnit::TestCaller<CTestGetDistanceNextPoi>(
						"Get distance to the next poi with empty route",
						&CTestGetDistanceNextPoi::testGetDistanceNextPoiWithEmptyRoute));
		return suite;
	}
};

#endif /* TEST_TESTGETDISTANCENEXTPOI_H_ */
