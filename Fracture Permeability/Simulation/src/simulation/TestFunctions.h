/*
 * TestingSimulationFunctions.h
 *
 *  Created on: Dec 1, 2012
 *      Author: jqnorris
 */

#ifndef TESTINGSIMULATIONFUNCTIONS_H_
#define TESTINGSIMULATIONFUNCTIONS_H_

#include "Simulation.h"

namespace simulationFunctionsTestFunctions
{
void testSimulationFunctions();
int testDamageMatrix(PoreArray &, Options &);
int testFlow(Matrix &, Options &);
int testApplyBoundaryConditions(PoreArray &, Matrix &, Options &);
}

#endif /* TESTINGSIMULATIONFUNCTIONS_H_ */
