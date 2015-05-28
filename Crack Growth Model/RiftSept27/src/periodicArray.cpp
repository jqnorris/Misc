/*
 * periodicArray.cpp
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#include "periodicArray.h"
#include "element.h"
#include "randKnuth.h"
#include "orderedPair.h"

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

int periodicArray::bC(int i)
{
	return ((i%N+N)%N);
}

orderedPair periodicArray::randElement()
{
	int site = randKnuth()*N*N;
	return orderedPair(site/N,site % N);
}

void periodicArray::initialize(double initialGap)
{
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			array[i][j].gap=initialGap;
		}
	}
}

