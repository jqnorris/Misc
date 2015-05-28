// Cemostrate delcaration of a class and
// definition of an object of the class

#include <iostream>

class Cat
{
	public:
		int itsAge;
		int itsWeight;
};

int main()
{
	Cat Frisky;
	Frisky.itsAge = 5;
	std::cout << "Frisky is a cat who is ";
	std::cout << Frisky.itsAge << " years old.\n";
	return 0;
}