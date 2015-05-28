/*
 * Statistics.h
 *
 *  Created on: Oct 1, 2012
 *      Author: jqnorris
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include "periodicArray.h"

class Statistics {
public:
	Statistics(periodicArray & arrayIn);
	virtual ~Statistics();
	periodicArray & array;
	double averageGap();

};

#endif /* STATISTICS_H_ */
