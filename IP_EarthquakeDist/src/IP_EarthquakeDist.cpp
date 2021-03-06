// IP_Clusters3.cpp : Defines the entry point for the console application.
//

#include <deque>
#include <map>
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>
#include <exception>
#include <algorithm>

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
	double bond_failure_time[2];
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
		bond_failure_time[0] = -1;
		bond_failure_time[1] = -1;
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
double p = 0.5;
double tau_short = 0.5*pow(10, -5);
double tau_long = 1;
double beta_short = 8;
double beta_long = 2;

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

double get_failure_time(Bond bond)
{
	Site pos = bond.first;
	short int direction = bond.second;
	if(direction < 2)
	{
		return lattice[pos].bond_failure_time[direction];
	}

	return lattice[get_end(bond)].bond_failure_time[direction-2];
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

double get_time_to_failure(Bond bond)
{
	if (get_strength(bond) > p)
	{
		//	if (boost_drand48() > p)
		//	{
		//return tau_long*pow(-log(1-boost_drand48()), 1.0/beta_long);
		return tau_long;
	}
	// return tau_short*pow(-log(1-boost_drand48()), 1.0/beta_short);
	return tau_short;
}

void add_new_Bonds(Site & inv_site, double current_time)
{
	Bond new_bond;
	for(short int dir=0; dir < 4; dir++)
	{
		new_bond = std::make_pair(inv_site, dir);
		if (lattice.count(get_end(new_bond)) >> 0)
		{
			double new_failure_time = current_time+get_time_to_failure(new_bond);
			if(!lattice.at(get_end(new_bond)).is_invaded && new_failure_time < p)
			{
				short int direction = new_bond.second;
				if(direction < 2)
				{
					lattice[inv_site].bond_failure_time[direction] = new_failure_time;
				}
				else
				{
					lattice[get_end(new_bond)].bond_failure_time[direction-2] = new_failure_time;
				}
				accessible_Bonds.insert(std::make_pair(new_failure_time, new_bond));
			}
		}		
	}
}

unsigned int burstIter = 1;
bool invade_bond(double current_time, Bond & inv_bond)
{
	Site inv_site = get_end(inv_bond);
	if (lattice.at(inv_site).is_invaded)
	{
		trappedBonds.push_back(inv_bond);
		return true;
	}
	else
	{
		if ( get_strength(inv_bond) < p)
		{
			lattice.at(inv_bond.first).burstN[inv_bond.second] = burstIter;
		}
		else
		{
			burstIter++;
		}
		cluster.push_back(inv_bond);
		lattice.at(inv_site).is_invaded = true;
		add_new_Bonds(inv_site, current_time);
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

long int generate_burst(short int L, short int W)
{
	short int j, k;
	long int cluster_size;
	bool already_invaded;

	for(j=-W/2; j < W/2; j++)
	{
		for(k=-L/2+1; k < L/2+1; k++)
		{
			Site loc = std::make_pair(j, k);
			unitCell_Square cell;
			lattice.insert(std::make_pair(loc, cell));
		}
	}

	Site start = std::make_pair(0,0);
	lattice[start].is_invaded = true;
	add_new_Bonds(start, 0);
	try
	{
		while(accessible_Bonds.size() > 0 )
		{
			std::multimap<double, Bond>::iterator weakest;
			weakest = accessible_Bonds.begin();
			already_invaded = invade_bond(weakest->first, weakest->second);
			accessible_Bonds.erase(weakest);
		}
		std::multimap<double, Bond>::iterator weakest = accessible_Bonds.begin();
		cluster.push_back(weakest->second);
	}
	catch (std::exception& e) {}

	cluster_size = cluster.size();

	lattice.clear();
	cluster.clear();

	return cluster_size;

}

int main(int argc, char **argv)
{
	long int i;
	short int W, L, aspect_ratio;
	L = atoi(argv[1]);
	aspect_ratio = atoi(argv[2]);
	p = atof(argv[3]);
	long int num_runs = atoi(argv[4]);
	W = L * aspect_ratio;
	std::map<int, long int> burst_sizes;
	std::map<int, long int>::iterator iSizes;

	int burst_size;

	for(i=0; i < num_runs; i++)
	{
		burst_size = generate_burst(L, W);
		if(burst_sizes.count(burst_size) > 0)
		{
			burst_sizes[burst_size] = burst_sizes[burst_size]+1;
		}
		else
		{
			burst_sizes.insert(std::make_pair(burst_size, 1));
		}
	}

	std::ofstream toFile("burstSizes.txt", std::ios::trunc);

	toFile << burst_sizes.size() << "\n";
	toFile << "p=\t" << p << "\n";

	for(iSizes = burst_sizes.begin(); iSizes != burst_sizes.end(); iSizes++)
	{
		toFile << iSizes->first << "\t";
		toFile << iSizes->second << "\n";
	}

	return 0;
}

