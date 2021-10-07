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

int factorial(int n)
{
    return (n==0) || (n==1) ? 1 : n* factorial(n-1);
}

init_cond::init_cond(){}

init_cond::init_cond(all_par_set init_AP, std::string init_opt, int init_ord)
{
	this->AP = init_AP;
	this->opt = init_opt;
	this->ord = init_ord;

	vec init_v(2*AP.IP.Xpts.par_int, fill::zeros);

	int_par_dbl_set ip(AP);
	osc_par_dbl_set op(AP);

	if(this->opt=="her")
	{
		double ny = pow(op.m*op.w/M_PI,1/4);
		double nx2 = op.m*op.w;
		double nx = sqrt(nx2);

		for(int i=0; i<this->AP.IP.Xpts.par_int; i++)
		{
			double x = ip.Xmin + i*ip.dX + ip.dX/2;

			init_v(i) = ny/sqrt(factorial(this->ord)*pow(2,this->ord))*exp(-nx2/2*x*x)*hermite(this->ord,nx*x);
		}

/*



		if(this->ord==1)
		{
			for(int i=0; i<this->AP.IP.Xpts.par_int; i++)
			{
				double x = ip.Xmin + i*ip.dX + ip.dX/2;

				init_v(i) = ny/sqrt(2.0)*(2*nx*x)*exp(-nx2/2*x*x);
			}
		}
		else if(this->ord==3)
		{
			for(int i=0; i<this->AP.IP.Xpts.par_int; i++)
			{
				double x = ip.Xmin + i*ip.dX + ip.dX/2;

				init_v(i) = ny/sqrt(48.0)*(8*nx2*nx*x*x*x-12*nx*x)*exp(-nx2/2*x*x);
				double y = hermite(3,x);
				int n = 4;
			}
		}
		else if(this->ord==3)
		{
			for(int i=0; i<this->AP.IP.Xpts.par_int; i++)
			{
				double x = ip.Xmin + i*ip.dX + ip.dX/2;

				init_v(i) = ny/sqrt(48.0)*(8*nx2*nx*x*x*x-12*nx*x)*exp(-nx2/2*x*x);
			}
		}
		else
		{
			cout << "err007: order for inital condition not available";
		}
	*/
	}
	
	else
	{
		cout << "err006: option for inital condition not available";
	}
	this->v = init_v;
}

