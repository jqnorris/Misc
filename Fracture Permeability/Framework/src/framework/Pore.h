/*
 * Pore.h
 *
 *  Created on: Nov 29, 2012
 *      Author: jqnorris
 */

#ifndef PORE_H_
#define PORE_H_

class Rock;

class Pore {
public:
	Pore();
	virtual ~Pore();
	float naturalVolume;
	float currentVolume;
	float deltaVolume;
	float pressure;
	int flowPaths;
	Rock ** neighbors;
};

#endif /* PORE_H_ */
