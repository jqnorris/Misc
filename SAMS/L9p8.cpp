// Listing 9.8
// Returning multiple values from a function
// using references

#include <iostream>

using namespace std;

enum Err_Code { SUCCESS, ERROR };

Err_Code Factor(int, int&, int&);

int main()
{
	int number, squared, cubed;
	Err_Code result;
	
	cout << "Enter a number (0 - 20): ";
	cin >>number;
	
	result = Factor(number, squared, cubed);
	
	if (result == SUCCESS)
	{
		cout << "number: " << number << endl;
		cout << "suare: " <<squared << endl;
		cout << "cubed:" << cubed << endl;
		
	}
	else
	{
		cout << "Error encountered!!" << endl;
	};
	return 0;
}

Err_Code Factor (int n, int &rSquared, int &rCubed)
{
	if (n > 20)
	{
		return ERROR;  // simple error code
	}
	else
	{
		rSquared = n*n;
		rCubed = n*n*n;
		return SUCCESS;
	}
}
	
		