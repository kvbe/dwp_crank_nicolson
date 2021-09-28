#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <regex>


#include "../hdr/parameter.hpp"


using namespace std;

par_i::par_i(int init_int, 
		 string init_str,
		 string init_tex
		)
{
	par_int = init_int;
	par_str = init_str;
	par_tex = init_tex;
}

//###########################################

par::par(double init_dbl, 
		 string init_str,
		 string init_tex
		)
{
	par_dbl = init_dbl;
	par_str = init_str;
	par_tex = init_tex;
}

par::par(int init_int, 
		 string init_str,
		 string init_tex
		)
{
	par_dbl = (double)init_int;
	par_str = init_str;
	par_tex = init_tex;
}

par::par(bool init_bool, 
		 string init_str,
		 string init_tex
		)
{
	par_dbl = 0.0;
	if(init_bool)
	{
		par_dbl = 1.0;
	}	
	par_str = init_str;
	par_tex = init_tex;
}

par::par(par_i init_par_i)
{
	par_dbl = (double)init_par_i.par_int;
	par_str = init_par_i.par_str;
	par_tex = init_par_i.par_tex;
}

//###########################################

par_cmd::par_cmd(char **be, char **en)
	: begin(be), end(en)
{}

double par_cmd::get_dbl(const string &par_str, double dbl_default)
{
	string new_str = "-" + par_str;
	char **itr = find(begin, end, new_str);

	if (itr != end && ++itr != end)
	{
		char *b;
		double d;
		d = strtod(*itr, &b);
		if (0 == d && *itr == b)
		{
			cout << "Input of "<< par_str << " was wrong. ";
			cout << "Setting to default: "<< dbl_default << endl;
			return dbl_default;
		}
		return d;
	}
	return dbl_default;
}

//###########################################

mode_cmd::mode_cmd(int init_argc, char **init_argv)
{
	argc = init_argc;
	argv = init_argv;
	
	
	for(int i = 1; i < argc; i++)
	{
		cmd_line += argv[i];
	}
	
	regex mode_rgx(R"(-m:(\w*))");
	smatch mode_match;
	
	if(regex_search(cmd_line, mode_match, mode_rgx))
	{
		mode_str = mode_match[1];
	}
	

	if(mode_str == "ts")
	{
		regex ts_rgx(R"(ts\[(.*?)\])");
		smatch ts_match;
		
		if(regex_search(cmd_line, ts_match, ts_rgx))
		{
			par1_str = ts_match[1];
		}
		
	}
	
	
	if(mode_str == "lscan")
	{
		regex lscan_rgx(R"(lscan\[(.*?),(.*?),(.*?),(.*?),(.*?)\])");
		smatch lscan_match;
		
		if(regex_search(cmd_line, lscan_match, lscan_rgx))
		{
		
			par1_str = lscan_match[1];

			par1_start = stod(lscan_match[2]);
			par1_stop  = stod(lscan_match[3]);
			par1_steps = stoi(lscan_match[4]);
			
			par2_str = lscan_match[5];
		}
		
	}
	
	if(mode_str == "maxscan")
	{
		regex maxscan_rgx(R"(maxscan\[(.*?),(.*?),(.*?),(.*?),(.*?)\])");
		smatch maxscan_match;
		
		if(regex_search(cmd_line, maxscan_match, maxscan_rgx))
		{
		
			par1_str = maxscan_match[1];

			par1_start = stod(maxscan_match[2]);
			par1_stop  = stod(maxscan_match[3]);
			par1_steps = stoi(maxscan_match[4]);
			up_down = maxscan_match[5];
			
		}
		
	}
	
	
	
	if(mode_str == "maxsweep")
	{
		regex maxsweep_rgx(R"(maxsweep\[(.*?),(.*?),(.*?),(.*?),(.*?)\])");
		smatch maxsweep_match;
		
		if(regex_search(cmd_line, maxsweep_match, maxsweep_rgx))
		{
		
			par1_str = maxsweep_match[1];

			par1_start = stod(maxsweep_match[2]);
			par1_stop  = stod(maxsweep_match[3]);
			par1_steps = stoi(maxsweep_match[4]);
			up_down = maxsweep_match[5];
			
		}
		
	}
	
	
	if(mode_str == "maxsweep_twopar")
	{
		regex maxsweep_twopar_rgx(R"(maxsweep_twopar\[\[(.*?),(.*?)\],(.*?),(.*?),(.*?),(.*?)\])");
		smatch maxsweep_twopar_match;
		
		if(regex_search(cmd_line, maxsweep_twopar_match, maxsweep_twopar_rgx))
		{
		
			par1_str = maxsweep_twopar_match[1];
			par2_str = maxsweep_twopar_match[2];

			par1_start = stod(maxsweep_twopar_match[3]);
			par1_stop  = stod(maxsweep_twopar_match[4]);
			par1_steps = stoi(maxsweep_twopar_match[5]);
			up_down = maxsweep_twopar_match[6];
			
			
			
		}
		
	}
	
	
	
	if(mode_str == "statesweep")
	{
		regex statesweep_rgx(R"(statesweep\[(.*?),(.*?),(.*?),(.*?),(.*?),(.*?)\])");
		smatch statesweep_match;
		
		if(regex_search(cmd_line, statesweep_match, statesweep_rgx))
		{
		
			par1_str = statesweep_match[1];

			par1_start = stod(statesweep_match[2]);
			par1_stop  = stod(statesweep_match[3]);
			par1_steps = stoi(statesweep_match[4]);
			
			par2_str = statesweep_match[5];
			up_down = statesweep_match[6];
			
			
		}
		
	}
	
}



