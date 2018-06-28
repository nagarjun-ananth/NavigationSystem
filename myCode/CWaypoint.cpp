/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CWaypoint.cpp
 * Author          : Nagarjun Anantha Padmanabha
 * Description     : Contains the implementation for CWaypoint class.
 *
 *
 ****************************************************************************/

// System Headers
#define _USE_MATH_DEFINES	//Need this for definition of M_PI
#include<iostream>
#include<math.h>
using namespace std;

// Own Headers
#include "CWaypoint.h"

//Implementation

CWaypoint::CWaypoint(string name, double latitude, double longitude)
{
	set(name, latitude, longitude);
#ifdef SHOWADDRESS
	cout << "Object created at" << this << endl;
	cout << "Name :" << this->m_name << " Address: " << &(this->m_name) << endl;
	cout << "Latitude :" << this->m_latitude << " Address: "
	<< &(this->m_latitude) << endl;
	cout << "Longitude :" << this->m_longitude << " Address: "
	<< &(this->m_longitude) << endl;
#endif

	/**
	 * ON MY MACHINE:
	 * The size of variables with 'double' as data type (latitude and longitude) each take up 8bytes of memory.
	 * For the string name, the string class itself takes up 32 bytes of memory irrespective of the size of the string data
	 * that is being stored. However the size of the string data being stored can be obtained using the size method
	 * or length method of the string class. Example, std::string::size() which would give a result of length of
	 * the string. An object of string class would need 32 bytes of memory, it however contains a pointer to the heap memory
	 * where the the actual string data may be stored.
	 */
}

void CWaypoint::set(string name, double latitude, double longitude)
{
	m_latitude = m_longitude = 0;
	if (latitude <= 90 && latitude >= -90 && longitude <= 180 && longitude >= -180)
	{
		m_latitude = latitude;
		m_longitude = longitude;
	}
	m_name = name;
}

void CWaypoint::transformLongitude2degmmss(int& deg, int& mm, double& ss) const
{
	double longitude = abs(m_longitude);
	deg = int(longitude);
	mm = int((longitude - deg) * 60);
	ss = ((longitude - deg) * 60 - mm) * 60;
	if (m_longitude < 0)
	{
		deg *= (-1);
	}
}

string CWaypoint::getName() const
{
	return m_name;
}
double CWaypoint::getLatitude()
{
	return m_latitude;
}
double CWaypoint::getLongitude()
{
	return m_longitude;
}
void CWaypoint::getAllDataByReference(string & name, double & latitude,
		double & longitude) const
{
	name = m_name;
	latitude = m_latitude;
	longitude = m_longitude;
#ifdef SHOWADDRESS
	cout << "Parameter addresses in getAllDataByReference" << endl;
	cout << " address of name: " << &name << endl;
	cout << " address of latitude: " << &latitude << endl;
	cout << " address of longitude: " << &longitude << endl;
#endif
	/**
	 * The addresses of local variables in the main file and the addresses of the corresponding parameters in
	 * this function, when compared, are the same. The reason for this being that we pass the local variables by
	 * reference. Hence only a reference for those variables is received in the function and not a copy of the
	 * variables. Any operation performed on the function parameters operates on the same address as the local variables
	 * in the main file.
	 */
}

void CWaypoint::transformLatitude2degmmss(int & deg, int & mm,
		double & ss) const
{
	double latitude = abs(m_latitude);
	deg = int(latitude);
	mm = int((latitude - deg) * 60);
	ss = ((latitude - deg) * 60 - mm) * 60;
	if (m_latitude < 0)
	{
		deg *= (-1);
	}
}
void CWaypoint::print(ostream& os, int format) const
{
	switch (format)
	{
	case DEGREE:
		os << m_name << " on latitude = " << m_latitude << " and longitude = "
				<< m_longitude << endl;
		break;
	case MMSS:
		int deg, mm;
		double ss;
		transformLatitude2degmmss(deg, mm, ss);
		os << m_name << " on latitude = " << deg << "deg " << mm << "min " << ss
				<< "s";
		transformLongitude2degmmss(deg, mm, ss);
		os << " and longitude = " << deg << "deg " << mm << "min " << ss << "s"
				<< endl;
		break;
	default:
		os << "ERROR:Invalid print option selected";
		break;
	}
}

double CWaypoint::calculateDistance(const CWaypoint & wp)
{
	double distance = 0;
	double const degToRad = M_PI / 180;
	distance = EARTH_RADIUS
			* acos(
					sin(m_latitude * degToRad) * sin(wp.m_latitude * degToRad)
							+ cos(m_latitude * degToRad)
									* cos(wp.m_latitude * degToRad)
									* cos(
											(wp.m_longitude - m_longitude)
													* degToRad));
	return distance;
}

ostream& operator<<(ostream& os, const CWaypoint& wp)
{
	wp.print(os, MMSS);
	return os;
}

CWaypoint::~CWaypoint()
{
}
