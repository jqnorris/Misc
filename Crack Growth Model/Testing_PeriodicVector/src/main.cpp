/*
 * main.cpp
 *
 *  Created on: Sep 28, 2012
 *      Author: jqnorris
 */

#include "element.h"
#include "periodicVector.h"
#include "iostream"

int main()
{
	periodicVector test;
	test.initialize(10);

	for(int i=0; i<10; i++)
	{
		test[i].gap=i;
	}

	std::cout << std::endl << std::endl << std::endl;

	for(int i=0; i<10; i++)
	{
		std::cout << test[i+10].gap << std::endl;
	}

	return 0;
}

