//Listing 4.6 using cin.get()

#include <iostream>
using namespace std;

int main()
{
	char buffer[80]={'\0'};
	cout << "Enter the string: ";
	cin.get(buffer,79); //get up to 79 or newline
	cout << "Her's the buffer: " << buffer << endl;
	return 0;
}
	