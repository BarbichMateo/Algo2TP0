#include <iostream>

#include "Array.h"

using namespace std;

float getDistance(Array <float> &coord1, Array <float> &coord2) //devuelve el cuadrado de la distancia entre vectores de float coord1 y coord2
{
    size_t i;float s=0;
    if(coord1.getSize()==coord2.getSize())
    {
        for(i=0;i<coord1.getSize();i++)
        {
            s+=(coord1[i]-coord2[i])*(coord1[i]-coord2[i]);
        }
        return s;
    }
    else
        cerr<<"Error al calcular distancia: los elementos no tienen la misma cantidad de dimensiones"<<endl;//o algo asi, un indicador de que habitan espacios vectoriales distintos y no se pueden comparar
    return -1;
}


int main (void)
{
	Array <float> v(5),w(5);
	size_t i;char c;
	for(i=0;i<v.getSize()+1;i++)
    {
        v[i]=i+1;
        w[i]=i+5;
    }
    cout<<"(";
    for(i=0;i<v.getSize();i++)
    {
        cout<<v[i]<<" ";
    }
    cout<<")"<<endl;
    cout<<"(";
    for(i=0;i<w.getSize();i++)
    {
        cout<<w[i]<<" ";
    }
    cout<<")"<<endl;
    cout<<"el cuadrado de la distancia entre v y w es: "<<getDistance(v,w)<<endl;
	cin.get(c);
	return 0;
}
