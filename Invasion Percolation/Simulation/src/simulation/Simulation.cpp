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

	cluster = new Pore*[options.maxSteps+1]();
	fractures = new Rock*[options.maxSteps]();

	cluster[0] = & pores.pores[options.N/2][options.N/2];

	cluster[0]->volume=1;
	currentStep=1;

}

Simulation::~Simulation()
{
	delete[] cluster;
	delete[] fractures;
}

void Simulation::initialize()
{
	setupPoreNeighbors(pores, matrix, options);
	setupMatrixNeighbors(pores, matrix, options);
}

void Simulation::timestep()
{
	double minStrength=1;

	for(int i=0; i<currentStep; i++)
	{
		for(int j=0; j<options.latticeType; j++)
			if(cluster[i]->neighbors[j]->pore1->volume != cluster[i]->neighbors[j]->pore2->volume)
			{
				if(cluster[i]->neighbors[j]->strength < minStrength)
				{
					minStrength = cluster[i]->neighbors[j]->strength;
					fractures[currentStep-1] = cluster[i]->neighbors[j];
				}
			}
	}

	if(fractures[currentStep-1]->pore1->volume != 1)
	{
		fractures[currentStep-1]->pore1->volume = 1;
		cluster[currentStep] = fractures[currentStep-1]->pore1;
	}
	if(fractures[currentStep-1]->pore2->volume != 1)
	{
		fractures[currentStep-1]->pore2->volume = 1;
		cluster[currentStep] = fractures[currentStep-1]->pore2;
	}

	currentStep++;
}
