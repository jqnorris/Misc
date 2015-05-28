/*
 * simulation.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: jqnorris
 */

#include "Lattice.h"
#include <iostream>

int main(int arc, char **argv)
{
	Lattice lattice;

	lattice.set_size(100);
	lattice.populate();

	// std::cout << lattice.by_id().find(boost::make_tuple(5, 5, 1))->strength << "\n";


	return 0;
}

