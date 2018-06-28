// GIT-Labor
// main.h

////////////////////////////////////////////////////////////////////////////////
// Header-Dateien
#include <iostream>		// Header für die Standard-IO-Objekte (z.B. cout, cin)
#include <string>
using namespace std;
// Erspart den scope vor Objekte der
// C++-Standard-Bibliothek zu schreiben
// z.B. statt "std::cout" kann man "cout" schreiben

// Inkludieren Sie hier die Header-Files Ihrer Klassen, z.B.
#include "CWaypoint.h"
#include "CNavigationSystem.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CCSVPersistentStorage.h"
#include "CJsonPersistence.h"


void testPersistenceComponent();
// Hauptprogramm
// Dient als Testrahmen, von hier aus werden die Klassen aufgerufen
int main(void)
{
	CWaypoint amsterdam("Amsterdam", 52.3702, 4.8952);
	CWaypoint darmstadt("Darmstadt", 49.8728, 8.6512);
	CWaypoint berlin("Berlin", 52.5200, 13.405);
	CWaypoint tokyo("Tokyo", 35.6895, 139.6917);
	CWaypoint newWayPoint;

	cout << berlin;

	cout << "For CWaypoint object darmstadt-" << endl;
	cout << "Name as return value : " << darmstadt.getName() << endl;
	cout << "Latitude as return value : " << darmstadt.getLatitude() << " deg"
			<< endl;
	cout << "Longitude as return value : " << darmstadt.getLongitude() << " deg"
			<< endl;

	string name;
	double latitude, longitude;
	tokyo.getAllDataByReference(name, latitude, longitude);
#ifdef SHOWADDRESS
	cout << "Address of local variables in main" << endl;
	cout << " address of name: " << &name <<endl;
	cout << " address of latitude: " << &latitude <<endl;
	cout << " address of longitude: " << &longitude <<endl;
#endif

	cout << "Distance between Amsterdam and Berlin: "
			<< amsterdam.calculateDistance(berlin) << " Km" << endl;
	cout << "Distance between Berlin and Tokyo: "
			<< berlin.calculateDistance(tokyo) << " Km" << endl;

	cout << endl << "Navigation System" << endl << "==================="
			<< endl;
	CNavigationSystem navigationSystem;
	navigationSystem.run();
//	testPersistenceComponent();
	return 0;
}

void testPersistenceComponent()
{
	CPoiDatabase poiDB;
	CWpDatabase wpDB;
	cout << "Testing JSON Persistence Component" << endl;
	cout << "==============================" << endl;

	CJsonPersistence cj;
	cj.setMediaName("test_persistence_valid");

	cj.readData(wpDB, poiDB, CPersistentStorage::REPLACE);
	wpDB.print();
	poiDB.print();
	cj.setMediaName("test_persistence_write");
	cj.writeData(wpDB, poiDB);
}
