
#include "iostream"

#include "../arrayPeriodicBC.h"
#include "arrayPeriodicBCTEST.h"
#include "../initializeIsing.h"
#include "initializeIsingTEST.h"
#include "../initializeNeighbors.h"
#include "initializeNeighborsTEST.h"
#include "../isingStep.h"
#include "isingStepTEST.h"

int a[10][10];

int main()
{

	arrayPeriodicBCTEST();
	initializeIsingTEST();
	initializeneighborsTEST();
	isingStepTEST();


	return 0;
}
