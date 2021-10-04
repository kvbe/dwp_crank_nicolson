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

//###########################################

all_par_set::all_par_set()
{}

all_par_set::all_par_set(string optO, string optI)
{
	osc_par_set OP_init{optO};
	int_par_set IP_init{optI};

	this->OP = OP_init;
	this->IP = IP_init;
}

all_par_set::all_par_set(osc_par_set OP_init, int_par_set IP_init)
{
	this->OP = OP_init;
	this->IP = IP_init;
}

vector<par> all_par_set::collect()
{
	vector<par> vecOP = this->OP.osc_par_set::collect();
	vector<par> vecIP = this->IP.int_par_set::collect();

	vecOP.insert(vecOP.end(), vecIP.begin(), vecIP.end());

	return vecOP;
}

vector<par*> all_par_set::collect_ptr()
{
	vector<par*> collection;

	collection.push_back(&OP.m);
	collection.push_back(&OP.w);
	collection.push_back(&OP.w2);
	collection.push_back(&OP.sb);
	collection.push_back(&OP.b0);
	collection.push_back(&OP.sr);
	
	collection.push_back(&IP.Tmin);
	collection.push_back(&IP.Tmax);
	collection.push_back(&IP.dT);

	collection.push_back(&IP.Xmax);
	collection.push_back(&IP.Xmin);
	collection.push_back(&IP.dX);

	return collection;
}

void all_par_set::cout_pars(vector<par> collection)
{
	for(unsigned int i = 0; i < collection.size(); i++)
	{
		cout << collection[i].par_str;
		cout << " = ";
		cout << collection[i].par_dbl;
		cout << endl;
	}
}

void all_par_set::cout_pars()
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

void all_par_set::check_cmd_line(int argc, char* argv[])
{
	par_cmd cmd(argv, argv+argc);
	
	this->OP.m.par_dbl = cmd.get_dbl(this->OP.m.par_str, this->OP.m.par_dbl);
	this->OP.w.par_dbl = cmd.get_dbl(this->OP.w.par_str, this->OP.w.par_dbl);
	this->OP.w2.par_dbl = this->OP.w.par_dbl * this->OP.w.par_dbl;
	this->OP.sb.par_dbl = cmd.get_dbl(this->OP.sb.par_str, this->OP.sb.par_dbl);
	this->OP.b0.par_dbl = cmd.get_dbl(this->OP.b0.par_str, this->OP.b0.par_dbl);
	this->OP.sr.par_dbl = cmd.get_dbl(this->OP.sr.par_str, this->OP.sr.par_dbl);

	this->IP.Tmin.par_dbl = cmd.get_dbl(this->IP.Tmin.par_str, this->IP.Tmin.par_dbl);
	this->IP.Tmax.par_dbl = cmd.get_dbl(this->IP.Tmax.par_str, this->IP.Tmax.par_dbl);
	this->IP.Tpts.par_int = cmd.get_dbl(this->IP.Tpts.par_str, this->IP.Tpts.par_int);
	this->IP.dT.par_dbl = cmd.get_dbl(this->IP.dT.par_str, this->IP.dT.par_dbl);

	this->IP.Xmin.par_dbl = cmd.get_dbl(this->IP.Xmin.par_str, this->IP.Xmin.par_dbl);
	this->IP.Xmax.par_dbl = cmd.get_dbl(this->IP.Xmax.par_str, this->IP.Xmax.par_dbl);
	this->IP.Xpts.par_int = cmd.get_dbl(this->IP.Xpts.par_str, this->IP.Xpts.par_int);
	this->IP.dX.par_dbl = cmd.get_dbl(this->IP.dX.par_str, this->IP.dX.par_dbl);

	this->IP.max_RAM = cmd.get_dbl("max_RAM", this->IP.max_RAM);


	double CN_RAM = 8.0*this->IP.Xpts.par_int*this->IP.Xpts.par_int;
	CN_RAM += 4.0*this->IP.Xpts.par_int;
	CN_RAM *= 8e-6;

	double IO_RAM = 2*this->IP.Xpts.par_int*this->IP.Tpts.par_int;
	IO_RAM *= 8e-6;

	this->IP.estimated_RAM = CN_RAM + IO_RAM;

	if(this->IP.max_RAM < CN_RAM)
	{
		cout << "err003: too much estimated RAM for the CN matrix" << endl;
	}
	else
	{
		if(this->IP.max_RAM > this->IP.estimated_RAM)
		{
			this->IP.divide_in_batches = false;
			this->IP.batches = 0;
		}
		else
		{
			this->IP.divide_in_batches = true;
			this->IP.batches = ceil(IO_RAM/(this->IP.max_RAM - CN_RAM));

			if(this->IP.batches > this->IP.Tpts.par_int)
			{
				cout << "err004: batch size smaller than time step" << endl;
			}
		}
	}
}

par* all_par_set::get_par_ptr(std::string par_str)
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
		cout << "err005"<< endl;
	}
	
	
	return out_par_ptr;
}

//###########################################

osc_par_dbl_set::osc_par_dbl_set(osc_par_set init_OP)
{
	this->m = init_OP.m.par_dbl;
	this->w = init_OP.w.par_dbl;
	this->w2 = init_OP.w.par_dbl*init_OP.w.par_dbl;
	this->sb = init_OP.sb.par_dbl;
	this->b0 = init_OP.b0.par_dbl;
	this->sr = init_OP.sr.par_dbl;
}

osc_par_dbl_set::osc_par_dbl_set(all_par_set init_AP)
{
	this->m = init_AP.OP.m.par_dbl;
	this->w = init_AP.OP.w.par_dbl;
	this->w2 = init_AP.OP.w.par_dbl*init_AP.OP.w.par_dbl;
	this->sb = init_AP.OP.sb.par_dbl;
	this->b0 = init_AP.OP.b0.par_dbl;
	this->sr = init_AP.OP.sr.par_dbl;
}

//###########################################

int_par_dbl_set::int_par_dbl_set(int_par_set init_IP)
{
	this->Tmin = init_IP.Tmin.par_dbl;
	this->Tmax = init_IP.Tmax.par_dbl;
	this->Tpts = (double) init_IP.Tpts.par_int;
	this->dT = init_IP.dT.par_dbl;

	this->Xmin = init_IP.Xmin.par_dbl;
	this->Xmax = init_IP.Xmax.par_dbl;
	this->Xpts = (double) init_IP.Xpts.par_int;
	this->dX = init_IP.dX.par_dbl;
}

int_par_dbl_set::int_par_dbl_set(all_par_set init_AP)
{
	this->Tmin = init_AP.IP.Tmin.par_dbl;
	this->Tmax = init_AP.IP.Tmax.par_dbl;
	this->Tpts = (double) init_AP.IP.Tpts.par_int;
	this->dT = init_AP.IP.dT.par_dbl;

	this->Xmin = init_AP.IP.Xmin.par_dbl;
	this->Xmax = init_AP.IP.Xmax.par_dbl;
	this->Xpts = (double) init_AP.IP.Xpts.par_int;
	this->dX = init_AP.IP.dX.par_dbl;
}