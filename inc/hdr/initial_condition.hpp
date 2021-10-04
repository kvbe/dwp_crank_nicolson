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

	init_cond(all_par_set, std::string, int);
};


/*

class icpar_set
{
public:
	par er_ic{0.0, "er_ic", "er_ic"};
	par ei_ic{0.0, "ei_ic", "ei_ic"};
	par g_ic{0.0, "g_ic"  , "g_ic"};
	par q_ic{0.0, "q_ic"  , "q_ic"};
	par j_ic{0.0, "j_ic"  , "j_ic"};
	
	par a1_ic{0.0, "a1_ic", "a1_ic"};
	par a2_ic{0.0, "a2_ic", "a2_ic"};
	par a3_ic{0.0, "a3_ic", "a3_ic"};
	par a4_ic{0.0, "a4_ic", "a4_ic"};
	par a5_ic{0.0, "a5_ic", "a5_ic"};
	
	par b1_ic{0.0, "b1_ic", "b1_ic"};
	par b2_ic{0.0, "b2_ic", "b2_ic"};
	par b3_ic{0.0, "b3_ic", "b3_ic"};
	par b4_ic{0.0, "b4_ic", "b4_ic"};
	par b5_ic{0.0, "b5_ic", "b5_ic"};
		
	
	icpar_set(std::string option);
	
	std::vector<par> collect();
	void cout_pars(std::vector<par> collection);
	
	void check_cmd_line(int argc, char* argv[]);
};


//###########################################

class osc_par_dbl_set
{
public:
	double ag;
	double aq;
	double Jg;
	double q0;
	double rs;
	double g;
	double gg;
	double gq;
	double sqrtkap;
	double dw;
	double T;

	osc_par_dbl_set(osc_par_set init_OP);
	osc_par_dbl_set(all_par_set init_AP);
};

//###########################################

class int_par_dbl_set
{
public:
	double int_time;
	double out_time;
	double dt;
	double sqrtdt;
	double D;
	double rea;

  
	ipar_dbl_set(ipar_set IP);
	ipar_dbl_set(allpar_set AP);
};


*/

#endif
