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
#include <cmath>
#include <fstream>
#include "boost/tuple/tuple.hpp"

typedef std::pair<int, int> Site;
typedef std::set<Site> SiteList;
typedef std::pair<Site, Site> Bond;
typedef std::pair<double,Bond> str_and_Bond;
typedef std::multimap<double, Bond> BondMap;


SiteList    invadedSites;
BondMap     accessibleBonds;
std::deque<str_and_Bond> growth;
std::deque<str_and_Bond> removed;

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

double anisotropy = 4;

double get_new_strength(int direction)
{
	if(direction == 0 or direction == 1)
	{
		return anisotropy*drand48();
	}
	else
	{
		return drand48();
	}
}

bool invade_bond(Bond & inv_bond, double strength)
{
	Site invSite = inv_bond.second;
	if (invadedSites.count(invSite) > 0){
		removed.push_back(std::make_pair(strength,inv_bond));
		return true;
	}


	double newStrength;
	Site newNeighbor;
	Bond newBond;
	growth.push_back(std::make_pair(strength,inv_bond));
	invadedSites.insert(invSite);
	for (int dir=0;dir<4;++dir)
	{
		newNeighbor = get_neighbor(invSite, dir);
		if (invadedSites.count(newNeighbor) == 0)
		{
			newStrength = get_new_strength(dir);
			if(newStrength < 1.0 || accessibleBonds.size() < 10000)
			{
				newBond = std::make_pair(invSite, newNeighbor);
				accessibleBonds.insert(std::make_pair(newStrength, newBond));
			}
		}
	}
	return false;
}

long int i, N;
double cutoff = 0.77;
long int counter=0;
bool already_invaded;
const int num_r_values = 100;
const double log_r_max = 6;
const double log_r_min = 0.1;
double r[num_r_values];
const int num_runs = 1;
long int M_array[num_runs][num_r_values] = {{0}};
long int Removed_array[num_runs][num_r_values];
long int Both_array[num_runs][num_r_values];
std::map<long int, long int> burst_counts;
const int chem_level_cutoff = 10000;
std::map<Site, int> chem_level_list;
int chem_level_array[num_runs][chem_level_cutoff] = {{0}};
std::deque<boost::tuple<int, int, long int> > burst_list;
std::deque<boost::tuple<int, int, int, long int> > burst_array;

void initialize_sim(void)
{
	Site start = std::make_pair(0, 0);
	invadedSites.insert(start);
	for (int neigh=0;neigh<4; neigh++)
	{
		Bond newBond;
		double newStrength =get_new_strength(neigh);
		newBond = std::make_pair(start, get_neighbor(start, neigh));
		accessibleBonds.insert(std::make_pair(newStrength, newBond));
	}
}

void run_sim(void)
{
	BondMap::iterator weakest;
	Bond hypocenter;

	counter = 0;

	for (i=0; i<N;)
	{
		weakest = accessibleBonds.begin();
		already_invaded = invade_bond(weakest->second, weakest->first);
		if(!already_invaded)
		{
			if(weakest->first < cutoff)
			{
				if(counter == 0)
				{
					hypocenter = weakest->second;
				}
				counter +=1;
			}
			else
			{
				if(counter != 0)
				{
					if(burst_counts.count(counter) > 0)
					{
						burst_counts[counter] += 1;
					}
					else
					{
						burst_counts.insert(std::make_pair(counter,1));
					}
					burst_list.push_back(boost::make_tuple(hypocenter.first.first, hypocenter.first.second, counter));
					counter = 0;
				}
			}

			if(chem_level_list.count(weakest->second.first ) > 0)
			{
				chem_level_list.insert(std::make_pair(weakest->second.second, chem_level_list[weakest->second.first]+1));
			}
			else
			{
				chem_level_list.insert(std::make_pair(weakest->second.second, 1));
			}

			i++;
		}
		accessibleBonds.erase(weakest);
	}
}

