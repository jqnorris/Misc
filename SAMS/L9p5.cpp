//Listing 9.5 - Demostrates passing by refernce
#include <iostream>

using namespace std;
void swap(int *px, int *py);

int main()
{
	int x = 5, y = 10;
	
	cout << "Main. Before swap, x: " << x << " y: " << y << endl;
	swap(&x,&y);
	cout << "Main. After swap, x: " << x << " y: " << y << endl;
	
	return 0;
}

void swap (int *px, int *py)
{
	int temp;
	
	cout << "Swap. Before swap, x: " << *px << " y: " << *py << endl;
	
	temp =*px;
	*px = *py;
	*py = temp;
	
	cout << "Swap. After swap, x: " << *px << " y: " << *py << endl;
}