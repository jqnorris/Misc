/*
 * E15p5.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: jqnorris
 */

#include <iostream>
#include <cmath>

using namespace std;

template <typename T1, typename T2>
class CHoldsPairArray
{
private:
	T1 array1[10];
	T2 array2[10];
public:
	CHoldsPairArray(const T1& value1, const T2& value2)
	{
		fill_n(array1, 10, value1);
		fill_n(array2, 10, value2);
	};

	T1 & getValue1(const int index)
	{
		return array1[index];
	};

	T2 & getValue2(const int index)
	{
		return array2[index];
	};

	void setValue1(const int index, T1 value)
	{
		array1[index]=value;
	};

	void setValue2(const int index, T2 value)
	{
		array2[index]=value;
	};
};

int main()
{
	//Define pair of arrays
	CHoldsPairArray<int,char*>Name(1,"test");
	cout << Name.getValue1(9) << endl;
	cout << Name.getValue2(9) << endl;
	Name.setValue1(1,11);
	Name.setValue2(1,"hello");
	cout << Name.getValue1(1) << endl;
	cout << Name.getValue2(1) << endl;

	//Define pair of arrays
	CHoldsPairArray<long,float>Name2(9999999,pow(10.0, 10.0));
	cout << Name2.getValue1(9) << endl;
	cout << Name2.getValue2(0) << endl;
	Name2.setValue1(1,11);
	Name2.setValue2(1,0.00000000000000001);
	cout << Name2.getValue1(1) << endl;
	cout << Name2.getValue2(1) << endl;

	return 0;
}
