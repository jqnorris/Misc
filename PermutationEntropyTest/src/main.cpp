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
typedef std::multimap<long int, std::string> perm_Reverse;

int main(int argc, char **argv)
{
	long int N, i, j, count, test, factorial;
	double value;
	int block_length, Lmax, index;


	block_cont block;
	perm_counter permutations;
	perm_Reverse reversed;
	block_cont::iterator beginning;
	std::stringstream perm_string;
	std::string perm;

	N = 150000000;
	double * strengths;
	srand48(time(NULL));

	Lmax = 1;
	factorial = 2;
	test = 1000;
	while (test > 10)
	{
		Lmax++;
		factorial = factorial*(Lmax+1);
		test = N/(factorial);
	}
	strengths = new double[N];
	for (i=0; i < N; i++)
	{
		strengths[i] = drand48();
	}

	std::ofstream toFile("perm_Entropy.txt", std::ios::trunc);
	toFile.close();
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
		std::ofstream toFile("perm_Entropy.txt", std::ios::app);
		while (!permutations.empty())
		{
			perm = permutations.begin()->first;
			count = permutations.begin()->second;
			reversed.insert(std::make_pair(count, perm));
			permutations.erase(perm);
		}
		while (!reversed.empty())
		{
			perm = reversed.begin()->second;
			count = reversed.begin()->first;
			toFile << perm << "\t" << count << "\n";
			reversed.erase(reversed.begin());
		}
		std::cout << block_length << " complete\n";
		toFile.close();
	}

	delete[] strengths;

	return 0;
}
