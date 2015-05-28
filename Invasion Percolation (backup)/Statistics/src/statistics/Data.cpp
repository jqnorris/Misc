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

Data::Data(PoreArray & P, Matrix & M, Options & O, Simulation & S):pores(P),matrix(M),options(O),simulation(S)
{
	initialize();
}

Data::~Data()
{

}

void Data::writeInvasion()
{
	ofstream toFile1("invasion.txt", std::ios::app);
	ofstream toFile2("fractures.txt", std::ios::app);
	ofstream toFile3("clusters.txt", std::ios::app);

	toFile2.precision(17);

	for(int i=0; i< simulation.currentStep; i++)
	{
		toFile1 << simulation.cluster[i]->positionX << "\t" << simulation.cluster[i]->positionY << "\t" << "\n";
	}

	for(int i=0; i< simulation.currentStep-1; i++)
	{
		toFile2 << simulation.fractures[i]->strength << "\n";
	}

	toFile1.close();
	toFile2.close();

	for(int i=0; i< matrix.xDimension; i++)
	{
		for(int j=0; j< matrix.yDimension; j++)
		{
			toFile3 << matrix.matrix[i][j].pore1->positionX << "\t";
			toFile3 << matrix.matrix[i][j].pore1->positionY << "\t";
			toFile3 << matrix.matrix[i][j].pore2->positionX << "\t";
			toFile3 << matrix.matrix[i][j].pore2->positionY << "\t";
			toFile3 << matrix.matrix[i][j].strength << "\n";
		}
	}

	toFile3.close();
}

void Data::initialize()
{
	ofstream toFile1("invasion.txt", std::ios::trunc);
	toFile1 << "Invasion for: " << options.jobName << "\n";
	toFile1.close();

	ofstream toFile2("fractures.txt", std::ios::trunc);
	toFile2 << "Fractures for: " << options.jobName << "\n";
	toFile2.close();

	ofstream toFile3("clusters.txt", std::ios::trunc);
	toFile3 << "Clusters for: " << options.jobName << "\n";
	toFile3.close();

}
