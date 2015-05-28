/*
 * Simulation.h
 *
 *  Created on: Nov 30, 2012
 *      Author: jqnorris
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "../framework/Framework.h"
#include "DamageMatrix.h"
#include "Flow.h"
#include "ApplyBoundaryConditions.h"
#include "TestFunctions.h"
#include "InitializeMatrix.h"
#include "InitializePores.h"

class Simulation {
public:
	Simulation(PoreArray &, Matrix &, Options &);
	virtual ~Simulation();
	PoreArray & pores;
	Matrix & matrix;
	Options & options;
	void initialize();
	void timestep();

};

#endif /* SIMULATION_H_ */
