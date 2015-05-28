/*
 * L11.12.cpp
 *
 *  Created on: Jun 26, 2012
 *      Author: jqnorris
 */

//Listing 11.12 Demostration of Private Inheritance
#include <iostream>

using namespace std;

class ElectricMotor
{
public:
	ElectricMotor() {};
	virtual ~ElectricMotor() {};
public:
	void StartMotor()
	{
		Accelerate();
		Cruise();
	}

	void StopMotor()
	{
		cout << "Motor stopped" << endl;
	};

private:
	void Accelerate()
	{
		cout << "Motor started" << endl;
	}
	void Cruise()
	{
		cout << "Motor running at constant speed" << endl;
	}

};

class Fan : private ElectricMotor
{
public:
	Fan() {};
	~Fan() {}

	void StartFan()
	{
		StartMotor();
	}

	void StopFan()
	{
		StopMotor();
	}
};

int main()
{
	Fan mFan;

	mFan.StartFan();
	mFan.StopFan();
}
