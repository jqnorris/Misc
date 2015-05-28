/*
 * initializeNeighborsTEST.h
 *
 *  Created on: Jul 11, 2012
 *      Author: jqnorris
 */

#ifndef INITIALIZENEIGHBORSTEST_H_
#define INITIALIZENEIGHBORSTEST_H_

#include "../initializeNeighbors.h"
#include "../isingElement.h"
#include "../isingNeighbors.h"
#include "../pbcIndexer.h"
#include <iostream>

void initializeneighborsTEST()
{
	ArrayPeriodicBC<element,3> patemp;
	ArrayPeriodicBC<element,3>* pa=&patemp;

	(*pa)[0][0].setSpin(1);
	(*pa)[0][1].setSpin(-1);
	(*pa)[0][2].setSpin(1);
	(*pa)[1][0].setSpin(-1);
	(*pa)[1][1].setSpin(1);
	(*pa)[1][2].setSpin(-1);
	(*pa)[2][0].setSpin(1);
	(*pa)[2][1].setSpin(-1);
	(*pa)[2][2].setSpin(1);

	neighbors<element, 3, 1> natemp;
	neighbors<element, 3, 1>* na=&natemp;

	initializeNeighbors(pa, na, 3, 1);

	int errorcount1=0;

	for(int i=0; i<3; i++)
	{
		for(int j=0; j<3; j++)
		{
			if ((*na).neighbors[i][j][1]!=&((*na).neighborsUp[pbc(i-1,3)][(j)]))
				errorcount1++;
		}
	}



	int errorcount2=0;

	if ((*na).neighborsUp[1][1]!=4)
	{
		errorcount2++;
	}
	if ((*na).neighborsUp[0][0]!=4)
	{
		errorcount2++;
	}
	if ((*na).neighborsUp[2][1]!=5)
	{
		errorcount2++;
	}


	if ((errorcount1+errorcount2)==0)
	{
		std::cout << "initializeNeighbors test PASSED.\n";
	}
	else
	{
		std::cout << "initializeNeighbors test FAILED!\n";
	};

}

#endif /* INITIALIZENEIGHBORSTEST_H_ */
