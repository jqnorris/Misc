/*
 * periodicVector.h
 *
 *  Created on: Sep 28, 2012
 *      Author: jqnorris
 */

#ifndef PERIODICVECTOR_H_
#define PERIODICVECTOR_H_

#include "element.h"

class periodicVector {
public:
	periodicVector();
	virtual ~periodicVector();
	int N;
	element * vector;
	void initialize(int Nin);
	element& operator[](int i);
};

#endif /* PERIODICVECTOR_H_ */
