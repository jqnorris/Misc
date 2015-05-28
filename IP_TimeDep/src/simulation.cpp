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
#include <cmath>
#include <iostream>

typedef std::pair<int, int> Site;
typedef std::set<Site> SiteList;
typedef std::pair<double, std::pair<Site, Site> > Bond;
typedef std::multimap<double, Bond> BondMap;


SiteList    invadedSites;
BondMap     accessibleBonds;
std::deque<Bond> growth;
std::deque<Bond> trapped;
double beta = 0.25;
double pc = 0.5;
double alpha =0.0000001;

double get_time(void)
{
	if (drand48() < pc)
	{
		return pow(-log(1-drand48()), 1.0/beta);
	}
	return 10^6;
}

Site get_neighbor(Site pos, unsigned int direction)
{
	switch (direction)
	{
	case 0: // up
		return std::make_pair(pos.first, pos.second+1);
	case 1: // down
		return std::make_pair(pos.first, pos.second-1);
	case 2: // left
		return std::make_pair(pos.first-1, pos.second);
	case 3: // right
		return std::make_pair(pos.first+1, pos.second);
	}
}

bool invade_bond(Bond & inv_bond, double cur_time)
{
	Site invSite = inv_bond.second.second;
	if (invadedSites.count(invSite) > 0){
		trapped.push_back(inv_bond);
		return true;
	}


	double newTime;
	Site newNeighbor;
	Bond newBond;
	growth.push_back(inv_bond);
	invadedSites.insert(invSite);
	for (int dir=0;dir<4;++dir)
	{
		newNeighbor = get_neighbor(invSite, dir);
		if (invadedSites.count(newNeighbor) == 0)
		{
			newTime = get_time()+cur_time;
			newBond = std::make_pair(newTime, std::make_pair(invSite, newNeighbor));
			accessibleBonds.insert(std::make_pair(newTime, newBond));
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

	Site start = std::make_pair(0, 0);
	invadedSites.insert(start);
	for (int neigh=0;neigh<4; neigh++)
	{
		Bond newBond;
		double newTime = get_time();
		newBond = std::make_pair(newTime, std::make_pair(start, get_neighbor(start, neigh)));
		accessibleBonds.insert(std::make_pair(newTime, newBond));
	}

	for (i=0; i<N;)
	{
		BondMap::iterator weakest;
		weakest = accessibleBonds.begin();
		already_invaded = invade_bond(weakest->second, weakest->first);
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
	while (!growth.empty())
	{
		current_Line = growth.front();
		growth.pop_front();
		toFile1 <<  current_Line.first << "\t";
		toFile1 <<  current_Line.second.first.first << "\t";
		toFile1 <<  current_Line.second.first.second << "\t";
		toFile1 <<  current_Line.second.second.first << "\t";
		toFile1 <<  current_Line.second.second.second << "\n";
	}


	while (!trapped.empty())
	{
		current_Line = trapped.front();
		trapped.pop_front();
		toFile2 <<  current_Line.first << "\t";
		toFile2 <<  current_Line.second.first.first << "\t";
		toFile2 <<  current_Line.second.first.second << "\t";
		toFile2 <<  current_Line.second.second.first << "\t";
		toFile2 <<  current_Line.second.second.second << "\n";
	}

	toFile1.close();
	toFile2.close();

	return 0;
}



