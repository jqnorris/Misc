/*
 * main.cpp
 *
 *  Created on: Feb 8, 2013
 *      Author: jqnorris
 */


#include <map>
#include <string>
#include "RandKnuth.h"
#include <iostream>

using std::multimap;
using std::string;
using std::cout;
using std::endl;
using std::pair;

int main()
{
	std::multimap<string, char> testMap;

	std::map <string, char> grade_list;

	multimap<string, int> m;
	m.insert(pair<string, int>("b", 6));
	m.insert(pair<string, int>("c", 7));
	m.insert(pair<string, int>("c", 7));
	m.insert(pair<string, int>("c", 7));
	m.insert(pair<string, int>("c", 6));

	cout<<m.begin()->first<<endl;
	m.erase(m.begin());
	cout<<m.begin()->first<<endl;
	cout<<m.size() <<endl;
	m.erase(m.begin());
	cout<<m.begin()->first<<endl;
	cout<<m.size() <<endl;

	grade_list["John"] = 'B';
	testMap.insert(std::pair<string, char>("John", 'B'));

	cout<<grade_list.begin()->first<<endl;
	cout<<testMap.begin()->first<<endl;


	return 0;
}

