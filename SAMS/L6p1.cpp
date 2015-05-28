// Listing 6.1 - demonstrates the use of function protptypes

#include <iostream>
int Area(int length, int width);//function prototype

int main()
{
	using std::cout;
	using std::cin;
	
	int lengthOfYard = 0;
	int widthOfYard = 0;
	int areaOfYard = 0;
	
	cout << "\nHow wide is your yard? ";
	cin >> widthOfYard;
	cout << " \nHow long is your yard?";
	cin >> lengthOfYard;
	
	areaOfYard=Area(lengthOfYard, widthOfYard);
	
	cout << "\nYour yard is ";
	cout << areaOfYard;
	cout << " square feet\n\n";
	return 0;
}

int Area(int length, int width)
{
	return length * width;
}