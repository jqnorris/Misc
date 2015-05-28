/*
 * Lattice.cpp
 *
 *  Created on: Feb 5, 2014
 *      Author: jqnorris
 */

#include "Lattice.h"
#include <algorithm>
#include <list>
#include <set>

Lattice::Lattice()
{
	L = 10;
	p_cutoff = 0.5;
}

Lattice::~Lattice()
{

}

//Lattice::Substructure::index<Lattice::strength>::type::index & Lattice::operator[] (const boost::tuple<int, int, int> id)
//{
//	return substructure.get<Lattice::strength>().find(id);
//}

Lattice::Substructure::index<Lattice::strength>::type & Lattice::by_strength()
{
	return substructure.get<Lattice::strength>();
}

Lattice::Substructure::index<Lattice::id>::type & Lattice::by_id()
{
	return substructure.get<Lattice::id>();
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
	substructure.get<id>().clear();

	for (int i = 0; i < L; i++)
	{
		for (int j = 0; j < L; j++)
		{
			for (int k = 0; k < 2; k++)
			{
				Bond new_bond(i, j, k);
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

struct new_cluster_number
{
	new_cluster_number(const int & new_number) :
			new_number(new_number)
	{
	}

	void operator()(Bond & bond)
	{
		bond.cluster_number = new_number;
	}

private:
	int new_number;
};

void Lattice::hoshen_kopelman()
{
	cluster_map[0] = 0;

	int next_cluster_number = 0;

	boost::tuple<int, int, int> up_id;
	boost::tuple<int, int, int> down_id;
	boost::tuple<int, int, int> left_id;
	boost::tuple<int, int, int> right_id;

	std::list<Substructure::index<id>::type::iterator> bonds_to_combine;

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

			if (by_id().find(up_id)->strength < p_cutoff)
			{
				bonds_to_combine.push_back(by_id().find(up_id));
				if (this_cluster_number == 0)
				{
					this_cluster_number = find_cluster_num(
							by_id().find(up_id)->cluster_number);
				}
			};
			if (by_id().find(down_id)->strength < p_cutoff)
			{
				bonds_to_combine.push_back(by_id().find(down_id));
				if (this_cluster_number != 0
						&& find_cluster_num(
								by_id().find(down_id)->cluster_number)
								< this_cluster_number)
				{
					this_cluster_number = find_cluster_num(
							by_id().find(down_id)->cluster_number);
				}
			};
			if (by_id().find(left_id)->strength < p_cutoff)
			{
				bonds_to_combine.push_back(by_id().find(left_id));
				if (this_cluster_number != 0
						&& find_cluster_num(
								by_id().find(left_id)->cluster_number)
								< this_cluster_number)
				{
					this_cluster_number = by_id().find(left_id)->cluster_number;
				}
			};
			if (by_id().find(right_id)->strength < p_cutoff)
			{
				bonds_to_combine.push_back(by_id().find(right_id));
				if (this_cluster_number != 0
						&& by_id().find(right_id)->cluster_number
								< this_cluster_number)
				{
					this_cluster_number =
							by_id().find(right_id)->cluster_number;
				}
			};

			if (bonds_to_combine.size() > 0 && this_cluster_number == 0)
			{
				cluster_map.insert(
						std::make_pair(next_cluster_number,
								next_cluster_number));
				this_cluster_number = next_cluster_number++;

			}

			std::list<Substructure::index<id>::type::iterator>::iterator iter;
			for (iter = bonds_to_combine.begin();
					iter != bonds_to_combine.end(); iter++)
			{
				by_id().modify((*iter),
						new_cluster_number(this_cluster_number));
			}
		}
	}

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

void Lattice::invade()
{

}

