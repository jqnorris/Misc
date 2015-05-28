/*
 * Model.cpp
 *
 *  Created on: Sep 28, 2012
 *      Author: jqnorris
 */

#include "Model.h"
#include "randKnuth.h"
#include <cmath>

Model::Model(periodicArray & arrayIn, OptionsBin & optionsIn)
:array(arrayIn), currentOptions(optionsIn)
{

}

Model::~Model()
{

}

void Model::timeStep()
{
	double deltaGap = getDeltaGap();

	currentElement = array.getRandomElement();

	double deltaEnergy = getDeltaEnergy(deltaGap);

	if(checkBoltzmann(deltaEnergy))
	{
		array[currentElement.x][currentElement.y].gap+=deltaGap;
	}

	numSteps++;
}

double Model::getDeltaGap()
{
	if(randKnuth() >= 0.5)
	{
		return currentOptions.deltaGap;
	}
	return -currentOptions.deltaGap;
}



double Model::getDeltaEnergy(double deltaGap)
{
	return freeEnergy(deltaGap)-freeEnergy();
}

bool Model::checkBoltzmann(double deltaEnergy)
{
	if(deltaEnergy > 0)
	{
		if( exp(-deltaEnergy/currentOptions.Temperature) > randKnuth())
		{
			return false;
		}
	}

	return true;
}


double Model::freeEnergy(double deltaGap)
{
	const double & Gap = array[currentElement.x][currentElement.y].gap + deltaGap;

	double forceTerm =  currentOptions.externalForce*Gap;

	double tempTerm = -currentOptions.interactionStrength * Gap * Gap;

	for(int i = 0; i < (2 * currentOptions.interactionRange + 1); i++ )
	{
		for(int j = 0; j < (2 * currentOptions.interactionRange + 1); j++)
		{
			tempTerm += currentOptions.interactionStrength * Gap * array[i][j].gap;
		}
	}
	double interactionTerm = 0.5 * tempTerm;

	double cohesionTerm = 2 * currentOptions.cohesionStrength * (1 - exp(-Gap * Gap));

	double quadraticTerm = currentOptions.quadraticStrength * pow(Gap, 4);

	return forceTerm + interactionTerm + cohesionTerm +quadraticTerm;
}
