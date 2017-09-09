// Main TP0 algo2
//
//

#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <sstream>

#include "cmdline.h"
#include "Array.h"

#define MSG_ERR_OPEN_FILE "Error al abrir el archivo "
#define MSG_ERR_FIND_DIMENSION "Error al leer la dimension"
#define MSG_ERROR_LINE "Error al leer la linea"
#define MSG_ERROR_DELIMITER "Error al buscar el delimitador"
#define MSG_ERROR_CALL_DIMENSION "Error en la llamada, las dimensiones no son correctas"
#define MSG_ERR_LOADING_POINTS "Error al cargar los puntos"
#define MSG_ERR_EOF_BEFORE "Error EOF visto antes de lo esperado"
#define MSG_ERROR_DISTANCE_DIMENSION "Error al calcular distancia: los elementos no tienen la misma cantidad de dimensiones"
#define MSG_ERROR_NULL_POINTER "Error puntero nulo"
#define MSG_ERROR_QUERY "Error en el query"

#define POINTS_STARTING_SIZE 1
#define CSV_DELIMITER ' '
//TODO: SEPARAR EL .H DEL MAIN

using namespace std;

static void opt_points (string const &arg);
static void opt_input(string const &arg);
static void opt_output(string const &arg);

int read_points_dimension(int &dimension, istream * ptr_iss);
int load_points (int dimension, Array <Array <double> >& points_tiberium, istream * ptr_iss);
int parse_line_vector(int dimension, Array <double> & vector, istream * ptr_iss);

double getDistance(Array <double> &coord1, Array <double> &coord2);
int get_min_distance(Array < Array <double> > &database,Array <double> & query);
int make_query (Array <Array <double> > &database, int dimension, istream * query_file, ostream * target_file);

//========= GLOBAL VARS =========
static option_t options[] = {
	{1, "p", "points", "-", opt_points, OPT_MANDATORY},
	{1, "i", "input", "-", opt_input, OPT_DEFAULT},
	{1, "o", "output", "-", opt_output, OPT_DEFAULT},
//	{0, "h", "help", "-", opt_input, OPT_DEFAULT},
	{0, }
};

static istream *points_stream = 0;
static istream *input_stream = 0;
static ostream *output_stream = 0;

static fstream pfs;
static fstream ifs;
static fstream ofs;

//======== Option parsers =========

static void opt_points (string const &arg)
{
	pfs.open(arg.c_str(), ios::in);
	points_stream = &pfs;

	if(!points_stream->good()){
		cerr << MSG_ERR_OPEN_FILE << arg << endl;
		exit(1);
	}
}


static void opt_input(string const &arg)
{
	if(arg == "-") {
		input_stream = &cin;
	}
	else{
		ifs.open(arg.c_str(), ios::in);
		input_stream = &ifs;
	}

	if(!input_stream-> good()){
		cerr << MSG_ERR_OPEN_FILE << arg << endl;
		exit(1);
	}
}

static void opt_output(string const &arg)
{
	if(arg == "-") {
		output_stream = &cout;
	}
	else{
		ofs.open(arg.c_str(), ios::out);
		output_stream = &ofs;
	}

	if(!output_stream-> good()){
		cerr << MSG_ERR_OPEN_FILE << arg << endl;
		exit(1);
	}
}

//========================================

ostream & operator<<(ostream &os, Array <double> &v)
{
	for(int i=0; i<v.getSize()-1; ++i){
		os << v[i] << CSV_DELIMITER;	
	}
	return os << v[v.getSize()-1]; 
}

int read_points_dimension(int &dimension, istream * ptr_iss)
{
	int n=0;
	char ch=0;

//TODO hacerlo para que acepte de mac
	if( NULL == ptr_iss){
		return 1;
	}
	if( ((*ptr_iss)>>n) && ((ch = ptr_iss->get()) == '\n') ){ //Linux endl
		dimension = n;
		return 0;
	}
	if( (n && ch =='\r') && ((ch = ptr_iss->get()) == '\n') ){ //Win endl
		dimension = n;
		return 0;
	}
	return 1;
}

int load_points (int dimension, Array <Array <double> > & points_tiberium, istream * ptr_iss)
{
	bool eof=false;
	int st;
	char ch;
	Array <double> * ptr_current_array

	if( ptr_iss == NULL){
		return 1;
	}
	for(int i=0; !eof; ++i){
		current_array = new Array <double> (dimension);
		st = parse_line_vector(dimension, current_array, ptr_iss);
		if(st == -1)
			eof = true;
		if(st == 1){
			--i;
			delete current_array;
		}
		if(st == 0){
			if(points_tiberium.getSize() == i){
//TODO Trabajo con memoria, falta validar
				points_tiberium.append(current_array);	
			}
			else{
				points_tiberium [i] = current_array;
			}
		}
	}
	return 0;
}


