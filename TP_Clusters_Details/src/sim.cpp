/*
 * sim.cpp
 *
 *  Created on: Dec 2, 2013
 *      Author: jqnorris
 */

#include <deque>
#include <map>
#include <set>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>
#include <exception>
#include <algorithm>
#include <iostream>

#ifdef _WIN32
//  Windows
#define rdtsc  __rdtsc

#else
//  For everything else
unsigned long long rdtsc(){
	unsigned int lo,hi;
	__asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
	return ((unsigned long long)hi << 32) | lo;
}
#endif

boost::rand48 rng(static_cast<unsigned int>(rdtsc()));
//boost::rand48 rng(static_cast<unsigned int>(12));
boost::uniform_01<boost::rand48> boost_drand48(rng);

typedef std::pair<short int,short int> Site;
typedef std::pair<Site, short int> Bond;

class unitCell_Square
{
public:
	bool is_invaded;
	bool is_open[2];
	double bonds[2];
	unsigned int clusterN;
	unsigned int burstN[2];
	unitCell_Square(void)
	{
		bonds[0] = boost_drand48();
		bonds[1] = boost_drand48();
		is_invaded = false;
		is_open[0] = false;
		is_open[1] =false;
		clusterN = 0;
		burstN[0] = 0;
		burstN[1] = 0;
	};
};


std::map<Site, unitCell_Square> lattice;
typedef std::map<Site, unitCell_Square>::iterator lattice_iterator;
typedef std::pair<unsigned int, Site> cluster_seed;
std::multimap<double, Bond> accessible_Bonds;
std::deque<Bond> cluster;
std::deque<Bond> trappedBonds;
std::map<unsigned int, cluster_seed> cluster_map;
unsigned int new_cluster_number = 1;
double pc = 0.49;

Site get_end(Bond bond)
{
	Site pos = bond.first;
	short int direction = bond.second;
	switch (direction)
	{
	case 0: // down
		return std::make_pair(pos.first, pos.second-1);
	case 1: // right
		return std::make_pair(pos.first+1, pos.second);
	case 2: // up
		return std::make_pair(pos.first, pos.second+1);
	case 3: // left
		return std::make_pair(pos.first-1, pos.second);
	default:
		return std::make_pair(0,0);
	}
}

double get_strength(Bond bond)
{
	Site pos = bond.first;
	short int direction = bond.second;
	if(direction < 2)
	{
		return lattice[pos].bonds[direction];
	}

	return lattice[get_end(bond)].bonds[direction-2];
}

void add_new_Bonds(Site & inv_site)
{
	Bond new_bond;
	for(short int dir=0; dir < 4; dir++)
	{
		new_bond = std::make_pair(inv_site, dir);
		if(!lattice.at(get_end(new_bond)).is_invaded)
		{
			accessible_Bonds.insert(std::make_pair(get_strength(new_bond), new_bond));
		}
	}
}

unsigned int burstIter = 1;
bool invade_bond(double strength, Bond & inv_bond)
{
	Site inv_site = get_end(inv_bond);
	if (lattice.at(inv_site).is_invaded)
	{
		trappedBonds.push_back(inv_bond);
		return true;
	}
	else
	{
		if ( strength < pc)
		{
			lattice.at(inv_bond.first).burstN[inv_bond.second] = burstIter;
		}
		else
		{
			burstIter++;
		}
		cluster.push_back(inv_bond);
		lattice.at(inv_site).is_invaded = true;
		add_new_Bonds(inv_site);
	}
	return false;
}

unsigned int find(unsigned int x)
{
	unsigned int y = x;
	while(cluster_map[y].first != y)
	{
		y = cluster_map[y].first;
	}

	while(cluster_map[x].first != x)
	{
		unsigned int z = cluster_map[x].first;
		cluster_map[x].first = y;
		x = z;
	}
	return y;
}

unsigned int combine(unsigned int x, unsigned int y)
{
	unsigned int w = std::max(find(x), find(y));
	unsigned int z = std::min(find(x), find(y));
	return cluster_map[w].first = z;
}


