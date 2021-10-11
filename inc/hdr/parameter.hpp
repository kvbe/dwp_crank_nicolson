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

	std::string p_mode_str1;
	std::string p_mode_str2;

	std::string m_mode_str1;
	std::string m_mode_str2;

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

	friend std::vector<double> estimate_batches(int, int, double);
};

//###########################################

class all_par_set
{
public:
	osc_par_set OP{"def"};
	int_par_set IP{"def"};
	
	all_par_set();
	all_par_set(int argc, char* argv[]);
	all_par_set(std::string optO, std::string optI);
	all_par_set(osc_par_set OP_init, int_par_set IP_init);

	
	std::vector<par> collect();
	std::vector<par*> collect_ptr();
	void cout_pars(std::vector<par> collection);
	void cout_pars();
	void check_cmd_line(int argc, char* argv[]);
	par* get_par_ptr(std::string);

	friend std::vector<double> estimate_batches(int, int, double);
};

//###########################################

class osc_par_dbl_set
{
public:
	double m;
	double w;
	double w2;
	double sb;
	double b0;
	double sr;

	osc_par_dbl_set(osc_par_set init_OP);
	osc_par_dbl_set(all_par_set init_AP);
};

//###########################################

class int_par_dbl_set
{
public:
	double Tmin;
	double Tmax;
	double Tpts;
	double dT;

	double Xmin;
	double Xmax;
	double Xpts;
	double dX;
  
	int_par_dbl_set(int_par_set init_IP);
	int_par_dbl_set(all_par_set init_AP);
};

#endif
