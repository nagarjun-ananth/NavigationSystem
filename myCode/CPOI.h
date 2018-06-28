/***************************************************************************
 *============= Copyright by Darmstadt University of Applied Sciences =======
 ****************************************************************************
 * Filename        : CPOI.h
 * Author          : Nagarjun Anantha Padmanabha
 * Description     : Contains the class declaration for CPOI and also the
 * 					 enum declaration t_poi for the type of POI.
 *
 *
 ****************************************************************************/

#ifndef CPOI_H
#define CPOI_H

/*Header files*/
#include <string>
#include "CWaypoint.h"
class CRoute;

/**
 * Enum declaration t_poi. Consists of four values,
 * RESTAURANT = 0
 * TOURISTIC = 1
 * GASSTATION = 2
 * UNIVERSITY = 3
 * NONE = 4
 * Used for classifying a CPOI based on type.
 */
enum t_poi
{
	RESTAURANT, TOURISTIC, GASSTATION, UNIVERSITY, NONE
};

/**
 * The CPOI class represents a point of interest on a map.
 * Provides information about it such as name, description
 * along with location details. Inherits class CWaypoint.
 */
class CPOI: public CWaypoint
{
private:
	/**
	 * The type of POI. One of the t_poi Enum values.
	 * @link aggregationByValue
	 * @clientCardinality 1
	 * @supplierCardinality 1
	 */
	t_poi m_type;

	/**
	 * The description about point of interest.
	 */
	std::string m_description;
public:
	/**
	 * Constructor
	 * @param t_poi Type of the POI, default NONE
	 * @param name Name of the POI, default "Not Positioned"
	 * @param description Description of the POI, default "No description"
	 * @param latitude Latitude coordinate of the POI, default 0, range -90..90
	 * @param longitude Longitude coordinate of the POI, default 0, range -180..180
	 */
	CPOI(t_poi type = NONE, std::string name = "Not Positioned",
			std::string description = "No description", double latitude = 0,
			double longitude = 0);

	/**
	 * This method will print the type and description of a POI along with
	 * its name and positional information to the given outstream.
	 * @return void
	 */
	void print(std::ostream& os) const;

	/**
	 * This method will provide all the data related to a POI through call by reference.
	 * @param name Name of the POI will be copied into this variable.
	 * @param latitude Latitude of the POI will be copied into this variable.
	 * @param longitude Longitude of the POI will be copied into this variable.
	 * @param type Type of the POI will be copied into this variable.
	 * @param description Description of the POI will be copied into this variable.
	 * @return void
	 */
	void getAllDataByReference(std::string& name, double & latitude,
			double & longitude, t_poi & type, std::string & description) const;

	/**
	 * Overloads the insertion operator for the class
	 * @param os the output stream used for overloading
	 * @param poi the poi instance that is using the overloaded operator
	 * @return ostream& the reference to the ostream that was during for overloading
	 */
	friend std::ostream& operator <<(std::ostream& os, const CPOI& poi);

};
/********************
 **  CLASS END
 *********************/
#endif /* CPOI_H */
