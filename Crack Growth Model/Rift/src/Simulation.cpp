/*
 * Simulation.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: jqnorris
 */

#include "OptionsBin.h"
#include "periodicBC.h"
#include "site.h"
#include "randKnuth.h"
#include <string>
#include <iostream>

int main()
{

	OptionsBin Options(true);

	if (Options.boundaryConditions == "Periodic")
	{
		ArrayPeriodicBC<site, Options.arraySize>* pArray
			= new ArrayPeriodicBC<site, Options.arraySize>;
	}


	std::cout << randKnuth() * (Options.arraySize*Options.arraySize-1) + 0.5;

}
