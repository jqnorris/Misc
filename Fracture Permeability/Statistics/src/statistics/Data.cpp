/*
 * Data.cpp
 *
 *  Created on: Dec 7, 2012
 *      Author: jqnorris
 */

#include <iostream>
#include <fstream>
#include "Data.h"

using std::ofstream;

Data::Data(PoreArray & P, Matrix & M, Options & O):pores(P),matrix(M),options(O)
{
	initialize();

}

Data::~Data()
{
	// TODO Auto-generated destructor stub
}

void Data::connectivity()
{
	int connectivityCount=0;

	for(int i=0; i< pores.dimension; i++)
	{
			for(int j=0; j< pores.dimension; j++)
			{
				if(pores.pores[i][j].currentVolume != pores.pores[i][j].naturalVolume)
				{
					connectivityCount++;
				}

			}
	}

	ofstream toFile("connectivity.txt", std::ios::app);

	toFile << connectivityCount << " " << pores.leakoff << "\n";

}

void Data::initialize()
{
	ofstream toFile("connectivity.txt", std::ios::trunc);
	toFile << "Connectivity for: " << options.jobName << "\n";
	toFile.close();

}
