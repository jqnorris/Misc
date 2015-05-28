/*
 * periodicArray.cpp
 *
 *  Created on: Sep 26, 2012
 *      Author: jqnorris
 */

#include "periodicArray.h"

periodicArray::periodicArray(int Ninput)
{
    N=Ninput;
	array = new periodicVector(Ninput);

}

periodicArray::~periodicArray()
{
	delete[] array;
}

periodicVector& periodicArray::operator [](int i)
{
	return array[(i%N+N)%N];
}
