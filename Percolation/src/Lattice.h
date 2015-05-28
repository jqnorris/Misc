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
#include <deque>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/composite_key.hpp>

class Lattice
{
private:

	struct Strength_tag
	{
	};

	struct Id_tag
	{
	};

	struct Perimeter_tag
	{
	};

	typedef boost::multi_index_container<Bond,
			boost::multi_index::indexed_by<
					// sort by strength
					boost::multi_index::ordered_non_unique<
							boost::multi_index::tag<Strength_tag>,
							boost::multi_index::member<Bond, double,
									&Bond::strength> >,
					// sort by id
					boost::multi_index::ordered_unique<
							boost::multi_index::tag<Id_tag>,
							boost::multi_index::member<Bond,
									boost::tuple<int, int, int>, &Bond::id> >,
					boost::multi_index::ordered_non_unique<
						boost::multi_index::tag<Perimeter_tag>,
						boost::multi_index::composite_key<Bond,
							boost::multi_index::member<Bond, bool, &Bond::in_perimeter>,
							boost::multi_index::member<Bond, double, &Bond::strength> > > > > Substructure;

	typedef Substructure::index<Strength_tag>::type Lattice_by_strength;

	typedef Substructure::index<Id_tag>::type Lattice_by_id;

	typedef Lattice::Substructure::index<Lattice::Id_tag>::type::iterator Element;

	typedef boost::tuple<int, int, int> Bond_id;

	int L;
	double p_cutoff;
	Substructure substructure;

	Lattice_by_strength & by_strength();
	Lattice_by_id & by_id();
	double get_new_strength();

	int find_cluster_num(int);
	int combine_cluster_nums(int, int);
	int hk_check_bond(Bond_id, int);
	std::map<int, int> cluster_map;
	std::map<int, int> cluster_sizes;

	struct change_strength
	{
		change_strength(double new_strength) :
				new_strength(new_strength)
		{
		}

		void operator()(Bond & bond)
		{
			bond.strength = new_strength;
		}

	private:
		double new_strength;
	};

	struct change_is_opened
	{
		change_is_opened(double new_is_opened) :
				new_is_opened(new_is_opened)
		{
		}

		void operator()(Bond & bond)
		{
			bond.strength = new_is_opened;
		}

	private:
		double new_is_opened;
	};

	struct change_cluster_number
	{
		change_cluster_number(double new_cluster_number) :
				new_cluster_number(new_cluster_number)
		{
		}

		void operator()(Bond & bond)
		{
			bond.cluster_number = new_cluster_number;
		}

	private:
		double new_cluster_number;
	};

	std::deque<Bond_id> invasion;
	std::deque<Bond_id> trapped;
	void invade_bond(Bond_id, bool);
	Bond_id get_good_id(Bond_id, bool);

public:
	Lattice();
	virtual ~Lattice();

	void set_size(int);
	int get_size();

	void set_p_cutoff(int);
	int get_p_cutoff();

	Element & operator[](const boost::tuple<int, int, int>);

	double get_strength(Bond_id);
	void set_strength(Bond_id, double);

	bool get_is_opened(Bond_id);
	void set_is_opened(Bond_id, bool);

	int get_cluster_number(Bond_id);
	void set_cluster_number(Bond_id, int);

	// Cluster Methods
	void populate();
	void hoshen_kopelman();
	void clear_clusters();

	// Invasion Methods
	void prep_invasion();


};

#endif /* LATTICE_H_ */
