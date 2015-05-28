/*
 * Options.h
 *
 *  Created on: Nov 29, 2012
 *      Author: jqnorris
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <string>

class Options {
public:
	Options();
	virtual ~Options();
	std::string jobName;
	int N;
	float v0;
	float phi0;
	float k0;
	float epsilonY0;
	float E0;
	int latticeType;
	float deltaV0;
	bool error;
	int timeSteps;
	void loadFromFile();
	void setDefault();
};

#endif /* OPTIONS_H_ */
