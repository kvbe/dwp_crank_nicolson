#ifndef __TIME_STEPPER_HPP_INCLUDED__
#define __TIME_STEPPER_HPP_INCLUDED__

#include "../hdr/parameter.hpp"
#include "../hdr/initial_condition.hpp"
#include "../hdr/cn_solver.hpp"



class time_stepper
{
public:
	all_par_set AP();
	cn_solver CN();
	init_cond IC();

	time_stepper(int argc, char* argv[]);

	std::vector<std::vector<double> > get_batch();
};

#endif
