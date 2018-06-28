/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.h
 * Author          :	Nagarjun Anantha Padmanabha
 * Description     : Contains implementation of CPOI class.
 *
 *
 ****************************************************************************/

// System Headers
#include<iostream>
using namespace std;

// Own Headers
#include "CPOI.h"
#include "CRoute.h"

// Implementation
void CPOI::print(ostream& os) const
{
	string point_of_interest_type;
	switch (m_type)
	{
	case RESTAURANT:
		point_of_interest_type = "Restaurant";
		break;
	case TOURISTIC:
		point_of_interest_type = "Touristic";
		break;
	case GASSTATION:
		point_of_interest_type = "Gas Station";
		break;
	case UNIVERSITY:
		point_of_interest_type = "University";
		break;
	case NONE:
		point_of_interest_type = "Information not available";
		break;
	}
	os << "Point of Interest" << endl;
	os << "=================" << endl;
	os << "of type " << point_of_interest_type << " : " << m_description
			<< endl;
	CWaypoint::print(os, MMSS);
}

CPOI::CPOI(t_poi type, string name, string description, double latitude,
		double longitude) :
		CWaypoint(name, latitude, longitude)
{
	m_type = type;
	m_description = description;
}

void CPOI::getAllDataByReference(string& name, double & latitude,
		double & longitude, t_poi & type, string & description) const
{
	CWaypoint::getAllDataByReference(name, latitude, longitude);
	description = m_description;
	type = m_type;
}

ostream& operator<<(ostream& os, const CPOI& poi)
{
	poi.print(os);
	return os;
}
