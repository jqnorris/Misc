#include <iostream>

long int divide(unsigned short int, unsigned short int);

int main()
{
	using namespace std;
	
	unsigned short int x, y;
	long int z;
	
	cout << "Give me two numbers.\n";
	cin >> x;
	cin >> y;
	z = divide(x,y);
	if (z==-1)
	{
		cout << "YOU CAN'T DIVIDE BY ZERO!!!!!!!!!\n";
	}
	else
	{
		cout << "Here is the result: " << z << endl;
	}
	return 0;	
}

long int divide(unsigned short int x, unsigned short int y)
{
	if (y==0)
	{
		return -1;
	}
	else
	{
		return x/y;
	}
}
	