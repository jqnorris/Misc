// IP_Clusters3.cpp : Defines the entry point for the console application.
//

#include <deque>
#include <map>
#include <stdlib.h>
#include <fstream>
#include <boost/random.hpp>
#include <boost/random/linear_congruential.hpp>
#include <boost/timer/timer.hpp>

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
std::vector<std::pair<double, Bond> > ruptured_bonds;
std::vector<std::pair<double, Bond> > trapped_bonds;
std::multimap<double, Site_index> next_hypocenters_list;
std::multimap<double, Site_index>::iterator next_hypocenter;

double pc = 0.5;
double tau_short = 1;
double tau_long = 10;

unsigned long int  lattice_size;
unsigned short int lattice_height, lattice_length, lattice_aspect_ratio;
Site * lattice;

typedef unsigned long int Bond_index;

Bond_index get_bond_index(Bond site_indexes)
{
	Site_index smaller_site_index = std::min(site_indexes.first, site_indexes.second);

	if( abs(site_indexes.first - site_indexes.second) > 1)
	{
		return smaller_site_index;
	}

	return smaller_site_index + lattice_length*(lattice_height-1) - smaller_site_index/lattice_length;
}

double * bond_strength_table;

Bond get_bond_from_index(Bond_index index)
{
	if(index < lattice_length*(lattice_height-1))
	{
		return std::make_pair(index, index+lattice_length);
	}
	unsigned long int temp = index - lattice_length*(lattice_height-1);
	unsigned long int index_1 = temp+temp/(lattice_length-1);
	return std::make_pair(index_1, index_1+1);
}

double get_bond_strength(Bond this_bond)
{
	return bond_strength_table[get_bond_index(this_bond)];
}


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

unsigned int get_site_x (Site_index site)
{
	return site % lattice_length;
}

unsigned int get_site_y (Site_index site)
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
			if(lattice[new_site])
			{
				Bond this_bond = std::make_pair(invaded_site, new_site);
				if(get_bond_strength(this_bond) < pc)
				{
					new_time = current_time + get_new_time_to_failure();
					accessible_bonds.insert(std::make_pair(new_time, std::make_pair(invaded_site, new_site)));
				}
				else
				{
					next_hypocenters_list.insert(std::make_pair(get_bond_strength(this_bond), new_site));
					//					trapped_bonds.push_back(std::make_pair(new_time, std::make_pair(invaded_site, new_site)));
				}
			}

		}
	}

}

