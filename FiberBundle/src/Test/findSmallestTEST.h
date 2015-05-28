
#include "../findSmallest.h"
#include "../arrayPeriodicBC.h"
#include "../fiberElement.h"
#include <iostream>

void findSmallestTEST()
{
	ArrayPeriodicBC<fiberElement,10> arrayTemp;


	for(int i=0, n=0; i<10; i++)
	{
		for(int j=0; j<10; j++, n++)
		{
			arrayTemp[i][j].setFailTime((double)n);
			arrayTemp[i][j].heal();
		}
	}

	ArrayPeriodicBC<fiberElement,10>* pArray= &arrayTemp;

	int a1=0;
	int a2=0;
	findSmallest(pArray, 10, a1, a2);

	for(int i=0, n=0; i<10; i++)
	{
		for(int j=0; j<10; j++, n++)
		{
			arrayTemp[i][j].setFailTime((double)100-n);
		}
	}

	int a3=0;
	int a4=0;
	findSmallest(pArray, 10, a3, a4);

	for(int i=0, n=0; i<10; i++)
	{
		for(int j=0; j<10; j++, n++)
		{
			arrayTemp[i][j].setFailTime(-(double)((50+n)%100));
		}
	}

	int a5=0;
	int a6=0;
	findSmallest(pArray, 10, a5, a6);




	if(a1==0 && a2==0 && a3==9 && a4==9 && a5==4 && a6==9)
	{
		std::cout << "findSmallest test PASSED.\n";
	}
	else
	{
		std::cout << "findSmallest test FAILED!\n";
	};
}
