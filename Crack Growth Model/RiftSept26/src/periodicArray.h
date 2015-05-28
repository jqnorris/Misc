/*
 * periodicArray.h
 *
 *  Created on: Sep 26, 2012
 *      Author: jqnorris
 */

#ifndef PERIODICARRAY_H_
#define PERIODICARRAY_H_

#include "periodicVector.h"

class periodicArray {
public:
	periodicArray(int N);
	virtual ~periodicArray();
	int N; // Size of array, N in NxN
	periodicVector * array; // Storing the elements
	periodicVector& operator [](int i);
};

#endif /* PERIODICARRAY_H_ */
