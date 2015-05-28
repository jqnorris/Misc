/*
 * periodicArray.h
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#ifndef PERIODICARRAY_H_
#define PERIODICARRAY_H_

#include "element.h"

class periodicArray {
public:
	periodicArray(int Ninput);
	virtual ~periodicArray();
	int N;
	element ** array;
};

#endif /* PERIODICARRAY_H_ */
