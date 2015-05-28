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

int main()
{

	OptionsBin Options(true);

	periodicArray Sim(Options.arraySize);

	Sim.initialize(Options.initialGap);

	Model(Sim, Options);

	return 0;
}
