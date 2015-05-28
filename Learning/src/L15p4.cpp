/*
 * L15p4.cpp
 *
 *  Created on: Jun 29, 2012
 *      Author: jqnorris
 */

#include <iostream>

// Template class with default template paramenters
template < typename T1=int, typename T2=double>
class CHoldsPair
{
private:
	T1 m_Value1;
	T2 m_Value2;
public:
	//Constructor that intializes member variables
	CHoldsPair ( const T1& value1, const T2& value2)
	{
		m_Value1 = value1;
		m_Value2 = value2;

	};

	//Accessor functions
	const T1& GetFirstValue ()
	{
		return m_Value1;
	};

	const T2& GetSecondValue ()
	{
		return m_Value2;
	};
};

int main()
{
	using namespace std;

	//Two instatiations of template CHOldsPair -
	CHoldsPair <> mIntFloatPair (300,10.09);
	CHoldsPair<short,char*>mShortStringPair(25, "Learn Templates, love C++");

	// Output values contained in the first object...
	cout << "The first object contains." << endl;
	cout << "Value 1: " << mIntFloatPair.GetFirstValue() << endl;
	cout << "Value 2: " << mIntFloatPair.GetSecondValue() << endl;

	// Output values contained in the first object...
	cout << "The first object contains." << endl;
	cout << "Value 1: " << mShortStringPair.GetFirstValue() << endl;
	cout << "Value 2: " << mShortStringPair.GetSecondValue() << endl;

	return 0;

}



