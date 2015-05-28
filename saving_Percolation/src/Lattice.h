/*
 * Lattice.h
 *
 *  Created on: Feb 5, 2014
 *      Author: jqnorris
 */

#ifndef LATTICE_H_
#define LATTICE_H_

#include "Bond.h"
#include <map>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>

class Lattice
{
private:
	struct strength
	{
	};

	struct id
	{
	};

	typedef boost::multi_index_container<Bond,
			boost::multi_index::indexed_by<
					// sort by less<string> on name
					boost::multi_index::ordered_non_unique<
							boost::multi_index::tag<strength>,
							boost::multi_index::member<Bond, double,
									&Bond::strength> >,
					boost::multi_index::ordered_unique<
							boost::multi_index::tag<id>,
							boost::multi_index::member<Bond,
									boost::tuple<int, int, int>, &Bond::id> > > > Substructure;

	Substructure substructure;
	int find_cluster_num(int);
	int combine_cluster_nums(int, int);
	Substructure::index<strength>::type & by_strength();
	Substructure::index<id>::type & by_id();
	std::map<int, int> cluster_map;
	short int L;
	double p_cutoff;
	std::map<int, int> cluster_sizes;
	Lattice::Substructure::index<Lattice::strength>::type::iterator & operator[](
				const boost::tuple<int, int, int>);

public:
//	typedef boost::tuple<int, int, int> id;

	Lattice();
	virtual ~Lattice();

	// Class Data Members

	// Class Method Members:


	// Basic Methods
	void set_size(int);
	int get_size();

	double get_strength_of(boost::tuple<int, int, int>);
	void set_strength_of();

	int get_cluster_number_of();

	// Cluster Methods
	void populate();
	void hoshen_kopelman();
	void clear_clusters();

	// Invasion Methods
	void prep_invasion();
	void invade();
	void invade(int);

};

#endif /* LATTICE_H_ */
