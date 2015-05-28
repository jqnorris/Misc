
#include "iostream"

#include "../arrayPeriodicBC.h"
#include "arrayPeriodicBCTEST.h"
#include "../findSmallest.h"
#include "findSmallestTEST.h"
#include "../redistributeStress.h"
#include "redistributeStressTEST.h"



int main()
{

	arrayPeriodicBCTEST();
	findSmallestTEST();
	redistributeStressTEST();

	return 0;
}
