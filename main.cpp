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

int read_points_dimension(int &dimension, istream * ptr_iss)
{
	int n=0;
	char ch=0;

//TODO hacerlo para que acepte de mac
	if( ptr_iss == 0){
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

	if( ptr_iss == NULL){
		return 1;
	}
	for(int i=0; !eof; ++i){
		Array <double> current_array (dimension);
		if(st = parse_line_vector(dimension, current_array, ptr_iss)){
			if(st == -1)
				eof = true;
			if(st == 1){
				// Leo hasta el '\n', y le resto a i para que vuelva como estaba
				// delete array
				while( ((ch = (ptr_iss->get())) != '\n') && (ch != EOF));
				--i;
				continue;
			}
			if(st == -2){
				eof = true;
				break;
			}
		}
		if(points_tiberium.getSize() == i){
			//TODO Trabajo con memoria, falta validar
			points_tiberium.append(current_array);	
		}
		else{
			points_tiberium [i] = current_array;
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

	for(int i=0;i<dimension;++i){
		(*ptr_iss)>>aux;
		ch = ptr_iss->get();
		if( (i != dimension-1) && (ch != CSV_DELIMITER) ){
			if(ptr_iss->eof())
				return -1;
			//Campo que no debería ser el ultimo y no sigue con delimitador
			cerr << MSG_ERROR_DELIMITER << endl;
			return 1;
		}
		vector[i] = aux;
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


int main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	int dimension;

	cmdl.parse(argc, argv);
	if(read_points_dimension(dimension,points_stream)){
//  TODO: COMO SE CIERRAN LOS STREAMS?
//		input_stream->close();
//		points_stream->close();
// 		output_stream->close();
		cerr<<MSG_ERR_FIND_DIMENSION<<endl;
		return 1;
	}
	Array <Array <double> > points_tiberium(POINTS_STARTING_SIZE);

	if(load_points(dimension, points_tiberium, points_stream)){
//		delete points_tiberium
//		input_stream->close();
//		points_stream->close();
//		output_stream->close();
		cerr<<MSG_ERR_LOADING_POINTS<<endl;
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
