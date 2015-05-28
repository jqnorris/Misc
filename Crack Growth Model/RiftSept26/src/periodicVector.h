/*
 * periodicVector.h
 *
 *  Created on: Sep 26, 2012
 *      Author: jqnorris
 */

#ifndef PERIODICVECTOR_H_
#define PERIODICVECTOR_H_

#include "element.h"

class periodicVector {
public:
	periodicVector(int N);
	virtual ~periodicVector();
	int N; // Size of vector
	element * vector; //
	element& operator [](int i);

};

#endif /* PERIODICVECTOR_H_ */
