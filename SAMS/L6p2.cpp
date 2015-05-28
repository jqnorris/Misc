#include <iostream>

float Convert(float TempFer);

int main()
{
	using namespace std;
	
	float TempFer;
	float TempCel;
	
	cout << "Please enter the temperature in Fahrenheit: ";
	cin >> TempFer;
	TempCel = Convert(TempFer);
	cout << "\nHere's the temperature in Celsius: ";
	cout << TempCel << endl;
	return 0;
}

float Convert(float TempFer)
{
	float TempCel;
	TempCel = ((TempFer -32)*5)/9;
	return TempCel;
}