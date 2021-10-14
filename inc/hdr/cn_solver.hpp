#ifndef __CN_SOLVER_HPP_INCLUDED__
#define __CN_SOLVER_HPP_INCLUDED__

#include "../hdr/parameter.hpp"
#include "../hdr/initial_condition.hpp"


class cn_solver
{
public:
	all_par_set AP{"def","def"};

	std::string barrier_mode;
	std::string step_mode;

	cn_solver();
	cn_solver(int argc, char* argv[]);
	cn_solver(all_par_set);
	cn_solver(all_par_set, std::string, std::string);
	cn_solver(std::string, std::string, std::string, std::string);


	arma::vec get_step(arma::vec, double);

	friend std::array<arma::sp_mat,2> build_mat(
		double,
		double,
		double,
		double,
		double,
		double,
		double,
		osc_par_dbl_set,
		std::string,
		std::string
	);

	friend double barrier(double, osc_par_dbl_set, std::string);
	friend double step(double, osc_par_dbl_set, std::string);


	friend double barrier_gauss(double, osc_par_dbl_set);
	friend double step_tanh(double, osc_par_dbl_set);
	friend double step_erf(double, osc_par_dbl_set);
};

#endif
