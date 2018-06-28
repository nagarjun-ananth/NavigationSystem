/*
 * CTestRoutePlusOperator.h
 *
 *  Created on: Jan 18, 2018
 *      Author: arjun
 */

#ifndef TEST_CTESTROUTEPLUSOPERATOR_H_
#define TEST_CTESTROUTEPLUSOPERATOR_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <iostream>
#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CJsonPersistence.h"

class CTestRoutePlusOperator: public CppUnit::TestFixture
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
	void testOverloadedPlusOperator()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);

		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");
		m_route->addPoi("RWTH Aachen","darmstadt");

		CRoute newRoute, resultantRoute;
		newRoute.connectToWpDatabase(m_wpDatabase);
		newRoute.connectToPoiDatabase(m_poiDatabase);
		newRoute.addWaypoint("Berlin");

		resultantRoute = *m_route + newRoute;
		CPPUNIT_ASSERT_EQUAL(4, (int)resultantRoute.getRoute().size());
		CPPUNIT_ASSERT("Amsterdam" == resultantRoute.getRoute()[0]->getName());
		CPPUNIT_ASSERT("Berlin" == resultantRoute.getRoute()[3]->getName());


	}

	void testOverloadedPlusOperatorDifferentDatabases()
	{
		std::ostringstream oss;
				std::streambuf* orig_buf(std::cout.rdbuf(oss.rdbuf()));
		CWpDatabase wpDatabase;
		CPoiDatabase poiDatabase;
		wpDatabase.addWaypoint(CWaypoint("Berlin", 30,40));
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);

		m_route->addWaypoint("Amsterdam");
		m_route->addWaypoint("Darmstadt");
		m_route->addPoi("RWTH Aachen", "darmstadt");

		CRoute newRoute, resultantRoute;
		newRoute.connectToWpDatabase(&wpDatabase);
		newRoute.connectToPoiDatabase(&poiDatabase);
		newRoute.addWaypoint("Berlin");

		resultantRoute = *m_route + newRoute;
		std::cout.rdbuf(orig_buf);
		CPPUNIT_ASSERT(
				oss.str()
						== "Cannot concatenate the two routes. The routes do not share the same databases.\n");
		CPPUNIT_ASSERT_EQUAL(0,(int)resultantRoute.getRoute().size());

	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("CRoute + overloaded operator tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestRoutePlusOperator>("Add two routes connected to same database",
						&CTestRoutePlusOperator::testOverloadedPlusOperator));
		suite->addTest(
				new CppUnit::TestCaller<CTestRoutePlusOperator>("Add two routes connected to different databases",
						&CTestRoutePlusOperator::testOverloadedPlusOperatorDifferentDatabases));
		return suite;
	}
};
#endif /* TEST_CTESTROUTEPLUSOPERATOR_H_ */
