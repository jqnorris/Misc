/*
 * Model.h
 *
 *  Created on: Sep 27, 2012
 *      Author: jqnorris
 */

#ifndef MODEL_H_
#define MODEL_H_

#include "periodicArray.h"
#include "OptionsBin.h"
#include "orderedPair.h"

void Model(periodicArray &, OptionsBin &);

namespace modelFunctions
{
double getDeltaGap(double size);
double getDeltaEnergy(periodicArray & A, orderedPair & E, OptionsBin & options, double deltaGap);
void checkBoltzmann(double detaGap, double temperature);
double freeEnergy(periodicArray & A, orderedPair & E, OptionsBin & options, double deltaGap);
}

#endif /* MODEL_H_ */
