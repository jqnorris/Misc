/*
 * Lattice.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: jqnorris
 */

#include "Lattice.h"
#include <algorithm>
#include "CC_Rand48.h"
#include <iostream>

Lattice::Lattice()
{
	L = 10;
	p_cutoff = 0.5;
}

Lattice::~Lattice()
{

}

Lattice::Element & Lattice::operator[](
		const boost::tuple<int, int, int> this_one)
{
	static Element test = substructure.get<Lattice::Id_tag>().find(
			boost::make_tuple(0, 0, 0));
	test = substructure.get<Lattice::Id_tag>().find(this_one);
	return test;
}

Lattice::Substructure::index<Lattice::Strength_tag>::type & Lattice::by_strength()
{
	return substructure.get<Lattice::Strength_tag>();
}

Lattice::Substructure::index<Lattice::Id_tag>::type & Lattice::by_id()
{
	return substructure.get<Lattice::Id_tag>();
}

/* Basic Methods
 */

void Lattice::set_size(int l)
{
	L = l;
}

int Lattice::get_size()
{
	return L;
}

/* Cluster Methods
 */

void Lattice::populate()
{
	substructure.get<Id_tag>().clear();

	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Bond new_bond(i, j, k, get_new_strength());
				substructure.insert(new_bond);
			}
		}
	}
}

int Lattice::find_cluster_num(int cluster_num)
{
	int min_num = cluster_num;
	while (cluster_map[min_num] != min_num)
	{
		min_num = cluster_map[min_num];
	}

	while (cluster_map[cluster_num] != cluster_num)
	{
		int next_num = cluster_map[cluster_num];
		cluster_map[cluster_num] = min_num;
		cluster_num = next_num;
	}

	return min_num;
}

int Lattice::combine_cluster_nums(int cluster_0, int cluster_1)
{
	int min_num;
	int max_num;
	if (cluster_0 != cluster_1)
	{
		min_num = std::min(find_cluster_num(cluster_0),
				find_cluster_num(cluster_1));
		max_num = std::max(find_cluster_num(cluster_0),
				find_cluster_num(cluster_1));
		cluster_map[max_num] = min_num;
	}
	else
	{
		min_num = find_cluster_num(cluster_0);
	};

	return min_num;
}

void Lattice::hoshen_kopelman()
{
	cluster_map[0] = 0;

	boost::tuple<int, int, int> up_id;
	boost::tuple<int, int, int> down_id;
	boost::tuple<int, int, int> left_id;
	boost::tuple<int, int, int> right_id;

	int this_cluster_number = 0;

	for (int i = 1; i < L; i++)
	{
		for (int j = 1; j < L; j++)
		{
			up_id = boost::make_tuple(i, j, 1);
			down_id = boost::make_tuple(i, j - 1, 1);
			left_id = boost::make_tuple(i - 1, j, 0);
			right_id = boost::make_tuple(i, j, 0);

			this_cluster_number = 0;

			this_cluster_number = hk_check_bond(up_id, this_cluster_number);
			this_cluster_number = hk_check_bond(down_id, this_cluster_number);
			this_cluster_number = hk_check_bond(left_id, this_cluster_number);
			this_cluster_number = hk_check_bond(right_id, this_cluster_number);

		}
	}

	Element bond, end;
	int temp_cluster_number;
	for (bond = by_id().begin(), end = by_id().end(); bond != end; bond++)
	{
		temp_cluster_number = bond->cluster_number;
		if (cluster_map[temp_cluster_number] != temp_cluster_number)
		{
			temp_cluster_number = find_cluster_num(bond->cluster_number);
			set_cluster_number(bond->id, temp_cluster_number);

			if (cluster_sizes.count(temp_cluster_number) == 0)
			{
				cluster_sizes.insert(std::make_pair(temp_cluster_number, 1));
			}
			else
			{
				cluster_sizes[temp_cluster_number]++;
			}
		}
	}
}

int Lattice::hk_check_bond(Bond_id id, int cluster_number)
{
	static int new_cluster_number = 1;
	int this_cluster_number = cluster_number;

	if (get_strength(id) < p_cutoff)
	{
		this_cluster_number = find_cluster_num(get_cluster_number(id));

		if (cluster_number == 0 && this_cluster_number == 0)
		{
			this_cluster_number = new_cluster_number++;
			cluster_map.insert(
					std::make_pair(this_cluster_number, this_cluster_number));
			set_cluster_number(id, this_cluster_number);

			return this_cluster_number;
		}

		if (cluster_number != 0 && this_cluster_number == 0)
		{
			set_cluster_number(id, cluster_number);

			return cluster_number;
		}

		if (cluster_number != 0 && this_cluster_number != 0)
		{
			return combine_cluster_nums(cluster_number, this_cluster_number);
		}
	}

	return this_cluster_number;
}

void Lattice::clear_clusters()
{
	cluster_map.clear();
	cluster_sizes.clear();

}

/* Invasion Methods
 */

void Lattice::prep_invasion()
{

}

double Lattice::get_strength(Bond_id id)
{
	return (*this)[id]->strength;
}

void Lattice::set_strength(Bond_id id, double strength)
{
	by_id().modify((*this)[id], change_strength(strength));
}

bool Lattice::get_is_opened(Bond_id id)
{
	return (*this)[id]->is_opened;
}
void Lattice::set_is_opened(Bond_id id, bool is_opened)
{
	by_id().modify((*this)[id], change_is_opened(is_opened));
}

int Lattice::get_cluster_number(Bond_id id)
{
	return (*this)[id]->cluster_number;
}

void Lattice::set_cluster_number(Bond_id id, int cluster_number)
{
	by_id().modify((*this)[id], change_cluster_number(cluster_number));
}

void Lattice::set_p_cutoff(int p_input)
{
	p_cutoff = p_input;
}

int Lattice::get_p_cutoff()
{
	return p_cutoff;
}

double Lattice::get_new_strength()
{
	return cc_drand48();
}

void Lattice::prep_invasion()
{



}

void Lattice::invade_bond(Bond_id bond, bool reverse)
{
	static int this_burst_number = 0;

	Bond_id good_id;

	if (bond.get<2>())
	{
		if (bond.get<2>() == 0)
		{
			good_id = boost::make_tuple(bond.get<0>(), bond.get<1>(), 0);
		}
		if (bond.get<2>() == 0)
		{
			good_id = boost::make_tuple(bond.get<0>(), bond.get<1>(), 1);
		}
	}
}

