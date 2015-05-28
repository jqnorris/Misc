/*
 * TestFunctions.h
 *
 *  Created on: Nov 30, 2012
 *      Author: jqnorris
 */

#ifndef TESTFUNCTIONS_H_
#define TESTFUNCTIONS_H_

#include "Framework.h"

namespace frameworkTestFunctions
{
void testFramework();
int testMatrixForAll(Matrix &, Options &);
int testPoreArrayForAll(PoreArray &, Options &);
int testSetupMatrixNeighborsSquareLattice(PoreArray &, Matrix &, Options &);
int testSetupMatrixNeighborsHexLattice(PoreArray &, Matrix &, Options &);
int testSetupPoreNeighborsSquareLattice(PoreArray &, Matrix &, Options &);
int testSetupPoreNeighborsHexLattice(PoreArray &, Matrix &, Options &);
}


#endif /* TESTFUNCTIONS_H_ */
