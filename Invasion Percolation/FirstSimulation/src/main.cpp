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

	Data data(pores, matrix, options, simulation);

	std::cout << "Beginning Run" << std::endl;

	for(int i=0; i<options.maxSteps-1; i++)
	{
		simulation.timestep();
		if(pores.reservoir.volume !=0)
		{
			i=options.maxSteps;
		}
	}

	data.writeInvasion();

	std::cout << std::endl << simulation.currentStep << " Steps Successfully Completed!" << std::endl;

	return 0;
}
