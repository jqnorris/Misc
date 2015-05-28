/*
 * simulation.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: jqnorris
 */
#include <iostream>
#include "includes/includes.h"

using std::cout;
using std::endl;

int main(void)
{
	Options options;

	PoreArray pores(options);

	Matrix matrix(options);

	Simulation simulation(pores, matrix, options);

	Data data(pores, matrix, options);

	for(int i=0; i<options.timeSteps; i++)
	{
		simulation.timestep();
		data.connectivity();
	}

	return 0;
}
