#ifndef __PARAMETER_HPP_INCLUDED__
#define __PARAMETER_HPP_INCLUDED__


class par_i
{
public:
	int par_int;
	std::string par_str;
	std::string par_tex;

	par_i(int init_int, 
	    std::string init_str,
	    std::string init_tex
	   );
};

//###########################################

class par
{
public:
	double par_dbl;
	std::string par_str;
	std::string par_tex;

	par(double init_dbl, 
	    std::string init_str,
	    std::string init_tex
	   );
	par(int init_int, 
	    std::string init_str,
	    std::string init_tex
	   );
	par(bool init_bool, 
	    std::string init_str,
	    std::string init_tex
	   );
	par(par_i init_par_i);
};

//###########################################

class par_cmd
{
	char **begin;
	char **end;
public:
	par_cmd(char **be,char **en);
	double get_dbl(const std::string&, double);
};

//###########################################

class mode_cmd
{
	char **argv;
	int argc;
	
public:
	std::string cmd_line;
	std::string mode_str;

	std::string par1_str;
	std::string par2_str;
	
	double par1_start;
	double par1_stop;
	int par1_steps;
	
	std::string up_down;
	
	mode_cmd(int, char**);
};

//###########################################

class osc_par_set
{
public:
	par m{1.0, "m", "m"};
	par w{1.0, "w", "\\omega"};
	par w2{1.0, "w2", "\\omega^2"};
	par sb{1.0, "sb", "\\sigma_b"};
	par b0{1.0, "b0", "b_0"};
	par sr{1.0, "sr", "s_r"};

	osc_par_set(std::string option);

	std::vector<par> collect();
	void cout_pars(std::vector<par> collection);
	void cout_pars();
};

//###########################################

class int_par_set
{
public:
	par Tmin{0.0, "Tmin", "t_{\\text{min}}"};
	par Tmax{1.0, "Tmax", "t_{\\text{max}}"};
	par_i Tpts{2, "Tpts", "t_{\\text{pts}}"};
	par dT{0.5, "dT", "\\Delta t"};

	par Xmin{-1.0, "Xmin", "x_{\\text{min}}"};
	par Xmax{1.0, "Xmax", "x_{\\text{max}}"};
	par_i Xpts{2, "Xpts", "x_{\\text{pts}}"};
	par dX{1.0, "dX", "\\Delta x"};

	double estimated_RAM = 44.0*8.0*1e-6;
	double max_RAM = 1e3;
	int batches = 0;
	bool divide_in_batches = false;

	int_par_set(std::string option);
	
	std::vector<par> collect();
	void cout_pars(std::vector<par> collection);
	void cout_pars();
};

//###########################################

class all_par_set
{
public:
	osc_par_set OP{"def"};
	int_par_set IP{"def"};
	
	all_par_set();
	all_par_set(std::string optO, std::string optI);
	all_par_set(osc_par_set OP_init, int_par_set IP_init);

	
	std::vector<par> collect();
	std::vector<par*> collect_ptr();
	void cout_pars(std::vector<par> collection);
	void cout_pars();


	void check_cmd_line(int argc, char* argv[]);
	par* get_par_ptr(std::string);
};

//###########################################

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




#endif