void write_sim_to_file()
{
	std::ofstream toFile1("fractures.txt", std::ios::trunc);
	std::ofstream toFile2("removed.txt", std::ios::trunc);

	toFile1 << growth.size() << "\n";
	toFile2 << removed.size() << "\n";

	toFile1 << "Invasion for: anisotropy= " << anisotropy << "\n";
	toFile2 << "Bonds removed for: anisotropy= " << anisotropy << "\n";

	toFile1.precision(17);
	toFile2.precision(17);

	str_and_Bond current_Line;
	while (!growth.empty())
	{
		current_Line = growth.front();
		growth.pop_front();
		toFile1 <<  current_Line  .first << "\t";
		toFile1 <<  current_Line.second.first.first << "\t";
		toFile1 <<  current_Line.second.first.second << "\t";
		toFile1 <<  current_Line.second.second.first << "\t";
		toFile1 <<  current_Line.second.second.second << "\n";
	}


	while (!removed.empty())
	{
		current_Line = removed.front();
		removed.pop_front();
		toFile2 <<  current_Line.first << "\t";
		toFile2 <<  current_Line.second.first.first << "\t";
		toFile2 <<  current_Line.second.first.second << "\t";
		toFile2 <<  current_Line.second.second.first << "\t";
		toFile2 <<  current_Line.second.second.second << "\n";
	}

	toFile1.close();
	toFile2.close();

}

void setup_r_values(void)
{
	double temp;
	for(int i=0; i<num_r_values; i++)
	{
		temp = log_r_min + static_cast< double >((log_r_max-log_r_min)* i)/ static_cast< float >(num_r_values);
		r[i] = pow(10.0, temp);
	}
}

std::multiset<long long int> r_squared_array;

void record_sim(int i)
{
	std::deque<str_and_Bond>::iterator iter;
	double temp_x;
	double temp_y;
	double temp_r_sq;

	for(iter=growth.begin(); iter!=growth.end(); iter++)
	{
		temp_x = iter->second.second.first;
		temp_y = iter->second.second.second;
		temp_r_sq = temp_x*temp_x+temp_y*temp_y;
		r_squared_array.insert(temp_r_sq);
	}

	long int count = 0;

	std::multiset<long long int>::iterator iter2 = r_squared_array.begin();

	for(int j=0; j<num_r_values; j++)
	{

		while(count<growth.size() && *iter2 < r[j]*r[j])
		{
			count++;
			iter2++;
		}
		M_array[i][j] = count;
	}

	for(iter=removed.begin(); iter!=removed.end(); iter++)
	{
		temp_x = iter->second.second.first;
		temp_y = iter->second.second.second;
		temp_r_sq = temp_x*temp_x+temp_y*temp_y;
		r_squared_array.insert(temp_r_sq);
	}

	count = 0;
	iter2 = r_squared_array.begin();

	for(int j=0; j<num_r_values; j++)
	{

		while(count<growth.size() + removed.size() && *iter2 < r[j]*r[j])
		{
			count++;
			iter2++;
		}
		Both_array[i][j] = count;
	}

	r_squared_array.clear();

	for(iter=removed.begin(); iter!=removed.end(); iter++)
	{
		temp_x = iter->second.second.first;
				temp_y = iter->second.second.second;
				temp_r_sq = temp_x*temp_x+temp_y*temp_y;
				r_squared_array.insert(temp_r_sq);
	}

	count = 0;
	iter2 = r_squared_array.begin();

	for(int j=0; j<num_r_values; j++)
	{

		while(count<removed.size() && *iter2 < r[j]*r[j])
		{
			count++;
			iter2++;
		}
		Removed_array[i][j] = count;
	}

	std::map<Site, int>::iterator iter3;

	for(iter3 = chem_level_list.begin(); iter3 != chem_level_list.end(); iter3++)
	{
		if(iter3->second < chem_level_cutoff)
		{
			chem_level_array[i][iter3->second]++;
		}
	}

	std::deque<boost::tuple<int, int, long int> >::iterator burst_iter = burst_list.begin();
	std::deque<boost::tuple<int, int, long int> >::iterator burst_list_end = burst_list.end();

	int burst_x;
	int burst_y;
	long int burst_size;

	while(burst_iter != burst_list_end)
	{
		burst_x = burst_iter->get<0>();
		burst_y = burst_iter->get<1>();
		burst_size = burst_iter->get<2>();

		burst_array.push_back(boost::make_tuple(i, burst_x, burst_y, burst_size));

		burst_iter++;
	}
}

