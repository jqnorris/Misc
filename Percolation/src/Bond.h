/*
 * Bond.h
 *
 *  Created on: Feb 4, 2014
 *      Author: jqnorris
 */

#ifndef BOND_H_
#define BOND_H_

#include "boost/tuple/tuple_io.hpp"
#include "boost/tuple/tuple_comparison.hpp"

class Bond
{
public:
	Bond(int, int, int, double);
	virtual ~Bond();

	//Class Data Members
	double strength;
	boost::tuple<int, int, int> id;
	bool is_opened;
	int cluster_number;
	int burst_number;
	bool in_perimeter;
	bool is_invaded;
	bool is_trapped;

	//Class Method Members
	bool operator ==(const Bond & other) const;
	bool operator !=(const Bond & other) const;

};

#endif /* BOND_H_ */
