//Listing 9.1 - Demostrating the use of pointers

#include <iostream>

int main()
{
	using namespace std;
	int intOne;
	int &rSomeRef = intOne;
	intOne =5;
	cout << "intONe: " << rSomeRef << endl;
	cout << "rSomeRef: " << rSomeRef << endl;
	
	rSomeRef = 7;
	cout << "intONe: " << intOne << endl;
	cout << "rSomeRef: " << rSomeRef << endl;
	
	return 0;
}
