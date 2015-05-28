#include "../arrayPeriodicBC.h"
#include "../fiberElement.h"
#include "../redistributeStress.h"
#include <iostream>

void redistributeStressTEST()
{
	ArrayPeriodicBC<fiberElement,3> arrayTemp;


	for(int i=0, n=0; i<3; i++)
	{
		for(int j=0; j<3; j++, n++)
		{
			arrayTemp[i][j].setStress(0);
			arrayTemp[i][j].heal();
		}
	}

	arrayTemp[1][1].setStress(8);
	arrayTemp[1][1].fracture();

	ArrayPeriodicBC<fiberElement,3>* pArray= &arrayTemp;

	redistributeStress(pArray, 1, 1, 3, 1, 8);

	int errorcount=0;

	for(int i=0, n=0; i<3; i++)
	{
		for(int j=0; j<3; j++, n++)
		{
			if (arrayTemp[i][j].getStress()!=1)
				errorcount++;
		}
	}



	if(errorcount==1)
	{
		std::cout << "redistributeStress test PASSED.\n";
	}
	else
	{
		std::cout << "redistributeStress test FAILED!\n";
	};
}
