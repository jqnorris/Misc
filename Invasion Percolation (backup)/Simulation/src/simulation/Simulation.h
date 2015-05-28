/*
 * Simulation.h
 *
 *  Created on: Nov 30, 2012
 *      Author: jqnorris
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "../framework/Framework.h"

class Simulation {
public:
	Simulation(PoreArray &, Matrix &, Options &);
	virtual ~Simulation();
	PoreArray & pores;
	Matrix & matrix;
	Options & options;
	long int currentStep;
	Pore ** cluster;
	Rock ** fractures;
	void initialize();
	void timestep();
};

#endif /* SIMULATION_H_ */
