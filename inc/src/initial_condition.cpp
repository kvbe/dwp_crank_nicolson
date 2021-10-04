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

	int_par_dbl_set ip(AP);
	osc_par_dbl_set op(AP);

	if(this->opt=="her")
	{
		double ny = pow(op.m*op.w/M_PI,1/4);
		double nx2 = op.m*op.w;
		double nx = sqrt(nx2);
		if(this->ord==3)
		{
			for(int i=0; i<this->AP.IP.Xpts.par_int; i++)
			{
				double x = ip.Xmin + i*ip.dX + ip.dX/2;

				init_v(i) = ny/sqrt(48.0)*(8*nx2*nx*x*x*x-12*nx*x)*exp(-nx2/2*x*x);
			}

			this->v = init_v;
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