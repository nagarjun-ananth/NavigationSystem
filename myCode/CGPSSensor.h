/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CGPSSensor.h
* Author          :	Nagarjun Anantha Padmanabha
* Description     : Contains only declaration for class CGPSSensor.
*
*
****************************************************************************/

#ifndef CGPSSENSOR_H
#define CGPSSENSOR_H

/*Header files*/
#include "CWaypoint.h"

/**
 * The CGPSSensor class represents a GPS sensor and simulates
 * its ability to get the current position.
 */
class CGPSSensor {
public:
	/**
	 * Constructor
	*/
	CGPSSensor();

	/**
	 * This method will provide information of the current location of GPS.
	 * @return CWaypoint, an instance of CWaypoint with current latitudinal and longitudinal positions.
	 */
    CWaypoint getCurrentPosition();

};
/********************
**  CLASS END
*********************/
#endif /* CGPSSENSOR_H */
