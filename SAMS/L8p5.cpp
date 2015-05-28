// LISting 8.5
// Allocating and deleting a pointer
#include <iostream>

int main()
{
	using namespace std;
	int localVariable = 5;
	int * pLocal= &localVariable;
	int * pHeap = new int;
	*pHeap = 7;
	cout << "localVariable: " << localVariable << endl;
	cout << "*plocal: " <<*pLocal << endl;
	cout << "*pHeap: " << *pHeap << endl;
	delete pHeap;
	pHeap = new int;
	*pHeap = 9;
	cout << "*pHeap: " << *pHeap << endl;
	delete pHeap;
	return 0;
}