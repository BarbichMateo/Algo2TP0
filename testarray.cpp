// Test de array.h

#include <iostream>

#include "Array.h"

using namespace std;

int main (void)
{
	Array <double> * v;
	
	v = new Array <double> (5);
	for(int i=0;i<v->getSize();++i){
		(*v)[i] = i*2.1;
	}
	cout << (*v);

	return 0;
}
