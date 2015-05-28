/*
 * periodicArray.h
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#ifndef PERIODICARRAY_H_
#define PERIODICARRAY_H_

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

class periodicArray {
public:
	periodicArray(int Ninput);
	virtual ~periodicArray();
	int N;
	periodicVector * array;
	periodicVector& operator[](int i);
};

#endif /* PERIODICARRAY_H_ */
