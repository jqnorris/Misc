/*
 * Bond.cpp
 *
 *  Created on: Feb 4, 2014
 *      Author: jqnorris
 */

#include "Bond.h"
#include "CC_Rand48.h"

Bond::Bond(int i, int j, int k)
{
	// Assign the bond a random strength
	strength = cc_drand48();
	id.get<0>() = i;
	id.get<1>() = j;
	id.get<2>() = k;
	opened = false;
	cluster_number = 0;
}

Bond::~Bond()
{

}

bool Bond::operator ==(const Bond & other) const
{
	bool strengths = (*this).strength == other.strength;
	bool ids = (*this).id == other.id;

	return strengths && ids;
}

bool Bond::operator !=(const Bond & other) const
{
	return !(*this == other);
}
