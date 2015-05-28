
#include "RandKnuth.h"
#include <iostream>
#include <fstream>

int main()
{
	std::ofstream toFile("precisionTest.txt");

	toFile.precision(17);

	for(int i=0; i< 200; i++)
	{
		toFile << randKnuth() << "\n";
	}

	toFile.close();

	return 0;
}


