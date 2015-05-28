//Listing 9.6 - Demostrates passing by refernce
#include <iostream>

using namespace std;
void swap(int &rx, int &ry);

int main()
{
	int x = 5, y = 10;
	
	cout << "Main. Before swap, x: " << x << " y: " << y << endl;
	swap(x,y);
	cout << "Main. After swap, x: " << x << " y: " << y << endl;
	
	return 0;
}

void swap (int &rx, int &ry)
{
	int temp;
	
	cout << "Swap. Before swap, x: " << rx << " y: " << ry << endl;
	
	temp =rx;
	rx = ry;
	ry = temp;
	
	cout << "Swap. After swap, x: " << rx << " y: " << ry << endl;
}