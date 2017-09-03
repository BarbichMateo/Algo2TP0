// Test para hacer bien la lectura y parseo de los CSV

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "Array.h"

#define MSG_ERR_OPEN_FILE "Error al abrir el archivo "
#define MSG_ERR_FIND_DIMENSION "Error al leer la dimension"
#define MSG_ERROR_LINE "Error al leer la linea"
#define MSG_ERROR_DELIMITER "Error al buscar el delimitador"
#define MSG_ERROR_CALL_DIMENSION "Error en la llamada, las dimensiones no son correctas"
#define MSG_ERR_LOADING_POINTS "Error al cargar los puntos"
#define MSG_ERR_EOF_BEFORE "Error EOF visto antes de lo esperado"

#define CSV_DELIMITER ' '

using namespace std;

int parse_line_vector(int dimension, Array <double> & vector, istream * ptr_iss);

int main(void)
{
	fstream is;
	istream *ptr_is;
	double d;
	char ch;
	int n;

	is.open("archivoTest", ios::in);
	ptr_is = &is;
	ch = is.get();
	ch = is.get();
	
	Array <double> v (3);
	n = parse_line_vector (3,v,ptr_is);
	cout << n << endl;

	return 0;
}

int parse_line_vector(int dimension, Array <double> & vector, istream * ptr_iss)
{	
	double aux;
	char ch;
	

	for(int i=0;i<dimension;++i){
		(*ptr_iss)>>aux;
		ch = ptr_iss->get();
		if( (i != dimension-1) && (ch != CSV_DELIMITER) ){
			if(ptr_iss->eof())
				return -1;
			//Campo que no debería ser el ultimo y no sigue con delimitador
cout << (int)ch << '\t';
			cerr << MSG_ERROR_DELIMITER << endl;
			return 1;
		}
		vector[i] = aux;
cout<< i << '\t' <<(int)ch << '\t' << vector[i] << endl;
	}

	//Ahora reviso si el último char leido es el final de linea (devuelvo 0), EOF (devuelvo -1 para que no sigan leyendo) o distinto de eso (algo esta mal en la linea)
	if( ch == '\n'){
		// Reviso si es el final del archivo, marcado como \nEOF
		if((ch = ptr_iss-> get()) == EOF )
			return -1;
		else{
			ptr_iss->putback(ch);
			return 0;
		}
	}
	if( ch == EOF ){
		// Reviso si el archivo termina como EOF directamente
		return -1;
	}
	// Si no entró en los otros, hubo un error
	cerr << MSG_ERROR_LINE << endl;
	return 1;
}