//###########################################


osc_par_set::osc_par_set(string option)
{
	if(option == "1")
	{
		this->m.par_dbl = 1.0;
		this->w.par_dbl = 1.0;
		this->w2.par_dbl = this->w.par_dbl*this->w.par_dbl;
		this->sb.par_dbl = 1.0;
		this->b0.par_dbl = 1.0;
		this->sr.par_dbl = 1.0;
	}
	else if(option == "also1")
	{
		this->m.par_dbl = 1.0;
		this->w.par_dbl = 1.0;
		this->w2.par_dbl = this->w.par_dbl*this->w.par_dbl;
		this->sb.par_dbl = 1.0;
		this->b0.par_dbl = 1.0;
		this->sr.par_dbl = 1.0;

	}
	else
	{
		cout << "err001: osc_par_set - mode not available" << endl;
	}
}

vector<par> osc_par_set::collect()
{
	vector<par> collection;
	
	collection.push_back(this->m);
	collection.push_back(this->w);
	collection.push_back(this->w2);
	collection.push_back(this->sb);
	collection.push_back(this->b0);
	collection.push_back(this->sr);
	
	return collection;
}

void osc_par_set::cout_pars(vector<par> collection)
{
	for(unsigned i=0; i<collection.size(); i++)
	{
		cout << collection[i].par_str;
		cout << " = ";
		cout << collection[i].par_dbl;
		cout << endl;
	}
}

void osc_par_set::cout_pars()
{
	vector<par> collection = this->collect();

	for(unsigned i=0; i<collection.size(); i++)
	{
		cout << collection[i].par_str;
		cout << " = ";
		cout << collection[i].par_dbl;
		cout << endl;
	}
}

//###########################################


