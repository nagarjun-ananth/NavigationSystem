/*
 * CTestRouteAdditiveAssignmentOperator.h
 *
 *  Created on: Jan 18, 2018
 *      Author: arjun
 */

#ifndef TEST_CTESTROUTEADDITIVEASSIGNMENTOPERATOR_H_
#define TEST_CTESTROUTEADDITIVEASSIGNMENTOPERATOR_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <iostream>
#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CJsonPersistence.h"

class CTestRouteAdditiveAssignmentOperator: public CppUnit::TestFixture
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
	void testCRouteAdditiveAssignmentOperator()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->addWaypoint("Amsterdam");

		*m_route += "Tokyo";

		const vector<const CWaypoint *> originalRoute = m_route->getRoute();
		CPPUNIT_ASSERT("Tokyo" == originalRoute[originalRoute.size()-2]->getName());
		CPPUNIT_ASSERT("Tokyo" == originalRoute[originalRoute.size()-1]->getName());
		const CWaypoint * pWp = originalRoute[originalRoute.size()-2];
		const CPOI* poi = dynamic_cast<const CPOI*>(pWp);
		CPPUNIT_ASSERT(!poi);
		pWp = originalRoute[originalRoute.size()-1];
		poi = dynamic_cast<const CPOI*>(pWp);
		CPPUNIT_ASSERT(poi);
	}
	void testCRouteAdditiveAssignmentOperatorWithoutWaypoint()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->addWaypoint("Amsterdam");

		*m_route += "RWTH Aachen";

		const vector<const CWaypoint *> originalRoute = m_route->getRoute();
		CPPUNIT_ASSERT(
				"RWTH Aachen"
						== originalRoute[originalRoute.size() - 1]->getName());
		const CWaypoint * pWp = originalRoute[originalRoute.size() - 1];
		const CPOI* poi = dynamic_cast<const CPOI*>(pWp);
		CPPUNIT_ASSERT(poi);
		CPPUNIT_ASSERT(
						"RWTH Aachen"
								!= originalRoute[originalRoute.size() - 2]->getName());
	}
	void testCRouteAdditiveAssignmentOperatorWithoutPoi()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->addWaypoint("Amsterdam");

		*m_route += "Darmstadt";

		const vector<const CWaypoint *> originalRoute = m_route->getRoute();
		CPPUNIT_ASSERT(
				"Darmstadt"
						== originalRoute[originalRoute.size() - 1]->getName());
		const CWaypoint * pWp = originalRoute[originalRoute.size() - 1];
		const CPOI* poi = dynamic_cast<const CPOI*>(pWp);
		CPPUNIT_ASSERT(!poi);
	}
	void testCRouteAdditiveAssignmentOperatorWithoutPoiWithoutWaypoint()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->addWaypoint("Amsterdam");

		*m_route += "Hildesheim";

		const vector<const CWaypoint *> originalRoute = m_route->getRoute();
		CPPUNIT_ASSERT_EQUAL(1,(int)originalRoute.size());
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite(
				"CRoute += overloaded operator tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestRouteAdditiveAssignmentOperator>(
						"positive test for += operator of CRoute",
						&CTestRouteAdditiveAssignmentOperator::testCRouteAdditiveAssignmentOperator));
		suite->addTest(
				new CppUnit::TestCaller<CTestRouteAdditiveAssignmentOperator>(
						"+= operator of CRoute finds only POI",
						&CTestRouteAdditiveAssignmentOperator::testCRouteAdditiveAssignmentOperatorWithoutWaypoint));
		suite->addTest(
				new CppUnit::TestCaller<CTestRouteAdditiveAssignmentOperator>(
						"+= operator of CRoute finds only waypoint",
						&CTestRouteAdditiveAssignmentOperator::testCRouteAdditiveAssignmentOperatorWithoutPoi));
		suite->addTest(
				new CppUnit::TestCaller<CTestRouteAdditiveAssignmentOperator>(
						"+= operator of CRoute finds neither POI nor waypoint",
						&CTestRouteAdditiveAssignmentOperator::testCRouteAdditiveAssignmentOperatorWithoutPoiWithoutWaypoint));
		return suite;
	}
};

#endif /* TEST_CTESTROUTEADDITIVEASSIGNMENTOPERATOR_H_ */
