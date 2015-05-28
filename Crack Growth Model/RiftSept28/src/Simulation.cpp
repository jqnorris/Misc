/*
 * Simulation.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: jqnorris
 */

#include "OptionsBin.h"
#include "periodicArray.h"
#include "Model.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <time.h>

int main()
{
	time_t start, end;

	time (&start);

	long int t;

	OptionsBin initialOptions(true);

	OptionsBin currentOptions = initialOptions;

	periodicArray array(currentOptions.arraySize);

	array.initialize(currentOptions.initialGap);

	Model FirstRun(array, currentOptions);

	for(int i=0; i< 1000; i++)
	{
		FirstRun.timeStep();
	}

	time (&end);

	double dif = difftime(end, start);

	t = clock();

	printf ("It took %.2lf seconds.\n", dif );
	printf ("It took %f seconds.\n",((float)t)/CLOCKS_PER_SEC);

	return 0;
}
