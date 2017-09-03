// Test de array.h

#include <iostream>

#include "Array.h"

using namespace std;

int main (void)
{
	Array <int> v(8),w(3);
	size_t i;
	int n;
	Array <Array <int> > m(2);
	char c,d;

	v[4] = 3;
	v[6] = 19;
	n = 7;
	v.append(n);

	for(i=0;i<v.getSize();++i){
		std::cout<<v[i]<<std::endl;
	}
	
	m[0] = v;
	m[1] = w;


	for(i=0;i<(m[0]).getSize();++i){
		std::cout<<(m[0])[i]<<std::endl;
	}
	for(i=0;i<(m[1]).getSize();++i){
		std::cout<<(m[1])[i]<<std::endl;
	}
	d = 'i';
	cin.get(c);
	if(c == 'c')
		std::cout << c << "ceeee";
	std::cout << c << std::endl;
	return 0;
}
