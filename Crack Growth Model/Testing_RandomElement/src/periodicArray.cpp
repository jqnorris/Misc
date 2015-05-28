/*
 * periodicArray.cpp
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#include "periodicArray.h"
#include "element.h"

periodicArray::periodicArray(int Ninput)
{
	N=Ninput;

	array = new element*[Ninput];
	for(int i=0; i < Ninput; i++)
	{
		array[i] = new element[N];
	}
}

periodicArray::~periodicArray()
{
	for(int i=0; i < N; i++)
	{
		delete[] array[i];
	}

	delete[] array;
}
