/*
 * simulation.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: jqnorris
 */

#include "Lattice.h"
#include <iostream>
#include <time.h>

int main(int arc, char **argv)
{
	time_t start, end;

	start = time(NULL);

	Lattice lattice;

	lattice.set_size(50);
	lattice.set_p_cutoff(0.5);
	lattice.populate();

	lattice.hoshen_kopelman();

	std::cout << (lattice[boost::make_tuple(1, 1, 1)]->cluster_number) << std::endl;

	std::cout << lattice.get_strength(boost::make_tuple(1, 1, 1)) << std::endl;

	std::cout << lattice.get_is_opened(boost::make_tuple(1, 1, 1)) << std::endl;

	std::cout << lattice.get_cluster_number(boost::make_tuple(1, 1, 1)) << std::endl;

	lattice.set_strength(boost::make_tuple(1, 1, 1), 0.5);

	std::cout << lattice.get_strength(boost::make_tuple(1, 1, 1)) << std::endl;

	end = time(NULL);

	double time = difftime(end, start);

	std::cout << time << std::endl;

	return 0;
}

