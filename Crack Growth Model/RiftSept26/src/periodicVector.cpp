/*
 * periodicVector.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: jqnorris
 */

#include "periodicVector.h"


periodicVector::periodicVector(int Ninput)
{
	N=Ninput;
	vector = new element[N];
}

periodicVector::~periodicVector()
{
	delete[] vector;
}

element& periodicVector::operator [](int i)
{
	return vector[(i%N+N)%N];
}
