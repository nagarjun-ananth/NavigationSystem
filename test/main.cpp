/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : main.cpp
 * Author          :	Nagarjun Anantha Padmanabha
 * Description     : Main function for unit test configuration
 *
 *
 ****************************************************************************/
#include <cppunit/TestCase.h>
#include <cppunit/TestSuite.h>
#include <cppunit/ui/text/TestRunner.h>
#include <iostream>
#include "CTestDatabaseConnect.h"
#include "CTestAddWaypoint.h"
#include "CTestGetDistanceNextPoi.h"
#include "CTestRouteCopyConstructor.h"
#include "CTestRouteAssignmentOperator.h"
#include "CTestRouteAdditiveAssignmentOperator.h"
#include "CTestRoutePlusOperator.h"
#include "CTestRoutePrint.h"
#include "CTestAddPoi.h"
using namespace std;
int main()
{
	cout << "hello world";
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(CTestDatabaseConnect::suite());
	runner.addTest(CTestAddWaypoint::suite());
	runner.addTest(CTestGetDistanceNextPoi::suite());
	runner.addTest(CTestRouteCopyConstructor::suite());
	runner.addTest(CTestRouteAssignmentOperator::suite());
	runner.addTest(CTestRouteAdditiveAssignmentOperator::suite());
	runner.addTest(CTestRoutePlusOperator::suite());
	runner.addTest(CTestRoutePrint::suite());
	runner.addTest(CTestAddPoi::suite());
	runner.run();
	return 0;
}


