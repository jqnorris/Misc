#include <iostream>

//function Demonstration Function
// prints out a useful message

void DemonstrationFunction()
{
	std::cout << "In Demonstration Function\n";
}

//function main - prints out a message, then
//calls DemonstrationDunction, then prints our
// a second message.

int main()
{
	std::cout << "In main\n";
	DemonstrationFunction();
	std::cout << "Back in main\n";
	return 0;
}