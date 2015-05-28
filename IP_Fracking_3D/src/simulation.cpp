/*
 * main.cpp
 *
 *  Created on: May 20, 2013
 *      Author: jqnorris
 */

#include <map>
#include <set>
#include <deque>
#include <stdlib.h>
#include <fstream>
#include "boost/tuple/tuple_io.hpp"
#include "boost/tuple/tuple_comparison.hpp"

typedef boost::tuple<int, int, int> Site;
typedef std::set<Site> SiteList;
typedef std::pair<double, std::pair<Site, Site> > Bond;
typedef std::multimap<double, Bond> BondMap;


SiteList    invadedSites;
BondMap     accessibleBonds;
std::deque<Bond> growth;
std::deque<Bond> trapped;

Site get_neighbor(Site pos, unsigned int direction)
{
	switch (direction)
	{
	case 0: // up
		return boost::make_tuple(pos.get<0>(), pos.get<1>(), pos.get<2>()+1);
	case 1: // down
		return boost::make_tuple(pos.get<0>(), pos.get<1>(), pos.get<2>()-1);
	case 2: // left
		return boost::make_tuple(pos.get<0>()+1, pos.get<1>(), pos.get<2>());
	case 3: // right
		return boost::make_tuple(pos.get<0>()-1, pos.get<1>(), pos.get<2>());
	case 4: // front
		return boost::make_tuple(pos.get<0>(), pos.get<1>()+1, pos.get<2>());
	case 5: // back
		return boost::make_tuple(pos.get<0>(), pos.get<1>()-1, pos.get<2>());
	}
}

double get_new_strength(int dir)
{
	if(dir == 2 || dir ==3)
	{
		return drand48()*0.5;
	}
	if(dir == 4 || dir ==5)
	{
		return drand48()*0.25;
	}
	return drand48();
}

bool invade_bond(Bond & inv_bond)
{
	Site invSite = inv_bond.second.second;
	if (invadedSites.count(invSite) > 0){
		trapped.push_back(inv_bond);
		return true;
	}


	double newStrength;
	Site newNeighbor;
	Bond newBond;
	growth.push_back(inv_bond);
	invadedSites.insert(invSite);
	for (int dir=0;dir<6;++dir)
	{
		newNeighbor = get_neighbor(invSite, dir);
		if (invadedSites.count(newNeighbor) == 0)
		{
			newStrength = get_new_strength(dir);
			newBond = std::make_pair(newStrength, std::make_pair(invSite, newNeighbor));
			accessibleBonds.insert(std::make_pair(newStrength, newBond));
		}
	}
	return false;
}


int main(int argc, char **argv)
{
	long int i, N;
	bool already_invaded;

	N = atoi(argv[1]);
	srand48(time(NULL));

	Site start = boost::make_tuple(0, 0, 0);
	invadedSites.insert(start);
	for (int neigh=0; neigh<6; neigh++)
	{
		Bond newBond;
		double newStrength = drand48();
		newBond = std::make_pair(newStrength, std::make_pair(start, get_neighbor(start, neigh)));
		accessibleBonds.insert(std::make_pair(newStrength, newBond));
	}

	for (i=0; i<N;)
	{
		BondMap::iterator weakest;
		weakest = accessibleBonds.begin();
		already_invaded = invade_bond(weakest->second);
		if(!already_invaded)
		{
			i++;
		}
		accessibleBonds.erase(weakest);
	}

	std::ofstream toFile1("fractures.txt", std::ios::trunc);
	std::ofstream toFile2("trapped.txt", std::ios::trunc);
	toFile1 << growth.size() << "\n";
	toFile2 << trapped.size() << "\n";
	toFile1 << "Invasion for: temp" << "\n";
	toFile2 << "Trapping for: temp" << "\n";
	toFile1.precision(17);
	toFile2.precision(17);

	Bond current_Line;
	std::multimap<unsigned int, Bond> bursts;
	unsigned int burst_number = 0;
	double cutoff = 0.1;
	bool bursting = false;
	while (!growth.empty())
	{
		current_Line = growth.front();
		growth.pop_front();
		toFile1 <<  current_Line.first << "\t";
		toFile1 <<  current_Line.second.first.get<0>() << "\t";
		toFile1 <<  current_Line.second.first.get<1>() << "\t";
		toFile1 <<  current_Line.second.first.get<2>() << "\t";
		toFile1 <<  current_Line.second.second.get<0>() << "\t";
		toFile1 <<  current_Line.second.second.get<1>() << "\t";
		toFile1 <<  current_Line.second.second.get<2>() << "\t";

		if(bursting && current_Line.first < cutoff)
		{
			toFile1 << burst_number << "\n";
		}
		else
		{
			if(bursting)
			{
				toFile1 << burst_number << "\n";
				burst_number += 1;
			}
			else
			{
				toFile1 << burst_number << "\n";
				bursting = true;
			};
		};

	}


	while (!trapped.empty())
	{
		current_Line = trapped.front();
		trapped.pop_front();
		toFile2 <<  current_Line.first << "\t";
		toFile2 <<  current_Line.second.first.get<0>() << "\t";
		toFile2 <<  current_Line.second.first.get<1>() << "\t";
		toFile2 <<  current_Line.second.first.get<2>() << "\t";
		toFile2 <<  current_Line.second.second.get<0>() << "\t";
		toFile2 <<  current_Line.second.second.get<1>() << "\t";
		toFile2 <<  current_Line.second.second.get<2>() << "\n";
	}

	toFile1.close();
	toFile2.close();

	return 0;
}



