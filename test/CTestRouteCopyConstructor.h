/*
 * CTestRouteCopyConstructor.h
 *
 *  Created on: Jan 18, 2018
 *      Author: arjun
 */

#ifndef TEST_CTESTROUTECOPYCONSTRUCTOR_H_
#define TEST_CTESTROUTECOPYCONSTRUCTOR_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <iostream>
#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CJsonPersistence.h"

class CTestRouteCopyConstructor: public CppUnit::TestFixture
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
	void testCRouteCopyConstructor()
	{
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);
		m_route->addWaypoint("Amsterdam");

		CRoute newRoute(*m_route);
		const vector<const CWaypoint *> originalRoute = m_route->getRoute();
		const vector<const CWaypoint *> copyRoute = newRoute.getRoute();
		CPPUNIT_ASSERT_EQUAL((int)originalRoute.size(), (int)copyRoute.size());
		CPPUNIT_ASSERT(originalRoute[0]->getName() == copyRoute[0]->getName());
	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("CRoute copy constructor");
		suite->addTest(
				new CppUnit::TestCaller<CTestRouteCopyConstructor>("Positive test for copy constructor of CRoute",
						&CTestRouteCopyConstructor::testCRouteCopyConstructor));
		return suite;
	}
};

#endif /* TEST_CTESTROUTECOPYCONSTRUCTOR_H_ */
