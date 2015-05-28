/*
 * OptionsBin.h
 *
 *  Created on: Sep 25, 2012
 *      Author: jqnorris
 */

#ifndef OPTIONSBIN_H_
#define OPTIONSBIN_H_

#include <string>
#include <vector>

class OptionsBin
{

public:
	OptionsBin();
	OptionsBin(bool loadFile); // Constructor that loads options file
								// or sets defaults
	virtual ~OptionsBin();
	void setDefault();
	std::string jobName; // A name for the current job
	int arraySize; // This is Z for an ZxZ array
	double initialGap; // The initial value of \zeta
	double deltaGap;	// ???
	double externalForce; // The force applied, p
	int interactionRange; // How far to include neighbors(which j's to sum over)
	double interactionStrength; // The strength of interaction, G(i,j)=G
	double cohesionStrength; // The "bond" strength, \gamma
	double quadraticStrength; // Quadratic coefficient, b
								//(keeps the fracture from running away)
	double Temperature; // Initial temperature for statistics
	bool error; // Used for keeping track of loading errors
	std::string boundaryConditions; // Linear, Periodic, etc.

};

#endif /* OPTIONSBIN_H_ */