bool grow_clusters(Bond bond)
{
	unsigned int one = find(lattice[bond.first].clusterN);
	unsigned int two;
	Site random_end;
	if(lattice.count(get_end(bond)) > 0)
	{
		two = find(lattice[get_end(bond)].clusterN);
	}
	else
	{
		two = -1;
	}
	if(two == -1)
	{
		if(one == 0)
		{
			if(boost_drand48() < 0.5)
			{
				random_end = bond.first;
			}
			else
			{
				random_end = get_end(bond);
			}
			cluster_map[new_cluster_number] = std::make_pair(new_cluster_number, random_end);
			lattice[bond.first].clusterN = new_cluster_number;
			new_cluster_number++;
		}
		return true;
	}
	if( (one != two || one == 0))
	{
		switch(!!one + !!two)
		{
		case 0:
			if(boost_drand48() < 0.5)
			{
				random_end = bond.first;
			}
			else
			{
				random_end = get_end(bond);
			}
			cluster_map[new_cluster_number] = std::make_pair(new_cluster_number, random_end);
			lattice[bond.first].clusterN = new_cluster_number;
			lattice[get_end(bond)].clusterN = lattice[bond.first].clusterN;
			new_cluster_number++;
			return true;
		case 1:
			lattice[bond.first].clusterN = std::max(one, two);
			lattice[get_end(bond)].clusterN = std::max(one, two);
			return true;
		case 2:
			lattice[bond.first].clusterN = combine(one, two);
			lattice[get_end(bond)].clusterN = lattice[bond.first].clusterN;
			return true;
		}
	}
	return false;
}

int main(int argc, char **argv)
{
	short int L, j, k, l;
	L = atoi(argv[1]);
	pc = atof(argv[2]);

	std::cout << pc << std::endl;


	for(j=-L/2; j < L/2; j++)
	{
		for(k=-L/2+1; k < L/2+1; k++)
		{
			Site loc = std::make_pair(j, k);
			unitCell_Square cell;
			lattice.insert(std::make_pair(loc, cell));
		}
	}

	for(j=-L/2; j < L/2; j++)
	{
		for(k=-L/2+1; k < L/2+1; k++)
		{
			for(l=0; l<2; l++)
			{
				Site loc = std::make_pair(j, k);
				Bond bond = std::make_pair(loc, l);
				accessible_Bonds.insert(std::make_pair(lattice[loc].bonds[l], bond));
			}
		}
	}

	std::multimap<double, Bond>::iterator weakest = accessible_Bonds.begin();
	while(weakest->first < pc  && accessible_Bonds.size() > 1)
	{
		lattice[weakest->second.first].is_open[weakest->second.second] = grow_clusters(weakest->second);
		accessible_Bonds.erase(weakest);
		weakest = accessible_Bonds.begin();
	}


	unitCell_Square * current_cell;
	for(j=-L/2; j < L/2; j++)
	{
		for(k=-L/2+1; k < L/2+1; k++)
		{
			current_cell = &lattice[std::make_pair(j,k)];
			current_cell->clusterN = find(current_cell->clusterN);
		}
	}

	long int bond_count = 0;
	for(lattice_iterator iter = lattice.begin(); iter != lattice.end(); iter++)
	{
		current_cell = &iter->second;
		if(current_cell->is_open[0])
		{
			bond_count++;
		}
		if(current_cell->is_open[1])
		{
			bond_count++;
		}
	}


	unitCell_Square Line;
	Site begin;
	Site other_end;
	std::map<unsigned int, unsigned int> cluster_sizes;
	while (!lattice.empty())
	{
		begin = lattice.begin()->first;
		Line = lattice.begin()->second;
		lattice.erase(begin);
		if(Line.is_open[0])
		{
			if(cluster_sizes.count(Line.clusterN) > 0)
			{
				cluster_sizes[Line.clusterN]++;
			}
			else
			{
				cluster_sizes.insert(std::make_pair(Line.clusterN,1));
			}
		}
		if(Line.is_open[1])
		{
			if(cluster_sizes.count(Line.clusterN) > 0)
			{
				cluster_sizes[Line.clusterN]++;
			}
			else
			{
				cluster_sizes.insert(std::make_pair(Line.clusterN,1));
			}

		}
	}

	unsigned int largest_cluster = 0;
	unsigned int largest_cluster_size = 0;
	std::map<unsigned int, unsigned int>::iterator iter;
	for(iter = cluster_sizes.begin(); iter != cluster_sizes.end(); iter++)
	{
		if(iter->second > largest_cluster_size)
		{
			largest_cluster = iter->first;
			largest_cluster_size = iter->second;
		}
	}

	std::map<unsigned int, unsigned int> cluster_count;
	unsigned int size, begin2;
	while (!cluster_sizes.empty())
	{
		begin2 = cluster_sizes.begin()->first;
		size = cluster_sizes.begin()->second;
		cluster_sizes.erase(begin2);
		if(cluster_count.count(size) > 0)
		{
			cluster_count[size]++;
		}
		else
		{
			cluster_count.insert(std::make_pair(size, 1));
		}
	}

	std::ofstream toFile4("cluster_distribution.txt", std::ios::trunc);
	toFile4 << cluster_count.size() << "\n";

	unsigned int count;
	while (!cluster_count.empty())
	{
		size = cluster_count.begin()->first;
		count = cluster_count.begin()->second;
		cluster_count.erase(size);
		toFile4 << size << "\t" << count << "\n";
	}

	toFile4.close();




	return 0;
}






