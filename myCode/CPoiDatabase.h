/***************************************************************************
*============= Copyright by Darmstadt University of Applied Sciences =======
****************************************************************************
* Filename        : CPoiDatabase.h
* Author          :	Nagarjun Anantha Padmanabha
* Description     :	Header file for CPoiDatabase class. Contains only the
* 					class declaration.
*
*
****************************************************************************/

#ifndef CPOIDATABASE_H
#define CPOIDATABASE_H

/*Header files*/
#include<string>
#include <map>
#include "CPOI.h"
#include<vector>
#include "CDatabase.h"

/**
 * The CPOIDatabase class represents a database with several points of interest.
 */
class CPoiDatabase: public CDatabase<std::string, CPOI> {
private:
	/**
	 * Map of points of interest (POI).
	 * @link aggregationByValue
	 * @supplierCardinality 10
	 * @clientCardinality 1
	 */
//	std::map<std::string, CPOI> m_POI;
public:
    /**
	 * Constructor
    */
    CPoiDatabase();

    /**
	 * This method will add a POI to the POI database.
	 * If a POI of same name is trying to be added, the
	 * it will not be added to the database.
	 * @param poi The CPOI instance that has to be added
	 * @return void
	 */
    void addPoi(CPOI const & poi);

    /**
	 * This method will provide a pointer to a valid POI that exists in the
	 * database based on the name of the POI.
	 * @param name Name of the POI for which a pointer is to be returned.
	 * @return CPOI *, a valid pointer to the POI if it exists in the database else NULL.
	 */
    CPOI* getPointerToPoi(std::string name);

    /**
     * Provides a vector of CPOI pointers for all CPOI in the database
     * @param allPoi A vector to contain the reference to all POIs in the database
     */
    std::map<std::string, CPOI> getPointersToAllPoi() const;

    /**
     * Adds multiple POIs to the database
     * @param allPoi A vector containing all POIs to be added to database
     */
    void addMultiplePoi(std::vector<CPOI> allPoi);

    /**
     * Clears the database
     */
    void clearDatabase();

    /**
     * Prints all the POIs in the database
     */
    void print();
};
/********************
**  CLASS END
*********************/
#endif /* CPOIDATABASE_H */
