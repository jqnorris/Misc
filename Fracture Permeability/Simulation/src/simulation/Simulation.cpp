/*
 * Simulation.cpp
 *
 *  Created on: Nov 30, 2012
 *      Author: jqnorris
 */

#include "Simulation.h"

Simulation::Simulation(PoreArray & P, Matrix & M, Options & O):pores(P),matrix(M),options(O)
{
 initialize();
}

Simulation::~Simulation()
{

}

void Simulation::initialize()
{
	initializePores(pores, matrix, options);
	initializeMatrix(pores, matrix, options);
}

void Simulation::timestep()
{
	pores.forAllPores(damageMatrix, options);
	matrix.forAllRock(calcFlow, options);
	pores.forAllPores(flow, options);
	applyBoundaryConditions(pores,matrix,options);
}