int_par_set::int_par_set(string option)
{
	if(option == "def")
	{
		this->Tmin.par_dbl = 0.0;
		this->Tmax.par_dbl = 1.0;
		this->Tpts.par_int = 2;
		this->dT.par_dbl = 0.5;

		this->Xmin.par_dbl = -1.0;
		this->Xmax.par_dbl = 1.0;
		this->Xpts.par_int = 2;
		this->dX.par_dbl = 1.0;

		//in megabytes
		this->estimated_RAM = 48.0*8e-6;
		this->max_RAM = 1e3;
		this->batches = 0;
		this->divide_in_batches = false;
	}
	else if(option == "quick")
	{
		this->Tmin.par_dbl = 0.0;
		this->Tmax.par_dbl = 4.0;
		this->Tpts.par_int = 50;
		this->dT.par_dbl = (this->Tmax.par_dbl-this->Tmin.par_dbl)/this->Tpts.par_int;

		this->Xmin.par_dbl = -5.0;
		this->Xmax.par_dbl = 5.0;
		this->Xpts.par_int = 50;
		this->dX.par_dbl = (this->Xmax.par_dbl-this->Xmin.par_dbl)/this->Xpts.par_int;

		this->max_RAM = 1e3;


		double CN_RAM = 8.0*this->Xpts.par_int*this->Xpts.par_int;
		CN_RAM += 4.0*this->Xpts.par_int;
		CN_RAM *= 8e-6;

		double IO_RAM = 2*this->Xpts.par_int*this->Tpts.par_int;
		IO_RAM *= 8e-6;

		this->estimated_RAM = CN_RAM + IO_RAM;

		if(this->max_RAM < CN_RAM)
		{
			cout << "err003: too much estimated RAM for the CN matrix" << endl;
		}
		else
		{
			if(this->max_RAM > this->estimated_RAM)
			{
				this->divide_in_batches = false;
				this->batches = 0;
			}
			else
			{
				this->divide_in_batches = true;
				this->batches = ceil(IO_RAM/(this->max_RAM - CN_RAM));

				if(this->batches > this->Tpts.par_int)
				{
					cout << "err004: batch size smaller than time step" << endl;
				}
			}
		}
	}
	else
	{
		cout << "err002: int_par_set - mode not defined" << endl;
	}

}

vector<par> int_par_set::collect()
{
	vector<par> collection;
	
	collection.push_back(this->Tmin);
	collection.push_back(this->Tmax);
	par Tpts_par(this->Tpts);
	collection.push_back(Tpts_par);
	collection.push_back(this->dT);

	collection.push_back(this->Xmin);
	collection.push_back(this->Xmax);
	par Xpts_par(this->Xpts);
	collection.push_back(Xpts_par);
	collection.push_back(this->dX);

	par estimated_RAM_par(this->estimated_RAM,"estimated_RAM","estimated RAM");
	collection.push_back(estimated_RAM_par);

	par max_RAM_par(this->max_RAM,"max_RAM","max RAM");
	collection.push_back(max_RAM_par);

	par divide_in_batches_par(this->divide_in_batches,"divide_in_batches","divide in batches");
	collection.push_back(divide_in_batches_par);

	par batches_par(this->batches,"batches","batches");
	collection.push_back(batches_par);
	
	return collection;
}

void int_par_set::cout_pars(vector<par> collection)
{
	for(unsigned int i = 0; i < collection.size(); i++)
	{
		cout << collection[i].par_str;
		cout << " = ";
		cout << collection[i].par_dbl;
		cout << endl;
	}
}

void int_par_set::cout_pars()
{
	vector<par> collection = this->collect();

	for(unsigned int i = 0; i < collection.size(); i++)
	{
		cout << collection[i].par_str;
		cout << " = ";
		cout << collection[i].par_dbl;
		cout << endl;
	}
}

