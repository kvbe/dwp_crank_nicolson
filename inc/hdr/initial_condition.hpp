#ifndef __INITIAL_CONDITION_HPP_INCLUDED__
#define __INITIAL_CONDITION_HPP_INCLUDED__

#include "../hdr/parameter.hpp"


class init_cond
{
public:
	all_par_set AP;
	std::string opt;
	int ord;
	arma::vec v;

	init_cond();
	init_cond(int argc, char* argv[]);
	init_cond(all_par_set, std::string, int);
};

//###########################################

class ic_cmd
{
	char **argv;
	int argc;
	
public:
	std::string cmd_line;

	std::string ic_mode;
	int ord;
	
	ic_cmd(int, char**);
};

#endif