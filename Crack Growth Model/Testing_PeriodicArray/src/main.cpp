/*
 * main.cpp
 *
 *  Created on: Sep 28, 2012
 *      Author: jqnorris
 */

#include "element.h"
#include "periodicArray.h"
#include "iostream"

int main()
{
	periodicArray test(10);

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			test[i][j].gap=i+j;
		}
	}

	for(int i=0; i<10; i++)
	{
		for(int j=0; j<10; j++)
		{
			std::cout << test[i][j].gap <<"  ";
		}
		std::cout << std::endl;
	}

	return 0;
}


