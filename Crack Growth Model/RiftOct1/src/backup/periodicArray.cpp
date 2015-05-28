/*
 * periodicArray.cpp
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#include "periodicArray.h"
#include "randKnuth.h"

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
	return array[((i%N+N)%N)];
}

orderedPair periodicArray::getRandomElement()
{
	int site = randKnuth()*N*N;
	return orderedPair(site/N,site % N);
}

void periodicArray::initialize(double token)
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			(*this)[i][j].initialize(token);
		}
	}
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
	return vector[((i%N+N)%N)];
}
