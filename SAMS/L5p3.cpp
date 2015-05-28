// LIsting 5.3 - demostrates use of
// prefix and postfix increment and
// decrement operators

#include <iostream>

int main()
{
	using std::cout;
	
	int myAge = 39;	//initalize two integers
	int yourAge = 39;
	cout << "I am: " << myAge << " years old.\n";
	cout << "You are: " << yourAge << " years old\n";
	myAge++;
	++yourAge;
	cout << "One year passes...\n";
	cout << "I am: " << myAge << " years old.\n";
	cout << "You are: " << yourAge << " years old\n";
	cout << "Another year passes...\n";
	cout << "I am: " << myAge++ << " years old.\n";
	cout << "You are: " << ++yourAge << " years old.\n";
	cout << "Let's print it again. \n";
	cout << "I am: " << myAge << " years old.\n";
	cout << "You are: " << yourAge << " years old\n";
	return 0;
}