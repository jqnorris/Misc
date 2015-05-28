/*
 * main.cpp
 *
 *  Created on: May 30, 2013
 *      Author: jqnorris
 */

#include <map>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

typedef std::map<double, int> block_cont;
typedef std::map<std::string, long int> perm_counter;

int main(int argc, char **argv)
{
	long int N, i, j, count;
	double value;
	int block_length, Lmax, index;
	Lmax = atoi(argv[1]);

	block_cont block;
	perm_counter permutations;
	block_cont::iterator beginning;
	std::stringstream perm_string;
	std::string temp, perm;

	std::ifstream from_file("fractures.txt");

	std::getline(from_file, temp);
	N = atoi(temp.c_str());
	std::getline(from_file, temp);
	double * strengths;

	strengths = new double[N];
	for (int i=0; i < N; i++)
	{
		std::getline(from_file, temp, '\t');
		strengths[i] = atof(temp.c_str());
		std::getline(from_file, temp);
	}

	from_file.close();

	std::ofstream toFile("perm_Entropy", std::ios::trunc);
	toFile.close()
	for (block_length=2; block_length<=Lmax; block_length++)
	{
		permutations.clear();
		for(i=0; i<N-block_length+1; i++)
		{
			index =0;
			for(j=i; j<i+block_length; j++)
			{
				value = strengths[j];
				block.insert(std:: make_pair(value, index));
				index++;
			}
			perm_string.str(std::string());
			while (!block.empty())
			{
				beginning = block.begin();
				perm_string << beginning->second << ',';
				block.erase(beginning);
			}

			perm = perm_string.str();
			if (permutations.count(perm) > 0)
			{
				permutations[perm] +=1;
			}
			else
			{
				permutations.insert(std::make_pair(perm, 1));
			};
		}
		std::ofstream toFile("perm_Entropy", std::ios::app);
		while (!permutations.empty())
		{
			perm = permutations.begin()->first;
			count = permutations.begin()->second;
			toFile << perm << "\t" << count << "\n";
			permutations.erase(perm);
		}
		std::cout << block_length << " complete\n";
		toFile.close();
	}

	delete[] strengths;

	return 0;
}
