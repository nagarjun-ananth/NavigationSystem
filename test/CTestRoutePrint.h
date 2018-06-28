/*
 * CTestRoutePrint.h
 *
 *  Created on: Jan 18, 2018
 *      Author: arjun
 */

#ifndef TEST_CTESTROUTEPRINT_H_
#define TEST_CTESTROUTEPRINT_H_

#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <iostream>
#include "../myCode/CRoute.h"
#include "../myCode/CWpDatabase.h"
#include "../myCode/CPoiDatabase.h"
#include "../myCode/CJsonPersistence.h"


class CTestRoutePrint: public CppUnit::TestFixture
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
		m_route->connectToWpDatabase(m_wpDatabase);
		m_route->connectToPoiDatabase(m_poiDatabase);



	}
	void tearDown()
	{
		delete m_route;
		delete m_wpDatabase;
		delete m_poiDatabase;
	}
	void testRoutePrint()
	{
		std::ostringstream oss;
		std::streambuf* orig_buf(std::cout.rdbuf(oss.rdbuf()));
		m_route->addWaypoint("Amsterdam");
		m_route->addPoi("RWTH Aachen", "Amsterdam");
		m_route->print();
		std::cout.rdbuf(orig_buf);
		string expectedPrintOutput =
				"Printing the route\n==================\nAmsterdam on latitude = 52deg 22min 12.72s and longitude = 4deg 53min 42.72s\n\nPoint of Interest\n=================\nof type University : Good university\nRWTH Aachen on latitude = 50deg 46min 48.72s and longitude = 6deg 3min 57.276s\n\n";
		CPPUNIT_ASSERT(expectedPrintOutput == oss.str());
	}

	void testEmptyRoutePrint()
	{
		std::ostringstream oss;
		std::streambuf* orig_buf(std::cout.rdbuf(oss.rdbuf()));
		m_route->print();
		std::cout.rdbuf(orig_buf);
		CPPUNIT_ASSERT("Empty Route!!!\n" == oss.str());

	}

	static CppUnit::TestSuite* suite()
	{
		CppUnit::TestSuite* suite = new CppUnit::TestSuite("CRoute print tests");
		suite->addTest(
				new CppUnit::TestCaller<CTestRoutePrint>("Print route",
						&CTestRoutePrint::testRoutePrint));
		suite->addTest(
				new CppUnit::TestCaller<CTestRoutePrint>("Print empty route",
						&CTestRoutePrint::testEmptyRoutePrint));
		return suite;
	}
};

#endif /* TEST_CTESTROUTEPRINT_H_ */
