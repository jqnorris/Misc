//LIsting 4.7 USing strcpy()

#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	char String1[] = "No man is an island";
	char String2[80] = {'\0'};
	
	strcpy(String2,String1);
	
	cout << "String1: " << String1 << endl;
	cout << "String2: " << String2 << endl;
	return 0;
}
