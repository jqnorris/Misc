/*
 * main.cpp
 *
 *  Created on: Oct 16, 2014
 *      Author: jqnorris
 */


#include <iostream>
#include <tuple>
#include <climits>

struct test_1
{
	int a;
	int b;
};


typedef std::pair<int, int> Site_coordinates;
typedef std::tuple<int, int, int> test;


int main(int argc, char **argv)
{
	std::cout << "Size of long int: " << sizeof(int) << "\t" << sizeof(int *) << "\n";
	std::cout << "Size of pair: " << sizeof(Site_coordinates) << "\t" << sizeof(Site_coordinates *) << "\n";
	std::cout << "Size of tuple: " << sizeof(test) << "\t" << sizeof(test *) << "\n";
	std::cout << "Size of struct: " << sizeof(test_1) << "\t" << sizeof(test_1 *) << "\n";
	std::cout << INT_MIN << "\t" << INT_MAX;

	return 0;
}

