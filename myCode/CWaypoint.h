/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CWaypoint.h
* Author          : Nagarjun Anantha Padmanabha
* Description     : Contains the declaration for the class CWaypoint along
* 					with few MACROS as constants needed for the Navigation
* 					system and display address of interested entities.
*
*
****************************************************************************/

#ifndef CWAYPOINT_H
#define CWAYPOINT_H

/**
 * Used as verbose for printing certain addresses in the program.
 */
//#define SHOWADDRESS
/*Header files*/
#include<string>
#include <iostream>
/**
 * Used to differentiate CWaypoint printing methods for coordinates
 * of a position. It is better to put it in this header file, as these
 * values will be needed by the child class (CPOI) for printing.
 */
#define DEGREE 1
#define MMSS 2

#define EARTH_RADIUS  6378.17 //Earth's radius in Kilometers

/**
 * CWaypoint class represents a location on a map with name and
 * positional values.
 */
class CWaypoint
{
private:
	/**
	 * Name of the Waypoint.
	 */
	std::string m_name;

	/**
	 * Latitude coordinate of the waypoint.
	 */
	double m_latitude;

	/**
	 * Longitude coordinate of the waypoint.
	 */
	double m_longitude;

public:
	/**
	 * Constructor
	 * @param name Name of the Waypoint, default "Not Positioned"
	 * @param latitude Latitude coordinate of the CWaypoint, default 0,  range -90..90
	 * @param longitude Longitude coordinate of the CWaypoint, default 0, range -180..180
	 */
	CWaypoint(std::string name = "Not Positioned", double latitude = 0,
			double longitude = 0);

	/**
	 * This method will set the given values for a CWaypoint instance
	 * @param name Name of the Waypoint
	 * @param latitude Latitude coordinate position of CWaypoint, default  0, range -90..90
	 * @param longitude Longitude coordinate position of CWaypoint, default  0, range -180..180
	 * @return void
	 */
	void set(std::string name, double latitude, double longitude);

	/**
	 * This method will provide the name of the CWaypoint instance.
	 * @return string, name of the CWaypoint
	 */
	std::string getName() const;

	/**
	 * This method will provide the latitude value of the CWaypoint instance.
	 * @return double, Latitude value of the CWaypoint
	 */
	double getLatitude();

	/**
	 * This method will provide the longitude value of the CWaypoint instance.
	 * @return double, Longitude value of the CWaypoint
	 */
	double getLongitude();

	/**
	 * This method will provide all the data related to a waypoint using call by reference.
	 * @param name, Name of the waypoint will be copied into this variable.
	 * @param latitude, Latitude of the waypoint will be copied into this variable.
	 * @param longitude, Longitude of the waypoint will be copied into this variable.
	 * @return void
	 */
	void getAllDataByReference(std::string & name, double & latitude,
			double & longitude) const;

	/**
	 * This method will calculate the distance between two CWaypoints.
	 * @param wp Waypoint to which the distance has to be calculated.
	 * @return double, distance in kilometers between the wp and waypoint instance invoking the method.
	 */
	double calculateDistance(const CWaypoint & wp);

	/**
	 * This method will print to the specified output stream the details of a
	 * waypoint in Decimal or DEG MM SS format.
	 * @param os the output stream to be printed to.
	 * @param format, specifies if the waypoint details should be printed in Decimal
	 * or DEG MM SS format. format requires values DEGREE or MMSS defined MACROS.
	 * @return void
	 */
	void print(std::ostream& os, int format) const;

	/**
	 * Overloads the insertion operator for the CWaypoint class.
	 * @param os The stream to be output to.
	 * @param wp the waypoint that is using the overloaded operator.
	 */
	friend std::ostream& operator<<(std::ostream& os, const CWaypoint& wp);

	virtual ~CWaypoint();

private:

	/**
	 * This method will transform the decimal waypoint longitude value into DEG MM SS format.
	 * @param deg, used as a container for the degree value
	 * @param mm, used as a container for minutes value
	 * @param ss, used as a container for seconds value
	 * @return void
	 */
	void transformLongitude2degmmss(int & deg, int & mm, double & ss) const;

	/**
	 * This method will transform the decimal waypoint latitude value into DEG MM SS format.
	 * @param deg,  used as a container for degree value
	 * @param mm, used as a container for minutes value
	 * @param ss, used as a container for seconds value
	 * @return void
	 */
	void transformLatitude2degmmss(int & deg, int & mm, double & ss) const;
};
/********************
 **  CLASS END
 *********************/
#endif /* CWAYPOINT_H */
