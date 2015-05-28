/*
 * Simulation.cpp
 *
 *  Created on: Nov 30, 2012
 *      Author: jqnorris
 */

#include "Simulation.h"
#include "iostream"

using std::pair;

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
	for(int i=0; i< options.latticeType; i++)
	{
		if(cluster[currentStep-1]->neighbors[i]->pore1->volume != cluster[currentStep-1]->neighbors[i]->pore2->volume)
		{
			perimeter.insert(pair<double, Rock*>(cluster[currentStep-1]->neighbors[i]->strength, cluster[currentStep-1]->neighbors[i]));
		}
	}

	while(perimeter.begin()->second->pore1->volume == perimeter.begin()->second->pore2->volume)
	{
		perimeter.erase(perimeter.begin());
	}

	perimeter.begin()->second->damage=1;
	fractures[currentStep-1] = perimeter.begin()->second;

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

	perimeter.erase(perimeter.begin());

	currentStep++;
}
