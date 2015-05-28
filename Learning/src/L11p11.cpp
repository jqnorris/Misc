/*
 * L11p11.cpp
 *
 *  Created on: Jun 26, 2012
 *      Author: jqnorris
 */

//Listing 11.11 Virtual copy constructor
#include <iostream>

using namespace std;

class Mammal
{
public:
	Mammal():itsAge(1){ cout << "Mammal constructor...\n";}
	virtual ~Mammal() { cout << "Mammal destructor..\n";}
	Mammal (const Mammal & rhs);
	virtual void Speak() const { cout << "Mammal speak!\n";}
	virtual Mammal* Clone() {return new Mammal(*this);}
	int GetAge() const { return itsAge;}

	protected:
	int itsAge;
};

Mammal::Mammal (const Mammal & rhs):itsAge(rhs.GetAge())
{
	cout <<  "Mammal Copy Constructor...\n";
}

class Dog : public Mammal
{
public:
	Dog() { cout << "Dog constuctor...\n";}
	virtual ~Dog() { cout << "Dog destructor...\n";}
	Dog( const Dog & rhs);
	void Speak() const { cout << "Woof!\n";}
	virtual Mammal* Clone() { return new Dog(*this);}
};

Dog::Dog(const Dog & rhs):Mammal(rhs)
{
	cout << "Dog copy constructor...\n";
}

class Cat : public Mammal
{
public:
	Cat() { cout << "Dog constuctor...\n";}
	virtual ~Cat() { cout << "Dog destructor...\n";}
	Cat( const Cat & rhs);
	void Speak() const { cout << "Meow!\n";}
	virtual Mammal* Clone() { return new Cat(*this);}
};

Cat::Cat(const Cat & rhs):Mammal(rhs)
{
	cout << "Dog copy constructor...\n";
}

enum ANIMALS{ MAMAL, DOG, CAT};
const int NumAnimalTypes = 3;

int main()
{
	Mammal *theArray[NumAnimalTypes];
	Mammal* ptr;
	int choice, i;
	for (i=0; i<NumAnimalTypes; i++)
	{
		cout << "(1)dog (2)cat (3)Mammal: ";
		cin >> choice;
		switch (choice)
		{
		case DOG: ptr = new Dog;
				break;
		case CAT: ptr = new Cat;
				break;
		default: ptr = new Mammal;
				break;
		}
		theArray[i] = ptr;
	}
	Mammal *OtherArray[NumAnimalTypes];
	for (i=0;i<NumAnimalTypes; i++)
	{
		theArray[i]->Speak();
		OtherArray[i] = theArray[i]->Clone();
	}
	return 0;
}
