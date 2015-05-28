// Playing around with C++

#include "isingElement.h"
#include "arrayPeriodicBC.h"
#include "initializeIsing.h"
#include "isingNeighbors.h"
#include "initializeNeighbors.h"
#include "isingStep.h"
#include "randKnuth.h"
#include <iostream>
#include <typeinfo>
#include <cmath>

// Size of square lattice
const int N=50;

// Rectilinear range of interactions
const int R=1;

// Temperature
const int T=0.001;

// Runs
const int runs=10000;

int main()
{
	ArrayPeriodicBC<element,N>* pArray = new ArrayPeriodicBC<element,N>;

	initializeIsing<>(pArray, N, 1);

	neighbors<element, N, R>* arrayNeighbors= new neighbors<element, N, R>;

	initializeNeighbors<>(pArray, arrayNeighbors, N, R);

	isingStep<>(pArray, arrayNeighbors, N, R, T);

	for(int i=0; i<runs;)
	{
		for(int j=0; j<50; j++, i++)
		{
			isingStep(pArray, arrayNeighbors, N, R, T);
		}

	}


	std::cout << (*pArray)[4][2].getSpin() << std::endl;
	std::cout << (*arrayNeighbors).neighborsUp[4][2] << std::endl;


	delete pArray;
	delete arrayNeighbors;
	return 0;
}

