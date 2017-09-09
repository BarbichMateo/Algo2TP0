// Test de array.h

#include <iostream>

#include "Array.h"

using namespace std;

int main (void)
{
	Array <int> * v;
	
	v = new Array <int> (5);
	(*v)[3] = 2;
	cout << (*v)[3];
	delete v;
	(*v)[4] = 3;
	cout << (*v)[4];
	

	return 0;
}