void clear_sim(void)
{
	invadedSites.clear();
	accessibleBonds.clear();
	growth.clear();
	removed.clear();
	r_squared_array.clear();
	counter = 0;
	chem_level_list.clear();
	burst_list.clear();
}

void write_runs_to_file(void)
{
	std::ofstream toFile1("cluster_masses.txt", std::ios::trunc);
	toFile1 << num_runs << "\t" << num_r_values << "\t" << N << "\n";
	toFile1 << "Cluster mass as a function of radius" << "\n";

	for(int j=0; j< num_r_values; j++)
	{
		toFile1 << r[j] << "\t";
	}
	toFile1 << "\n";

	for(int j=0; j< num_runs; j++)
	{
		for(int k=0; k< num_r_values; k++)
		{
			toFile1 << M_array[j][k] << "\t";
		}
		toFile1 << "\n";
	}

	toFile1.close();

	std::ofstream toFile2("removed_masses.txt", std::ios::trunc);
	toFile2 << num_runs << "\t" << num_r_values << "\t" << N << "\n";
	toFile2 << "Mass of removed bonds as a function of radius" << "\n";

	for(int j=0; j< num_r_values; j++)
	{
		toFile2 << r[j] << "\t";
	}
	toFile2 << "\n";

	for(int j=0; j< num_runs; j++)
	{
		for(int k=0; k< num_r_values; k++)
		{
			toFile2 << Removed_array[j][k] << "\t";
		}
		toFile2 << "\n";
	}

	toFile2.close();

	std::ofstream toFile3("both_masses.txt", std::ios::trunc);
	toFile3 << num_runs << "\t" << num_r_values << "\t" << N << "\n";
	toFile3 << "Mass of cluster and removed bonds as a function of radius" << "\n";

	for(int j=0; j< num_r_values; j++)
	{
		toFile3 << r[j] << "\t";
	}
	toFile3 << "\n";

	for(int j=0; j< num_runs; j++)
	{
		for(int k=0; k< num_r_values; k++)
		{
			toFile3 << Both_array[j][k] << "\t";
		}
		toFile3 << "\n";
	}

	toFile3.close();

	std::ofstream toFile4("burst_sizes.txt", std::ios::trunc);
	toFile4 << num_runs << "\t" << N << "\t" << cutoff << "\t" << burst_counts.size() << "\n";
	toFile4 << "Counts of burst masses" << "\n";

	std::map<long int, long int>::iterator iter3;

	for(iter3 = burst_counts.begin(); iter3 != burst_counts.end(); iter3++)
	{
		toFile4 << iter3->first << "\t" << iter3->second << "\n";
	}

	toFile4.close();

	std::ofstream toFile5("chem_levels.txt", std::ios::trunc);
	toFile5 << num_runs << "\t" << N << "\t" << chem_level_cutoff << "\n";
	toFile5 << "Counts of chemical level styles" << "\n";

	for(int j=0; j < num_runs; j++)
	{
		for(int k=0; k<chem_level_cutoff; k++)
		{
			toFile5 << chem_level_array[j][k] << "\t";
		}
		toFile5 << "\n";
	}

	toFile5.close();

	std::ofstream toFile6("bursts.txt", std::ios::trunc);
		toFile6 << burst_array.size() << "\n";
		toFile6 << "Burst hypocenters and size for: anisotropy= " << anisotropy << "\n";
		std::deque<boost::tuple<int, int, int, long int> >::iterator burst_iter = burst_array.begin();
		std::deque<boost::tuple<int, int, int, long int> >::iterator burst_list_end = burst_array.end();

		while(burst_iter != burst_list_end)
		{
			toFile6 << burst_iter->get<0>() << "\t";
			toFile6 << burst_iter->get<1>() << "\t";
			toFile6 << burst_iter->get<2>() << "\t";
			toFile6 << burst_iter->get<3>() << "\n";

			burst_iter++;
		}

		burst_list.clear();
		toFile6.close();
}

int main(int argc, char **argv)
{
	srand48(time(NULL));
	N = atoi(argv[1]);
	setup_r_values();

	for(int j = 0; j< num_runs-1; j++)
	{
		initialize_sim();
		run_sim();
		record_sim(j);
		clear_sim();
	}

	initialize_sim();
	run_sim();
	record_sim(num_runs-1);
	write_sim_to_file();

	write_runs_to_file();

	return 0;
}



