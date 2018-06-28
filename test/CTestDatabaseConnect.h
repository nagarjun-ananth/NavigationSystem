/*
 * CTestWpDbConnect.h
 *
 *  Created on: Jan 17, 2018
 *      Author: arjun
 */

#ifndef TEST_CTESTDATABASECONNECT_H_
#define TEST_CTESTDATABASECONNECT_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <iostream>
#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CJsonPersistence.h"

class CTestDatabaseConnect: public CppUnit::TestFixture
{
private:
	CRoute * m_route;
	CWpDatabase * m_wpDatabase;
	CPoiDatabase * m_poiDatabase;
public:
	void setUp(){
		m_route = new CRoute();
		m_wpDatabase = new CWpDatabase();
		m_poiDatabase = new CPoiDatabase();
		CJsonPersistence cj;
		cj.setMediaName("test_persistence_valid");
		CPPUNIT_ASSERT(cj.readData(*m_wpDatabase, *m_poiDatabase, CPersistentStorage::REPLACE));

	}
	void tearDown()
	{
		delete m_route;
		delete m_wpDatabase;
		delete m_poiDatabase;
	}
	void testconnectToWpDatabase()
	{
		m_route->connectToWpDatabase(m_wpDatabase);

		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");
		const vector<const CWaypoint *> route = m_route->getRoute();
		CPPUNIT_ASSERT_EQUAL(2, (int)route.size());
	}
	void testconnectToPoiDatabase()
	{
		m_route->connectToPoiDatabase(m_poiDatabase);

		m_route->addPoi("RWTH Aachen","darmstadt");
		const vector<const CWaypoint *> route = m_route->getRoute();
		CPPUNIT_ASSERT_EQUAL(1, (int )route.size());
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("Connect to database tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestDatabaseConnect>("Connect route to WP database",
						&CTestDatabaseConnect::testconnectToWpDatabase));
		suite->addTest(
				new CppUnit::TestCaller<CTestDatabaseConnect>("Connect route to POI database",
						&CTestDatabaseConnect::testconnectToPoiDatabase));
		return suite;
	}
};
#endif /* TEST_CTESTDATABASECONNECT_H_ */
