#include <iostream>

#include "Array.h"

using namespace std;

double getDistance(Array <double> &coord1, Array <double> &coord2) //devuelve el cuadrado de la distancia entre vectores de double coord1 y coord2
{
    size_t i;double s=0;
    if(coord1.getSize()==coord2.getSize())
    {
        for(i=0;i<coord1.getSize();i++)
        {
            s+=(coord1[i]-coord2[i])*(coord1[i]-coord2[i]);
        }
        return s;
    }
    else
        cerr<<MSG_ERROR_DISTANCE_DIMENSION <<endl;
    return -1;
}


int main (void)
{
    char c;
	Array <float> v(5),w(5);//los cambie a float porque es lo que vamos a usar para las coordenadas y queria ver que ande bien con eso
	size_t i;
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
    cout<<"el cuadrado de la distancia entre v y w es: "<<getDistance(v,w)<<endl;//este ciclo para probar si funciona la distancia
	cin.get(c);
	return 0;
}
