/*
 * Model.h
 *
 *  Created on: Sep 28, 2012
 *      Author: jqnorris
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "periodicArray.h"
#include "OptionsBin.h"
#include "orderedPair.h"

class Model {
public:
	Model(periodicArray & arrayIn, OptionsBin & optionsIn);
	virtual ~Model();
	unsigned int numSteps;
	periodicArray & array;
	OptionsBin currentOptions;
	orderedPair currentElement;
	void timeStep();
	double getDeltaGap();
	double getDeltaEnergy(double deltaGap);
	bool checkBoltzmann(double detaGap);
	double freeEnergy(double deltaGap=0);

};

#endif /* MODEL_H_ */
