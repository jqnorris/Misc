/*
 * Data.h
 *
 *  Created on: Dec 7, 2012
 *      Author: jqnorris
 */

#ifndef DATA_H_
#define DATA_H_

#include "../includes/includes.h"

class Data {
public:
	Data(PoreArray &, Matrix &, Options &, Simulation &);
	virtual ~Data();
	PoreArray & pores;
	Matrix & matrix;
	Options & options;
	Simulation & simulation;
	void writeInvasion();
	void initialize();
};

#endif /* DATA_H_ */
