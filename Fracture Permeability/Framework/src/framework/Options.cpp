/*
 * Options.cpp
 *
 *  Created on: Nov 29, 2012
 *      Author: jqnorris
 */

#include "Options.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

using std::cout;
using std::endl;
using std::getline;
using std::string;

Options::Options()
{

	loadFromFile();

}

Options::~Options()
{

}

void Options::loadFromFile()
{
	int counter=0;

	string test, temp;

	std::ifstream optionsFile("options.in");

	if(optionsFile.good())
	{
		cout << endl << "Loading Options File." << endl << endl;

		getline(optionsFile, jobName);
		cout << "\tOptions for: " << jobName << endl;

		counter++;

		getline(optionsFile, test, '=');
		if (test == "Volume")
		{
			getline(optionsFile, temp);
			v0 =atof(temp.c_str());
			cout << "\t Volume = " << v0<< endl;

			counter++;
		}

		getline(optionsFile, test, '=');
		if (test == "N")
		{
			getline(optionsFile, temp);
			N =atoi(temp.c_str());
			cout << "\t N = " << N<< endl;

			counter++;
		}

		getline(optionsFile, test, '=');
		if (test == "LatticeType")
		{
			getline(optionsFile, temp);
			latticeType =atoi(temp.c_str());
			cout << "\t LatticeType = " << latticeType<< endl;

			counter++;
		}

		getline(optionsFile, test, '=');
		if (test == "YoungsModulus")
		{
			getline(optionsFile, temp);
			E0 =atof(temp.c_str());
			cout << "\t YoungsModulus = " << E0 << endl;

			counter++;
		}

		getline(optionsFile, test, '=');
		if (test == "YieldStrain")
		{
			getline(optionsFile, temp);
			epsilonY0 =atof(temp.c_str());
			cout << "\t YieldStrain = " << epsilonY0 << endl;

			counter++;
		}

		getline(optionsFile, test, '=');
		if (test == "Permeability")
		{
			getline(optionsFile, temp);
			k0 =atof(temp.c_str());
			cout << "\t Permeability = " << k0 << endl;

			counter++;
		}

		getline(optionsFile, test, '=');
		if (test == "Porosity")
		{
			getline(optionsFile, temp);
			phi0 =atof(temp.c_str());
			cout << "\t Porosity = " << phi0 << endl;

			counter++;
		}

		getline(optionsFile, test, '=');
		if (test == "DeltaVolume")
		{
			getline(optionsFile, temp);
			deltaV0 =atof(temp.c_str());
			cout << "\t DeltaVolume = " << deltaV0 << endl;

			counter++;
		}

		getline(optionsFile, test, '=');
		if (test == "TimeSteps")
		{
			getline(optionsFile, temp);
			timeSteps =atoi(temp.c_str());
			cout << "\t TimeSteps = " << timeSteps << endl;

			counter++;
		}
	}
	else
	{

		cout << endl << "No Options File Found!!!" << endl;
		cout << endl << "\tUsing default values." << endl;

		setDefault();
		counter=-1;

	};

	if (counter==10 || counter==-1)
	{
		error=false;
		cout << endl << "Options successfully set." << endl << endl;

	}
	else
	{
		cout << endl << "\t***Error Loading Options!!!***" << endl;
		cout << endl << "\tUsing default values." << endl;
		setDefault();
		error=true;
	}
}

void Options::setDefault()
{
	jobName="DEFAULT";
	v0=1;
	N=5;
	latticeType=4;
	E0=0;
	epsilonY0=0;
	k0=0;
	phi0=0;
	deltaV0=0.5;

}
