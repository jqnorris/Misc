// Listing 8.1 Demostrates address-of operator
// and addresses of local variables

#include <iostream>

int main()
{
	using namespace std;
	unsigned short shortVar=5;
	unsigned long longVar=65535;
	long sVar = -65535;
	
	cout << "shortVar: \t" << shortVar;
	cout << "\tAddress of shortVar:\t";
	cout << &shortVar << endl;
	
	cout << "longVar: \t" << longVar;
	cout << "\tAddress of longVar:\t";
	cout << &longVar << endl;
	
	cout << "sVar: \t" << sVar;
	cout << "\tAddress of sVar:\t";
	cout << &sVar << endl;
	return 0;
}