int parse_line_vector(int dimension, Array <double> & vector, istream * ptr_iss)
{	
// Leo una linea de ptr_iss, en csv, la parceo y la pongo en vector
	double aux;
	char ch;

// TODO: ACEPTAR ENDL DE WIN Y MAC
// TODO: VALIDAR LA LECTURA DEL DOBLE
// TODO: VALIDAR SI HAY MÁS DE UNA COSA DESPUES DEL DELIMITADOR

// TODO: EOF lo manda por argumento
	for(int i=0;i<dimension;++i){
		(*ptr_iss)>>aux;
		ch = ptr_iss->get();
		if( (i != dimension-1) && (ch != CSV_DELIMITER) ){
			if(ptr_iss->eof()){
				return -1;
			}
			//Campo que no debería ser el ultimo y no sigue con delimitador
cout << (int)ch << i << endl;
			cerr << MSG_ERROR_DELIMITER << endl;
			if(ch == '\n'){
				return 1;
			}
			// Leo hasta el '\n', y le resto a i para que vuelva como estaba
		//	while( ((ch = (ptr_iss->get())) != '\n') && (ch != EOF));
			return 1;
		}
		vector[i] = aux;
	}

	//Ahora reviso si el último char leido es el final de linea (devuelvo 0), EOF (devuelvo -1 para que no sigan leyendo) o distinto de eso (algo esta mal en la linea)
	if( ch == '\n'){
		// Reviso si es el final del archivo, marcado como \nEOF
		return 0;
	}
	if( ch == EOF ){
		// Reviso si el archivo termina como EOF directamente
		// Que la llamen de nuevo para enterarse
		return 0;
	}
	// Si no entró en los otros, hubo un error
	cerr << MSG_ERROR_LINE << endl;
	return 1;
}

double getDistance(Array <double> &coord1, Array <double> &coord2) 
//devuelve el cuadrado de la distancia entre vectores de double coord1 y coord2
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

int get_min_distance(Array < Array <double> > database,Array <double> & query)
{
	int database_dimension, min_pos=0;
	double min_distance,new_distance;

	database_dimension= database.getSize(); 
	for (int i=0; i< database_dimension;++i){
		new_distance = getDistance(database[i],query);
		if(new_distance < min_distance){
			min_distance = new_distance;
			min_pos = i;
		}
	}
	return min_pos;
} 

int make_query (Array <Array <double> > database, int dimension, istream * query_file, ostream * target_file)
{
	int st,pos;
	bool eof=false;
	Array <double> current_array (dimension);

	if(query_file||target_file){
		cerr << MSG_ERROR_NULL_POINTER << endl;
		return 1;
	}

//	current_array =  new Array <double> (dimension);
	while(!eof){
		st = parse_line_vector(dimension, current_array, query_file);
		if(st == -1)
			eof = true;
		if(st == 1){
			//No hago nada
		}
		if(st == 0){
			pos = get_min_distance(database, current_array);
//TODO hacer que eso ande
			(*target_file) << database[pos] << endl;
		}
	}
	return 0;
}



int main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	int dimension;
	Array <Array <double> > * ptr_points_tiberium;

	cmdl.parse(argc, argv);
	if(read_points_dimension(dimension,points_stream)){
//  TODO: COMO SE CIERRAN LOS STREAMS?
//		input_stream->close();
//		points_stream->close();
// 		output_stream->close();
		cerr<<MSG_ERR_FIND_DIMENSION<<endl;
		return 1;
	}
	ptr_points_tiberium = new Array <Array <double> > (POINTS_STARTING_SIZE);
//  TODO: validar memoria
	if(load_points(dimension, *ptr_points_tiberium, points_stream)){
		delete points_tiberium;
//		input_stream->close();
//		points_stream->close();
//		output_stream->close();
		cerr<<MSG_ERR_LOADING_POINTS<<endl;
		return 1;
	}

	if(make_query(*ptr_points_tiberium,dimension,input_stream,output_stream)){
		delete &points_tiberium;
		cerr<<MSG_ERROR_QUERY << endl;
		return 1;
	}
	

//debug print
cout << points_tiberium[0].getSize()<<endl;
for(int i=0;i<points_tiberium.getSize();++i){
	for(int j=0;j<(points_tiberium[i]).getSize();++j){
		cout<<points_tiberium[i][j]<<'\t';
	}
	cout<<'\n';
}
	
	return 0;
}
