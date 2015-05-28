#include <iostream>

using namespace std;

int Power(int base, int power);

int main()
{
	int base, power, result=1;
	
	cout << "Give me a number.\n";
	cin >> base;
	cout << "Give me a power.\n";
	cin >> power;
	
	cout << "\nWith recursion\n";
	result=Power(base,power);
	cout << "Here you go: " << result << endl << endl;
	
	cout << "With a for loop.\n";
	result=1;
	if (power==0)
	{
		result=1;
	}
	else
	{
		for(int i=1; i<=power; i++)
		{
			result=result*base;
		}
	}
	cout << "Here you go: " << result << endl << endl;
	
	return 0;
}

int Power(int base, int power)
{
	if (power==0)
	{
		return 1;
	};
	if (power==1)
	{
		return base;
	}
	else
	{
		return Power(base,1)*Power(base,(power-1));
	};
}
	