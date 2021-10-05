#ifndef __CN_SOLVER_HPP_INCLUDED__
#define __CN_SOLVER_HPP_INCLUDED__

#include "../hdr/parameter.hpp"
#include "../hdr/initial_condition.hpp"


class cn_solver
{
public:
	all_par_set AP;

	cn_solver();
	cn_solver(all_par_set);

	arma::vec get_step(arma::vec, double);
};

#endif