/*
//###########################################

allpar_set::allpar_set()
{

}

allpar_set::allpar_set(string optL, string optF, string optI)
{
	lpar_set LP_init{optL};
	fpar_set FP_init{optF};
	ipar_set IP_init{optI};

	this->LP = LP_init;
	this->FP = FP_init;
	this->IP = IP_init;
}

allpar_set::allpar_set(lpar_set LP_init, fpar_set FP_init, ipar_set IP_init)
{
	this->LP = LP_init;
	this->FP = FP_init;
	this->IP = IP_init;
}

vector<par> allpar_set::collect()
{
	vector<par> vecLP;
	vector<par> vecFP;
	vector<par> vecIP;
	
	vecLP = this->LP.lpar_set::collect();
	vecFP = this->FP.fpar_set::collect();
	vecIP = this->IP.ipar_set::collect();
	
	vecLP.insert(vecLP.end(), vecFP.begin(), vecFP.end());
	vecLP.insert(vecLP.end(), vecIP.begin(), vecIP.end());

	return vecLP;
}

vector<par*> allpar_set::collect_ptr()
{
	vector<par*> collection;
	
	collection.push_back(&LP.ag);
	collection.push_back(&LP.aq);
	collection.push_back(&LP.Jg);
	collection.push_back(&LP.q0);
	collection.push_back(&LP.rs);
	collection.push_back(&LP.g);
	collection.push_back(&LP.gg);
	collection.push_back(&LP.gq);
	collection.push_back(&LP.sqrtkap);
	collection.push_back(&LP.dw);
	collection.push_back(&LP.T);
	
	collection.push_back(&FP.K);
	collection.push_back(&FP.tau);
	collection.push_back(&FP.wLP);
	
	collection.push_back(&IP.int_time);
	collection.push_back(&IP.out_time);
	collection.push_back(&IP.dt);
	collection.push_back(&IP.sqrtdt);
	collection.push_back(&IP.D);
	
	

	return collection;
}

void allpar_set::cout_pars(vector<par> collection)
{
	for(unsigned int i = 0; i < collection.size(); i++)
	{
		cout << collection[i].par_str;
		cout << " = ";
		cout << collection[i].par_dbl;
		cout << endl;
	}
}

void allpar_set::check_cmd_line(int argc, char* argv[])
{
	par_cmd cmd(argv, argv+argc);
	
	this->LP.ag.par_dbl = cmd.get_dbl(this->LP.ag.par_str, this->LP.ag.par_dbl);
	this->LP.aq.par_dbl = cmd.get_dbl(this->LP.aq.par_str, this->LP.aq.par_dbl);
	this->LP.Jg.par_dbl = cmd.get_dbl(this->LP.Jg.par_str, this->LP.Jg.par_dbl);
	this->LP.q0.par_dbl = cmd.get_dbl(this->LP.q0.par_str, this->LP.q0.par_dbl);
	this->LP.rs.par_dbl = cmd.get_dbl(this->LP.rs.par_str, this->LP.rs.par_dbl);
	this->LP.g.par_dbl = cmd.get_dbl(this->LP.g.par_str, this->LP.g.par_dbl);
	this->LP.gg.par_dbl = cmd.get_dbl(this->LP.gg.par_str, this->LP.gg.par_dbl);
	this->LP.gq.par_dbl = cmd.get_dbl(this->LP.gq.par_str, this->LP.gq.par_dbl);
	this->LP.sqrtkap.par_dbl = cmd.get_dbl(this->LP.sqrtkap.par_str, this->LP.sqrtkap.par_dbl);
	this->LP.dw.par_dbl = cmd.get_dbl(this->LP.dw.par_str, this->LP.dw.par_dbl);
	this->LP.T.par_dbl = cmd.get_dbl(this->LP.T.par_str, this->LP.T.par_dbl);

	this->FP.K.par_dbl = cmd.get_dbl(this->FP.K.par_str, this->FP.K.par_dbl);
	this->FP.tau.par_dbl = cmd.get_dbl(this->FP.tau.par_str, this->FP.tau.par_dbl);
	this->FP.wLP.par_dbl = cmd.get_dbl(this->FP.wLP.par_str, this->FP.wLP.par_dbl);
	
	this->IP.int_time.par_dbl = cmd.get_dbl(this->IP.int_time.par_str, this->IP.int_time.par_dbl);
	this->IP.out_time.par_dbl = cmd.get_dbl(this->IP.out_time.par_str, this->IP.out_time.par_dbl);
	this->IP.dt.par_dbl = cmd.get_dbl(this->IP.dt.par_str, this->IP.dt.par_dbl);
	this->IP.sqrtdt.par_dbl = cmd.get_dbl(this->IP.dt.par_str, sqrt(this->IP.dt.par_dbl));
	this->IP.D.par_dbl = cmd.get_dbl(this->IP.D.par_str, this->IP.D.par_dbl);
	this->IP.rea.par_dbl = cmd.get_dbl(this->IP.rea.par_str, this->IP.rea.par_dbl);
}

par* allpar_set::get_par_ptr(std::string par_str)
{
	vector<par*> collection = this->collect_ptr();

	
	par out_par{-1.0, "err", "err"};
	par* out_par_ptr = &out_par;
	
	for(unsigned i = 0; i < collection.size(); i++)
	{
		
		if((*collection[i]).par_str == par_str)
		{
			out_par_ptr = collection[i];
		}
	}
	
	if((*out_par_ptr).par_str == "err")
	{
		cout << "err008"<< endl;
	}
	
	
	return out_par_ptr;
}


double allpar_set::larger_delay()
{
	double T1 = this->LP.T.par_dbl;
	double T2 = this->FP.tau.par_dbl;
	double max_tau = T1 < T2 ? T2 : T1; 
	return max_tau;
}

double allpar_set::smaller_delay()
{
	double T1 = this->LP.T.par_dbl;
	double T2 = this->FP.tau.par_dbl;
	double min_tau = T1 > T2 ? T2 : T1; 
	return min_tau;
}

//###########################################

icpar_set::icpar_set(string option)
{
	if(option == "std")
	{
		er_ic.par_dbl = 0.4;
		ei_ic.par_dbl = 0.0;
		g_ic.par_dbl = 4.0;
		q_ic.par_dbl = 1.0;
		j_ic.par_dbl = 1.0;
		
		a1_ic.par_dbl = 2.0;
		a2_ic.par_dbl = 0.0;
		a3_ic.par_dbl = 1.0;
		a4_ic.par_dbl = 1.0;
		a5_ic.par_dbl = 1.0;
		
		b1_ic.par_dbl = 0.0;
		b2_ic.par_dbl = 1.0;
		b3_ic.par_dbl = 0.0;
		b4_ic.par_dbl = 0.0;
		b5_ic.par_dbl = 0.0;
	}
	else
	{
		cout << "err002" << endl;
	}
}

vector<par> icpar_set::collect()
{
	vector<par> collection;
	
	collection.push_back(this->er_ic);
	collection.push_back(this->ei_ic);
	collection.push_back(this->g_ic);
	collection.push_back(this->q_ic);
	collection.push_back(this->j_ic);
	
	collection.push_back(this->a1_ic);
	collection.push_back(this->a2_ic);
	collection.push_back(this->a3_ic);
	collection.push_back(this->a4_ic);
	collection.push_back(this->a5_ic);
	
	collection.push_back(this->b1_ic);
	collection.push_back(this->b2_ic);
	collection.push_back(this->b3_ic);
	collection.push_back(this->b4_ic);
	collection.push_back(this->b5_ic);

	
	return collection;
}

void icpar_set::cout_pars(vector<par> collection)
{
	for(unsigned int i = 0; i < collection.size(); i++)
	{
		cout << collection[i].par_str;
		cout << " = ";
		cout << collection[i].par_dbl;
		cout << endl;
	}
}

void icpar_set::check_cmd_line(int argc, char* argv[])
{
	par_cmd cmd(argv, argv+argc);
	
	this->er_ic.par_dbl = cmd.get_dbl(this->er_ic.par_str, this->er_ic.par_dbl);
	this->ei_ic.par_dbl = cmd.get_dbl(this->ei_ic.par_str, this->ei_ic.par_dbl);
	this->g_ic.par_dbl = cmd.get_dbl(this->g_ic.par_str, this->g_ic.par_dbl);
	this->q_ic.par_dbl = cmd.get_dbl(this->q_ic.par_str, this->q_ic.par_dbl);
	this->j_ic.par_dbl = cmd.get_dbl(this->j_ic.par_str, this->j_ic.par_dbl);
	
	this->a1_ic.par_dbl = cmd.get_dbl(this->a1_ic.par_str, this->a1_ic.par_dbl);
	this->a2_ic.par_dbl = cmd.get_dbl(this->a2_ic.par_str, this->a2_ic.par_dbl);
	this->a3_ic.par_dbl = cmd.get_dbl(this->a3_ic.par_str, this->a3_ic.par_dbl);
	this->a4_ic.par_dbl = cmd.get_dbl(this->a4_ic.par_str, this->a4_ic.par_dbl);
	this->a5_ic.par_dbl = cmd.get_dbl(this->a5_ic.par_str, this->a5_ic.par_dbl);

	this->b1_ic.par_dbl = cmd.get_dbl(this->b1_ic.par_str, this->b1_ic.par_dbl);
	this->b2_ic.par_dbl = cmd.get_dbl(this->b2_ic.par_str, this->b2_ic.par_dbl);
	this->b3_ic.par_dbl = cmd.get_dbl(this->b3_ic.par_str, this->b3_ic.par_dbl);
	this->b4_ic.par_dbl = cmd.get_dbl(this->b4_ic.par_str, this->b4_ic.par_dbl);
	this->b5_ic.par_dbl = cmd.get_dbl(this->b5_ic.par_str, this->b5_ic.par_dbl);
}

//###########################################

lpar_dbl_set::lpar_dbl_set(lpar_set LP)
{
	this->aq = LP.aq.par_dbl;
	this->ag = LP.ag.par_dbl;
	this->Jg = LP.Jg.par_dbl;
	this->q0 = LP.q0.par_dbl;
	this->rs = LP.rs.par_dbl;
	this->g = LP.g.par_dbl;
	this->gg = LP.gg.par_dbl;
	this->gq = LP.gq.par_dbl;
	this->sqrtkap = LP.sqrtkap.par_dbl;
	this->dw = LP.dw.par_dbl;
	this->T = LP.T.par_dbl;
}

lpar_dbl_set::lpar_dbl_set(allpar_set AP)
{
	this->aq = AP.LP.aq.par_dbl;
	this->ag = AP.LP.ag.par_dbl;
	this->Jg = AP.LP.Jg.par_dbl;
	this->q0 = AP.LP.q0.par_dbl;
	this->rs = AP.LP.rs.par_dbl;
	this->g = AP.LP.g.par_dbl;
	this->gg = AP.LP.gg.par_dbl;
	this->gq = AP.LP.gq.par_dbl;
	this->sqrtkap = AP.LP.sqrtkap.par_dbl;
	this->dw = AP.LP.dw.par_dbl;
	this->T = AP.LP.T.par_dbl;
}

//###########################################

fpar_dbl_set::fpar_dbl_set(fpar_set FP)
{
	this->K = FP.K.par_dbl;
	this->tau = FP.tau.par_dbl;
	this->wLP = FP.wLP.par_dbl;
}

fpar_dbl_set::fpar_dbl_set(allpar_set AP)
{
	this->K = AP.FP.K.par_dbl;
	this->tau = AP.FP.tau.par_dbl;
	this->wLP = AP.FP.wLP.par_dbl;
}

//###########################################

ipar_dbl_set::ipar_dbl_set(ipar_set IP)
{
	this->int_time = IP.int_time.par_dbl;
	this->out_time = IP.out_time.par_dbl;
	this->dt = IP.dt.par_dbl;
	this->sqrtdt = IP.sqrtdt.par_dbl;
	this->D = IP.D.par_dbl;
	this->rea = IP.rea.par_dbl;
}

ipar_dbl_set::ipar_dbl_set(allpar_set AP)
{
	this->int_time = AP.IP.int_time.par_dbl;
	this->out_time = AP.IP.out_time.par_dbl;	
	this->dt = AP.IP.dt.par_dbl;
	this->sqrtdt = AP.IP.sqrtdt.par_dbl;
	this->D = AP.IP.D.par_dbl;
	this->rea = AP.IP.rea.par_dbl;
}

*/