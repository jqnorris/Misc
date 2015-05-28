#include <iostream>

using namespace std;

int main()
{
	int rows, columns;
	
	cout << "How many rows?\n";
	cin >> rows;
	cout << "How many columns?\n";
	cin >> columns;
	
	for(int i=0; i<rows; i++)
	{
		for(int j=0; j<columns; j++)
		{
			cout << "0";
		}
		cout << endl;
	}
	
	return 0;
}
	