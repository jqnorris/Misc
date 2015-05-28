/*
 * periodicArray.h
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#ifndef PERIODICARRAY_H_
#define PERIODICARRAY_H_

#include "element.h"
#include "orderedPair.h"

class periodicArray {
public:
	periodicArray(int Ninput);
	virtual ~periodicArray();
	int N;
	element ** array;
	unsigned int numSteps;
	int bC(int i);
	orderedPair randElement();
	void initialize(double initialGap);
};

#endif /* PERIODICARRAY_H_ */
