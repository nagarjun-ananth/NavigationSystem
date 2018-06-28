/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CRoute.h
 * Author          :	Nagarjun Anantha Padmanabha
 * Description     : Implementation of the CRoute class.
 *
 *
 ****************************************************************************/

// System Headers
#include<iostream>

using namespace std;

// Own Headers
#include "CRoute.h"
#include "CPoiDatabase.h"
#include "CWpDatabase.h"
#include "CPOI.h"

// Implementation

CRoute::CRoute()
{
	m_pPoiDatabase = NULL;
	m_pWpDatabase = NULL;
}

void CRoute::connectToPoiDatabase(CPoiDatabase* pPoiDB)
{
	m_pPoiDatabase = pPoiDB;
}

void CRoute::addWaypoint(string name)
{
	/*Check if connection to database is established*/
	if (!m_pWpDatabase)
	{
		cout << "ERROR:WP database not found" << endl;
		return;
	}

	CWaypoint * pWaypoint = m_pWpDatabase->getPointerToWaypoint(name);
	/*Check if waypoint exists in the database*/
	if (pWaypoint)
	{
		m_path.push_back(pWaypoint);
	}
	else
	{
		cout << "ERROR: Could not find the Waypoint with name " << name
				<< ". Not in the pool." << endl;
	}
}

double CRoute::getDistanceNextPoi(const CWaypoint& wp, CPOI& poi)
{
	double minDistance = -1;
	CWaypoint * nextPoi;

	/*Check if route is empty*/
	if (m_path.size() == 0)
	{
		return minDistance;
	}

	list<CWaypoint *>::iterator iterator;
	double distance;
	for (iterator = m_path.begin()++; iterator != m_path.end(); iterator++)
	{
		if (dynamic_cast<CPOI *>(*iterator))
		{
			distance = (**iterator).calculateDistance(wp);
			if (minDistance == -1 || distance < minDistance)
			{
				minDistance = distance;
				nextPoi = *iterator;
			}
		}
	}
	if (minDistance != -1)
	{
		poi = *(dynamic_cast<CPOI *>(nextPoi));
	}
	return minDistance;
}

CRoute::CRoute(const CRoute& origin)
{
	m_pPoiDatabase = origin.m_pPoiDatabase;
	m_pWpDatabase = origin.m_pWpDatabase;
	m_path = origin.m_path;
}

CRoute& CRoute::operator =(const CRoute& rhs)
{
	m_pPoiDatabase = rhs.m_pPoiDatabase;
	m_pWpDatabase = rhs.m_pWpDatabase;
	m_path = rhs.m_path;
	return *this;
}

CRoute& CRoute::operator +=(string rhs)
{
	this->addWaypoint(rhs);
	this->addPoi(rhs, rhs);
	return *this;
}

CRoute CRoute::operator+(const CRoute& rhs)
{
	CRoute resultantRoute;
	if (!(this->m_pWpDatabase == rhs.m_pWpDatabase
			&& this->m_pPoiDatabase == rhs.m_pPoiDatabase))
	{
		cout
				<< "Cannot concatenate the two routes. The routes do not share the same databases."
				<< endl;
	}
	else
	{
		resultantRoute.m_path = this->m_path;
		resultantRoute.m_path.insert(resultantRoute.m_path.end(),
				rhs.m_path.begin(), rhs.m_path.end());
	}
	return resultantRoute;
}

CRoute::~CRoute()
{
	m_pPoiDatabase = NULL;
	m_pWpDatabase = NULL;
}

void CRoute::addPoi(string namePoi, string afterWp)
{
	/*Check if connection to database is established*/
	if (!m_pPoiDatabase)
	{
		cout << "ERROR: POI Database not found" << endl;
		return;
	}

	CPOI * pPoi = m_pPoiDatabase->getPointerToPoi(namePoi);
	CWaypoint * pWaypoint = NULL;
	if (m_pWpDatabase)
	{
		pWaypoint = m_pWpDatabase->getPointerToWaypoint(afterWp);
	}

	/*Check if POI exists in the database*/
	if (!pPoi)
	{
		cout << "ERROR: Could not find POI with name " << namePoi
				<< ". Not in the pool." << endl;
		return;
	}
	/*Check if such a waypoint exists in the database*/
	if (pPoi && !pWaypoint)
	{
		m_path.push_back(pPoi);
		return;
	}
	bool wpFoundInRoute = false;
	list<CWaypoint *>::reverse_iterator reverse_iterator;
	for (reverse_iterator = m_path.rbegin(); reverse_iterator != m_path.rend();
			reverse_iterator++)
	{
		if ((*reverse_iterator) == pWaypoint)
		{
			m_path.insert(reverse_iterator.base(), pPoi);
			wpFoundInRoute = true;
			break;
		}
	}
	if (!wpFoundInRoute)
	{
		m_path.push_back(pPoi);
	}
}

void CRoute::print()
{
	if (m_path.size() == 0)
	{
		cout << "Empty Route!!!" << endl;
		return;
	}
	cout << "Printing the route" << endl;
	cout << "==================" << endl;
	list<CWaypoint *>::iterator iterator;
	for (iterator = m_path.begin(); iterator != m_path.end(); iterator++)
	{
		CPOI* poi = dynamic_cast<CPOI*>(*iterator);
		if (poi)
		{
			cout << *(poi) << endl;
		}
		else
		{
			cout << (**iterator) << endl;
		}
	}
	/**
	 * When naïve approach with the overloaded operators was used for printing,
	 * the waypoints would print properly but not the POIs. Reason being that,
	 * since even POIs are stored using pointers of type CWaypoint, the compiler
	 * does not recognize a POI as a POI when the << operator is used. Instead it
	 * assumes the data to be a Waypoint and hence calls the overloaded <<
	 * operator of CWaypoint and not of CPOI.
	 */
}
void CRoute::connectToWpDatabase(CWpDatabase* pWpDB)
{
	m_pWpDatabase = pWpDB;
}

const vector<const CWaypoint*> CRoute::getRoute()
{
	list<CWaypoint *>::iterator iterator;
	vector<const CWaypoint *> route;
	for (iterator = m_path.begin(); iterator != m_path.end();
			iterator++)
	{
		route.push_back(*iterator);
	}

	return route;
}
