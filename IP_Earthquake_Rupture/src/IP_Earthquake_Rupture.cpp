// IP_Clusters3.cpp : Defines the entry point for the console application.
//

#include <deque>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>

// Obtaining a platform independent random number generator
//  Windows
#ifdef _WIN32
#define rdtsc  __rdtsc

//  For everything else
#else
unsigned long long rdtsc(){
    unsigned int lo,hi;
    __asm__ __volatile__ ("rdtsc" : "=a" (lo), "=d" (hi));
    return ((unsigned long long)hi << 32) | lo;
}
#endif

boost::rand48 rng(static_cast<unsigned int>(rdtsc()));
//boost::rand48 rng(static_cast<unsigned int>(12));
boost::uniform_01<boost::rand48> boost_drand48(rng);

typedef unsigned long int Site_index;
typedef std::pair<unsigned short int, unsigned short int> Site_coordinates;
typedef std::pair<Site_index, Site_index> Bond;
typedef bool Site;
std::multimap<double, Bond> accessible_bonds;
std::multimap<double, Bond>::iterator ab_iterator;
std::deque<std::pair<double, Bond> > ruptured_bonds;
std::deque<std::pair<double, Bond> > trapped_bonds;

double pc = 0.5;
double tau_short = 1;
double tau_long = 10;

unsigned long int  lattice_size;
unsigned short int lattice_height, lattice_length, lattice_aspect_ratio;
Site * lattice;

Site_index get_neighboring_site(Site_index current_index, short int direction)
{
	switch (direction)
	{
		case 0: // down
			return current_index+lattice_length;
		case 1: // right
			if((current_index+1) % lattice_length == 0)
			{
				return lattice_size;
			}
            return current_index+1;
		case 2: // up
			if(current_index < lattice_length)
			{
				return lattice_size;
			}
			else
			{
				return current_index-lattice_length;
			}
		case 3: // left
			if(current_index % lattice_length == 0)
			{
				return lattice_size;
			}
			else
			{
				return current_index-1;
			}
		default:
			return lattice_size;
    }
}

unsigned short int get_site_x (Site_index site)
{
	return site % lattice_length;
}

unsigned short int get_site_y (Site_index site)
{
	return lattice_height - (site/lattice_length + 1);
}

double get_new_time_to_failure()
{
	return tau_short;
}

void add_new_rupture_directions(double current_time, Site_index invaded_site)
{
	for(short int dir=0; dir < 4; dir++)
	{
		Site_index new_site = get_neighboring_site(invaded_site, dir);

		double new_time;

		if(new_site < lattice_size)
		{
			if(lattice[new_site] && boost_drand48() < 0.5)
			{
				new_time = current_time + get_new_time_to_failure();
				accessible_bonds.insert(std::make_pair(new_time, std::make_pair(invaded_site, new_site)));
			}

		}
	}

}

bool invade_bond(double current_time, Bond inv_bond)
{
	if (!(lattice[inv_bond.second]))
	{
		trapped_bonds.push_back(std::make_pair(current_time, inv_bond));
		return false;
	}
	else
	{
		ruptured_bonds.push_back(std::make_pair(current_time, inv_bond));
		lattice[inv_bond.second] = false;
		add_new_rupture_directions(current_time, inv_bond.second);
	}
    return true;
}

bool grow_rupture()
{
	if(accessible_bonds.size() > 0)
	{
		ab_iterator = accessible_bonds.begin();
		invade_bond(ab_iterator->first, ab_iterator->second);
		accessible_bonds.erase(ab_iterator);
		return true;
	}

	return false;
}

int main(int argc, char **argv)
{
	lattice_height = atoi(argv[1]);
	lattice_length = atoi(argv[2]);

	lattice_size = lattice_length * lattice_height;

	lattice = new Site[lattice_size];
	std::fill_n(lattice, lattice_size, true);

	Site_index rupture_initiation_site = lattice_size*boost_drand48();

	lattice[rupture_initiation_site] = false;

	add_new_rupture_directions(0, rupture_initiation_site);

	while(grow_rupture())
	{

	}


	std::ofstream toFile1("rupture.txt", std::ios::trunc);
	std::ofstream toFile2("trapped.txt", std::ios::trunc);
	toFile1 << ruptured_bonds.size() << "\t";
	if(ruptured_bonds.size() > 0)
	{
		toFile1 << ruptured_bonds.back().first << "\n";
	}
	else
	{
		toFile1 << 0 << "\n";
	}
	toFile2 << trapped_bonds.size() << "\n";
	toFile1 << "Rupture for: " << lattice_height << " by " << lattice_length << "\n";
	toFile2 << "Trapping for: " << lattice_height << " by " << lattice_length << "\n";
	toFile1 << get_site_x(rupture_initiation_site) << "\t" << get_site_y(rupture_initiation_site) << "\n";
	toFile2 << get_site_x(rupture_initiation_site) << "\t" << get_site_y(rupture_initiation_site) << "\n";
	toFile1.precision(17);
	toFile2.precision(17);

	std::pair<double, Bond>  current_Line;
	while (!ruptured_bonds.empty())
	{
		current_Line = ruptured_bonds.front();
		ruptured_bonds.pop_front();
		toFile1 << current_Line.first << "\t";
		toFile1 <<  get_site_x(current_Line.second.first) << "\t";
		toFile1 <<  get_site_y(current_Line.second.first) << "\t";
		toFile1 <<  get_site_x(current_Line.second.second) << "\t";
		toFile1 <<  get_site_y(current_Line.second.second) << "\n";
	}


	while (!trapped_bonds.empty())
	{
		current_Line = trapped_bonds.front();
		trapped_bonds.pop_front();
		toFile2 << current_Line.first << "\t";
		toFile2 <<  get_site_x(current_Line.second.first) << "\t";
		toFile2 <<  get_site_y(current_Line.second.first) << "\t";
		toFile2 <<  get_site_x(current_Line.second.second) << "\t";
		toFile2 <<  get_site_y(current_Line.second.second) << "\n";
	}

	toFile1.close();
	toFile2.close();

    return 0;
}

