/*
 * Simulation.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: jqnorris
 */

#include "OptionsBin.h"
#include "periodicArray.h"
#include "Model.h"
#include "Statistics.h"
#include <string>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <time.h>

int main()
{
	time_t start, end;

	time (&start);

	OptionsBin initialOptions(true);

	OptionsBin currentOptions = initialOptions;

	periodicArray array(currentOptions.arraySize);

	array.initialize(currentOptions.initialGap);

	Statistics firstRunStats(array);

	std::cout << "The average initial gap is : "
			<< firstRunStats.averageGap() << std::endl;

	Model FirstRun(array, currentOptions);


	std::ofstream file;
	file.open("testingOutput");


	for(int i=0; i< 500; i++)
	{
		FirstRun.timeStep();
		if(i%100 == 0)
		{
			for(int i=0; i < currentOptions.arraySize; i++)
			{
				for(int j=0; j < currentOptions.arraySize; j++)
				{
					file << array[i][j].gap << " ";
				}
			}
			file << std::endl;
		}
	}

	std::cout << "The average final gap is : "
			<< firstRunStats.averageGap() << std::endl;

	time (&end);

	double dif = difftime(end, start);

	printf ("This run took %.2lf seconds.\n", dif );

	return 0;
}
