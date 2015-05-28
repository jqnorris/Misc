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
double getDeltaEnergy(double deltaGapIn, const OptionsBin & options);
void checkBoltzmann(double detaGap, double temperature);
double freeEnergy(periodicArray & array, orderedPair element, OptionsBin & options, double deltaGap=0);
}

#endif /* MODEL_H_ */
