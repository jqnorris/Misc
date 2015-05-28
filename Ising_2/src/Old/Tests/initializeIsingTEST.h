/*
 * initializeIsingTEST.h
 *
 *  Created on: Jul 10, 2012
 *      Author: jqnorris
 */

#ifndef INITIALIZEISINGTEST_H_
#define INITIALIZEISINGTEST_H_

#include "../initializeIsing.h"
#include "../isingElement.h"
#include <iostream>

void initializeIsingTEST()
{
	element a[10][10];
	element (*pa)[10][10]=&a;

	initializeIsing(pa, 10, 0);

	int errorcount1=0;

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			if ((*pa)[i][j].getSpin()!=1)
				errorcount1++;
		}
	}

	initializeIsing(pa, 10, 1);

	int errorcount2=0;

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			if ((*pa)[i][j].getSpin()!=-1 && (*pa)[i][j].getSpin()!=1)
				errorcount2++;
		}
	}

	if (errorcount1+errorcount2==0)
	{
		std::cout << "initializeIsing test PASSED.\n";
	}
	else
	{
		std::cout << "initializeIsing test FAILED!\n";
	};

}

#endif /* INITIALIZEISINGTEST_H_ */
