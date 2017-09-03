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
#define POINTS_STARTING_SIZE 10

using namespace std;

static void opt_points (string const &arg);
static void opt_input(string const &arg);
static void opt_output(string const &arg);

int read_input_dimension(int &dimension, istream * ptr_iss);
int load_points (int dimension, Array <Array <double> > points_tiberium, istream * ptr_iss);
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

int read_input_dimension(int &dimension, istream * ptr_iss)
{
	int n=0;
	char ch=0;

//TODO hacerlo para que acepte de mac
	if( ptr_iss == 0){
		return 1;
	}

	if( ((*ptr_iss)>>n) && ((ch = ptr_iss->get()) == '\n') ){
		dimension = n;
		return 0;
	}
	if( (n && ch =='\r') && ((ch = ptr_iss->get()) == '\n') ){
		dimension = n;
		return 0;
	}
	return 1;
}

int load_points (int dimension, Array <Array <double> > points_tiberium, istream * ptr_iss)
{
	bool eof=false;
	int st;

	for(int i=0; !eof; ++i){
		Array <int> current_array (dimension);
		if(st = parse_line_vector{dimension, current_array, ptr_iss}){
			if(st == -1)
				eof = true;
			if(st == 1){
				//delete array
				continue;
			}
		}
		points_tiberium [i] = current_array;
	}
}

int parse_line_vector(int dimension, Array <double> & vector, istream * ptr_iss)
{
	double aux;
	char ch;
// TODO: VALIDAR LA LECTURA DEL DOBLE
// TODO: VALIDAR SI HAY MÁS DE UNA COSA DESPUES DEL DELIMITADOR

	if ( vector.getSize != dimension ){
		cerr << MSG_ERROR_CALL_DIMENSION << endl;
		return 1;
	}
	for(int i=0 ; i<dimension-1 ; ++i){
		(*ptr_iss) >> aux;
		if( (ch = ptr_iss->get()) != CSV_DELIMITER ){
			cerr << MSG_ERROR_DELIMITER << endl;
			return 1;
		}
		vector[i] = aux;
	}
	(*ptr_iss) >> aux;
	if( ((ch = ptr_iss->get()) == '\n') || ((ch == '\r') && ((ch = ptr_iss->get()) == '\n'  )){
		// Si ahí termina la linea
		vector[dimension-1] = aux;
		return 0;
	}
	if( ch == EOF){
		vector[dimension-1] = aux;
		return -1;
	}
	
	// Si llego acá, es que no cerro bien la línea
	cerr << MSG_ERROR_LINE << endl;
	return 1;
}

int main(int argc, char * const argv[])
{
	cmdline cmdl(options);
	int dimension;

	cmdl.parse(argc, argv);
	if(read_input_dimension(dimension,input_stream)){
//  TODO: COMO SE CIERRAN LOS STREAMS?
//		input_stream->close();
//		points_stream->close();
// 		output_stream->close();
		cerr<<MSG_ERR_FIND_DIMENSION<<endl;
		return 1;
	}
	Array <Array <double> > points_tiberium(POINTS_STARTING_SIZE);
//	if(load_points(dimension, points_tiberium, input_stream)){
//		delete points_tiberium
//		input_stream->close();
//		points_stream->close();
//		output_stream->close();
//		cerr<<MSG_ERR_FIND_DIMENSION<<endl;
//		return 1;
//	}
	
	return 0;
}
