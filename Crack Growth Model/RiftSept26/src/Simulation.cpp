/*
 * Simulation.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: jqnorris
 */

#include "OptionsBin.h"
#include "periodicArray.h"
#include "randKnuth.h"
#include <string>
#include <iostream>

int main()
{

	OptionsBin Options(true);

	periodicArray array(Options.arraySize);

	(array[1][1]).gap=5;

	std::cout << ((array[1][1]).gap) << std::endl << std::endl;


	std::cout << randKnuth() * (Options.arraySize*Options.arraySize-1) + 0.5 << std::endl;

	return 0;
}
