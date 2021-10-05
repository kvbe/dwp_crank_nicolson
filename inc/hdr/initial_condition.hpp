#ifndef __INITIAL_CONDITION_HPP_INCLUDED__
#define __INITIAL_CONDITION_HPP_INCLUDED__

#include "../hdr/parameter.hpp"


class init_cond
{
public:
	all_par_set AP;
	std::string opt;
	int ord;
	arma::vec u;
	arma::vec v;

	init_cond();
	init_cond(all_par_set, std::string, int);
};

#endif
