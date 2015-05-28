/*
 * Model.cpp
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#include "Model.h"
#include "periodicArray.h"
#include "OptionsBin.h"
#include "element.h"
#include "randKnuth.h"
#include "orderedPair.h"
#include <cmath>

void Model(periodicArray & array, OptionsBin & Options)
{
	using namespace modelFunctions;

	double deltaGap = getDeltaGap(Options.deltaGap);

	orderedPair randElement=array.getRandomElement();

	double deltaEnergy = getDeltaEnergy(periodicArray & A, orderedPair & E, OptionsBin & options, double deltaGap=0)





}

namespace modelFunctions
{
double getDeltaGap(double size)
{
	if(randKnuth() >= 0.5)
	{
		return size;
	}
	return -size;
}

double getDeltaEnergy(periodicArray & A, orderedPair & E, OptionsBin & options, double deltaGap)
{
	double freeEnergy();

	return 1;
}

void checkBoltzmann(double deltaEnergy, double temperature)
{


}


double freeEnergy(periodicArray & A, orderedPair & E, OptionsBin & options, double deltaGap=0)
{
	double forceTerm = options.externalForce*A[E.x][E.y].gap;

	double tempTerm = -options.interactionStrength * A[E.x][E.y].gap * A[E.x][E.y].gap;

	for(int i = 0; i < (2 * options.interactionRange + 1); i++ )
	{
		for(int j = 0; j < (2 * options.interactionRange + 1); j++)
		{
			tempTerm += options.interactionStrength * A[E.x][E.y].gap * A[i][j].gap;
		}
	}
	double interactionTerm = 0.5 * tempTerm;

	double cohesionTerm = 2 * options.cohesionStrength * (1 - exp(-A[E.x][E.y].gap * A[E.x][E.y].gap));

	double quadraticTerm = options.quadraticStrength * pow(A[E.x][E.y].gap, 4);

	return forceTerm + interactionTerm + cohesionTerm +quadraticTerm;

}
}
