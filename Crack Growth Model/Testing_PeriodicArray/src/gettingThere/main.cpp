/*
 * main.cpp
 *
 *  Created on: Sep 28, 2012
 *      Author: jqnorris
 */

#include "iostream"
#include "periodicVector.h"

int main()
{
	//
	//	element * alpha;
	//	alpha = new element[10];
	//
	//	for(int i=0; i< 10; i++)
	//	{
	//		alpha[i].gap=i;
	//	}
	//
	//	for(int i=0; i< 10; i++)
	//	{
	//		std::cout << alpha[i].gap << std::endl;
	//	}
	//
	//	delete[] alpha;
	//

	periodicVector* array;
	array= new periodicVector[10];



	for(int i=0; i<10; i++)
	{
		array[i].initialize(10);
	}

	std::cout << std::endl << std::endl << std::endl;

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			array[i][j].gap=i+j;
		}
	}
	for(int i=0; i<10; i++)
	{
		std::cout << array[3][i].gap << std::endl;
	}

	delete[] array;

	return 0;
}


