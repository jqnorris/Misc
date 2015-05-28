/*
 * Simulation.h
 *
 *  Created on: Nov 30, 2012
 *      Author: jqnorris
 */

#ifndef SIMULATION_H_
#define SIMULATION_H_

#include "../framework/Framework.h"
#include <map>

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
	std::multimap<double, Rock*> perimeter;
};

#endif /* SIMULATION_H_ */
