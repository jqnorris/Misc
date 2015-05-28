#include <iostream>

using namespace std;

int main()
{
	int i=100;
	while(i<=200)
	{
		if (i==200)
		{
			cout << i << " Done.\n";
			i++;
		}
		else	
		{			
		cout << i << ", ";
		i+=2;	
		};
	}
	return 0;
}