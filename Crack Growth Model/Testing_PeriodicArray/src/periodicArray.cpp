/*
 * periodicArray.cpp
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#include "periodicArray.h"

periodicArray::periodicArray(int Ninput)
{
	N=Ninput;

	array = new periodicVector[Ninput];

	for(int i=0; i<Ninput; i++)
	{
		array[i].initialize(N);
	}

};

periodicArray::~periodicArray()
{
	delete[] array;
};

periodicVector& periodicArray::operator[](int i)
{
	if(i < 0 || i > N - 1 )
	{
	return array[((i%N+N)%N)];
	}
	return array[i];
}


periodicVector::periodicVector()
{

}

periodicVector::~periodicVector()
{
	delete[] vector;
}

void periodicVector::initialize(int Nin)
{
	N = Nin;

	vector = new element[Nin];
}

element& periodicVector::operator[](int i)
{
	if(i < 0 || i > N - 1 )
	{
	return vector[((i%N+N)%N)];
	}
	return vector[i];
}
