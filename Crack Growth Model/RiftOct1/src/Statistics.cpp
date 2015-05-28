/*
 * Statistics.cpp
 *
 *  Created on: Oct 1, 2012
 *      Author: jqnorris
 */

#include "Statistics.h"
#include "periodicArray.h"

Statistics::Statistics(periodicArray & arrayIn): array(arrayIn)
{

}

Statistics::~Statistics()
{

}

double Statistics::averageGap()
{
	double totalGap=0;

	for(int i=0; i < array.N; i++)
	{
		for(int j=0; j < array.N; j++)
		{
			totalGap+=array[i][j].gap;
		}
	}

	return totalGap/(array.N*array.N);
}
