//Listing 9.4 - Demostrates passing by value
#include <iostream>

using namespace std;
void swap(int x, int y);

int main()
{
	int x = 5, y = 10;
	
	cout << "Main. Before swap, x: " << x << " y: " << y << endl;
	swap(x,y);
	cout << "Main. After swap, x: " << x << " y: " << y << endl;
	
	return 0;
}

void swap (int x, int y)
{
	int temp;
	
	cout << "Swap. Before swap, x: " << x << " y: " << y << endl;
	
	temp =x;
	x = y;
	y = temp;
	
	cout << "Swap. After swap, x: " << x << " y: " << y << endl;
}