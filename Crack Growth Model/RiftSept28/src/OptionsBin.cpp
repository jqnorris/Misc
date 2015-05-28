/*
 * OptionsBin.cpp
 *
 *  Created on: Sep 25, 2012
 *      Author: jqnorris
 */

#include "OptionsBin.h"
#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstdio>

OptionsBin::OptionsBin()
{

}

OptionsBin::OptionsBin(bool loadFile)
{
	int counter=0;

	std::ifstream optionsFile("optionsFile.in");

	if (optionsFile.good())
	{
		std::cout << "Loading options file." << std::endl << std::endl;

		std::getline(optionsFile, jobName);
		std::cout << "   Options for: "
				<< jobName << std::endl;
		counter++;

		std::string test, temp;

		std::getline(optionsFile, test, '=');
		if (test == "arraySize")
		{
			std::getline(optionsFile, temp);
			arraySize = atoi(temp.c_str());
			std::cout << "      " << "arraySize"
					<< " = " << arraySize << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "initialGap")
		{
			std::getline(optionsFile, temp);
			initialGap = atof(temp.c_str());
			std::cout << "      initialGap = "
					<< initialGap << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "deltaGap")
		{
			std::getline(optionsFile, temp);
			deltaGap = atof(temp.c_str());
			std::cout << "      deltaGap = "
					<< deltaGap << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "externalForce")
		{
			std::getline(optionsFile, temp);
			externalForce = atof(temp.c_str());
			std::cout << "      externalForce = "
					<< externalForce << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "interactionRange")
		{
			std::getline(optionsFile, temp);
			interactionRange = atof(temp.c_str());
			std::cout << "      interactionRange = "
					<< interactionRange << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "interactionStrength")
		{
			std::getline(optionsFile, temp);
			interactionStrength = atof(temp.c_str());
			std::cout << "      interactionStrength = "
					<< interactionStrength << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "cohesionStrength")
		{
			std::getline(optionsFile, temp);
			cohesionStrength = atof(temp.c_str());
			std::cout << "      cohesionStrength = "
					<< cohesionStrength << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "quadraticStrength")
		{
			std::getline(optionsFile, temp);
			quadraticStrength = atof(temp.c_str());
			std::cout << "      quadraticStrength = "
					<< quadraticStrength << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "initialTemperature")
		{
			std::getline(optionsFile, temp);
			Temperature = atof(temp.c_str());
			std::cout << "      initialTemperature = "
					<< Temperature << std::endl;
			counter++;
		}

		std::getline(optionsFile, test, '=');
		if (test == "boundaryConditions")
		{
			std::getline(optionsFile, temp);
			boundaryConditions = temp;
			std::cout << "      bouncaryConditions = "
					<< boundaryConditions << std::endl;
			counter++;
		}
	}
	else
	{

		std::cout << "No Options File Found!!!" << std::endl;
		std::cout << std::endl << "   Using default values." << std::endl;

		setDefault();
		counter=-1;

	};

	if (counter==11 || counter==-1)
	{
		error=false;
		std::cout << std::endl
				<< "Options successfully set." << std::endl << std::endl;

	}
	else
	{
		std::cout << std::endl
				<< "      ***Error Loading Options!!!***" << std::endl;
		error=true;
	}
}

OptionsBin::~OptionsBin()
{

}

void OptionsBin::setDefault()
{
	jobName="DEFAULT";
	arraySize=100;
	initialGap=1;
	deltaGap=1;
	externalForce=0.5;
	interactionRange=10;
	interactionStrength=0.6;
	cohesionStrength=10;
	quadraticStrength=1;
	Temperature=100;
	boundaryConditions="Periodic";
}

