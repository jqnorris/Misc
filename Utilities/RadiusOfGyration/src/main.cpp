/*
 * main.cpp
 *
 *  Created on: Feb 11, 2013
 *      Author: jqnorris
 */

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main()
{
	string temp;
	vector<int> x;
	vector<int> y;

	ifstream myfile("invasion.txt");
	if(!myfile)
	{
		cout<<"Error opening output file"<<endl;
		return -1;
	}

	getline(myfile,temp);
	while(!myfile.eof())
	{
		getline(myfile,temp,'\t');
		x.push_back(atoi(temp.c_str()));
		getline(myfile,temp,'\n');
		y.push_back(atoi(temp.c_str()));
	}

	myfile.close();

	int length=x.size()-1;

	double* radiusG;
	radiusG = new double[length];

	long unsigned int Sum=0;

	radiusG[0]=0;

	for(int i=1; i<length; i++)
	{
		for(int j=0; j<i; j++)
		{
			Sum += ((x[i]-x[j])*(x[i]-x[j]) + (y[i]-y[j])*(y[i]-y[j]));
		}
		radiusG[i] = 1.0/(1.0*i)*sqrt(Sum);
	}

	ofstream toFile("radiusG.txt", std::ios::trunc);
	toFile << "Radius of Gyration in time\n";

	for(int i=0; i< length; i++)
	{
		toFile << radiusG[i] << "\n";
	}

	toFile.close();

	delete radiusG;

	return 0;
}


