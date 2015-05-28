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

void Model(periodicArray & Sim, OptionsBin & Options)
{
	using namespace modelFunctions;

	double deltaGap = getDeltaGap(Options.deltaGap);

	//double deltaEnergy = getDeltaEnergy(deltaGap);





}

namespace modelFunctions
{
double getDeltaGap(double size)
{
	if(randKnuth()>=0.5)
	{
		return size;
	}
	return -size;
}

double getDeltaEnergy(double deltaGapIn, OptionsBin & options)
{
	double freeEnergy();

	return 1;
}

void checkBoltzmann(double deltaEnergy, double temperature)
{


}

double freeEnergy(periodicArray & A, orderedPair & givenElement, OptionsBin & options, double deltaGap=0)
{
	double forceTerm = options.externalForce*A.array[A.bC(givenElement.x)][A.bC(givenElement.y)].gap;

	double interactionTerm=0;
	for(int i=0; i < (2*options.interactionRange+1); i++ )
	{
		for(int j=0; j < (2*options.interactionRange+1); j++)
		{
			interactionTerm+=options.interactionStrength*A.array[A.bC(givenElement.x)][A.bC(givenElement.y)].gap*A.array[A.bC(i)][A.bC(j)].gap;
		}
	}



	return forceTerm+interactionTerm;
}
}