bool invade_bond(double current_time, Bond inv_bond)
{
	if (!(lattice[inv_bond.second]))
	{
		//		trapped_bonds.push_back(std::make_pair(current_time, inv_bond));
		return false;
	}
	else
	{
		//		ruptured_bonds.push_back(std::make_pair(current_time, inv_bond));
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

Site_index rupture_initiation_site;
std::vector<std::pair<double, Bond> >::iterator iterator;

void clean_up_rupture()
{
	lattice[rupture_initiation_site] = true;

	for(iterator= ruptured_bonds.begin(); iterator != ruptured_bonds.end(); iterator++)
	{
		lattice[iterator->second.second] = true;
		bond_strength_table[get_bond_index(iterator->second)] = 0.5+0.5*boost_drand48();
	}
	ruptured_bonds.clear();
}

unsigned long int number_of_bonds;

unsigned long int this_rupture_size;

bool prep_next_rupture()
{
	if(next_hypocenters_list.size() < 1)
	{
		return false;
	}

	next_hypocenter = next_hypocenters_list.begin();

	while(lattice[next_hypocenter->second] == false)
	{
		if(next_hypocenters_list.size() > 2)
		{

			next_hypocenters_list.erase(next_hypocenter);
			next_hypocenter = next_hypocenters_list.begin();
		}
		else
		{
			return false;
		}
	}
	next_hypocenters_list.erase(next_hypocenter);

	rupture_initiation_site = next_hypocenter->second;
	lattice[rupture_initiation_site] = false;
	add_new_rupture_directions(0, rupture_initiation_site);
	this_rupture_size = 0;
	return true;
}

bool quiet()
{
	unsigned long int this_one = number_of_bonds*boost_drand48();

	bond_strength_table[this_one] = bond_strength_table[this_one]-0.001;

	if(bond_strength_table[this_one] < 0)
	{
		Bond failed_bond = get_bond_from_index(this_one);

		Site_index random_end;
		if(boost_drand48() < 0.5)
		{
			random_end = failed_bond.first;
		}
		else
		{
			random_end = failed_bond.second;
		}
		rupture_initiation_site = random_end;
		lattice[rupture_initiation_site] = false;
		add_new_rupture_directions(0, rupture_initiation_site);

		return false;
	}


	return true;
}

class earthquake{
public:
	long unsigned int area;
	long unsigned int waiting_time;
	long unsigned int epicenter;
};

std::vector<earthquake> event_list;

std::map<unsigned long int, unsigned long int> rupture_sizes;


unsigned long int i;
unsigned long int waiting_time = 0;
earthquake this_one;

void record_rupture()
{
	if(rupture_sizes.count(this_rupture_size) > 0)
	{
		rupture_sizes[this_rupture_size]++;
	}
	else
	{
		rupture_sizes.insert(std::make_pair(this_rupture_size, 1));
	}

	this_one.epicenter = rupture_initiation_site;
	this_one.area = this_rupture_size;
	this_one.waiting_time = waiting_time;

	event_list.push_back(this_one);
}

void print_lattice()
{
	for(int i=0; i< lattice_size; i++)
	{
		std::cout << lattice[i] << " ";

		if((i+1)%lattice_length < 1)
		{
			std::cout << "\n";
		}
	}

	std::cout << "\n";
}

void prep_lattice()
{
	std::fill_n(lattice, lattice_size, true);
	for(unsigned long int i=0; i<number_of_bonds; i++)
	{
		bond_strength_table[i] = boost_drand48();
	}

	next_hypocenters_list.insert(std::make_pair(0,boost_drand48()*lattice_size));
	prep_next_rupture();
}

unsigned long int number_of_ruptures = 0;

void grow_ruptures()
{
	while(grow_rupture())
	{
		this_rupture_size++;
	}


	record_rupture();


	while(prep_next_rupture())
	{
		while(grow_rupture())
		{
			this_rupture_size++;
		}
		record_rupture();
		number_of_ruptures++;
	}

}

int main(int argc, char **argv)
{
	boost::timer::auto_cpu_timer t;

	lattice_height = atoi(argv[1]);
	lattice_length = atoi(argv[2]);
	unsigned long int number_of_realizations = atoi(argv[3]);

	lattice_size = lattice_length * lattice_height;
	number_of_bonds = lattice_size+lattice_size-lattice_length-lattice_height;

	lattice = new Site[lattice_size];
	bond_strength_table = new double[number_of_bonds];

	for(int i=0; i<number_of_realizations; i++)
	{
		prep_lattice();
		grow_ruptures();
	}

	while(grow_rupture())
	{
		this_rupture_size++;
	}

	std::ofstream toFile1("size_distribution.txt", std::ios::trunc);
	toFile1 << rupture_sizes.size() << "\n";
	toFile1 << "Rupture sizes for: " << number_of_ruptures << " ruptures in " << number_of_realizations << " realizations on " << lattice_height << " by " << lattice_length << "\n";
	toFile1.precision(17);

	std::map<unsigned long int, unsigned long int>::iterator iterator;
	for(iterator = rupture_sizes.begin(); iterator != rupture_sizes.end(); iterator++)
	{
		toFile1 <<  iterator->first << "\t";
		toFile1 <<  iterator->second << "\n";
	}

	toFile1.close();

	std::ofstream toFile2("event_list.txt", std::ios::trunc);
	toFile2 << event_list.size() << "\n";
	toFile2 << "Events for: " << number_of_ruptures << " ruptures in " << number_of_realizations << " realizations on " << lattice_height << " by " << lattice_length << "\n";
	toFile2.precision(17);

	std::vector<earthquake>::iterator iterator2;
	for(iterator2 = event_list.begin(); iterator2 != event_list.end(); iterator2++)
	{
		toFile2 <<  iterator2->waiting_time << "\t";
		toFile2 <<  iterator2->area << "\t";
		toFile2 <<  get_site_x(iterator2->epicenter) << "\t";
		toFile2 <<  get_site_y(iterator2->epicenter) << "\n";
	}

	toFile2.close();

	delete[] lattice;
	delete[] bond_strength_table;
	return 0;
}

