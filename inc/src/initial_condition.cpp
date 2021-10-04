#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include <regex>

#include <armadillo>

#include "../hdr/initial_condition.hpp"


using namespace std;
using namespace arma;


init_cond::init_cond(all_par_set init_AP, std::string init_opt, int init_ord)
{
	this->AP = init_AP;
	this->opt = init_opt;
	this->ord = init_ord;

	vec init_v(AP.IP.Xpts.par_int, fill::zeros);

	if(this->opt=="her")
	{
		if(this->ord==3)
		{
			for(int i=0; i<this->AP.IP.Xpts.par_int; i++)
			{
				double x = 0;//this->AP.IP.Xmin.par_dbl + (this->AP.IP.Xmax.par_dbl-this->AP.IP.Xmin.par_dbl)*this->AP.IP.Xmin.par_dbl*i
				cout << i << "\t" << x << "\t" << init_v(i) << endl;
			}
		}
		else
		{
			cout << "err007: order for inital condition not available";
		}
	}
	else
	{
		cout << "err006: option for inital condition not available";
	}
}


/*

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