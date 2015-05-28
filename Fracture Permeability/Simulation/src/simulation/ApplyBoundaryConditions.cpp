/*
 * ApplyBoundaryConditions.cpp
 *
 *  Created on: Dec 3, 2012
 *      Author: jqnorris
 */

#include "ApplyBoundaryConditions.h"

void applyBoundaryConditions(PoreArray & pores, Matrix & matrix, Options & options)
{
	int x=options.N/2;
	int y=options.N/2;

	pores.pores[x][y].currentVolume+=options.deltaV0;


	pores.leakoff=+pores.reservoir.deltaVolume;
	pores.reservoir.deltaVolume=0;
}

