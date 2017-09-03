// 
// Con este programa se genera el archivo de entrada y el de consultas
// TODO logica para escribir las bases de datos // CLA con el archivo donde meter las cosas

#include <iostream>
#include <cstdlib>

#include <cmdline.h>


// ======= GLOBAL VARS =======
// option_t: has args, short name,long name,default value, parser,flags
static option_t options[] = {
	{1, "n", "num_entries", NULL, opt_entries, OPT_MANDATORY},
	{1, "d", "dimension", "-", opt_dimension, OPT_DEFAULT},
	{0, "E", "plus_dimension", NULL, opt_plus, OPT_DEFAULT},
	{0, "e", "minus_dimension", NULL, opt_minus, OPT_DEFAULT},
	{0, "h", "help", NULL, opt_help, OPT_DEFAULT},
	{0, },
};

static int num_entries;
static int num_dimensions;
static bool flag_error_plus_dimension = false;
static bool flag_error_minus_dimension = false;

// ======= Parse functions =======

int StrToInt (std::string const & s)
{
	int n;
	char *p;

	return strtol(c_str(s),NULL,10);
}

void opt_entries (std::string const & s)
{
	num_entries = StrToInt(s);
}

void opt_dimension (std::string const & s)
{
	dimension = StrToInt(s);
}

void opt_minus (std::string const & s)
{
	flag_error_minus_dimension = true;
}

void opt_minus (std::string const & s)
{
	flag_error_minus_dimension = true;
}


int main (int argc, char* argv[])
{
	cmdline cmdl(options);
	
	cmdl.parse(argc, argv);
	

	return 0;
}

