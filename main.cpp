#include <iostream>
#include <iomanip>
#include <fstream>

#include <sstream>
#include <string>

#include <cmath>
#include <complex>
#include <vector>
#include <random>
#include <armadillo>


#include <algorithm>
#include <chrono>
#include <ctime>

#include "timer.hpp"
#include "parameter.hpp"
#include "initial_condition.hpp"
#include "cn_solver.hpp"




using namespace std;
using namespace arma;

double barrier(double x)
{
	return 4.0;
}

double step(double t)
{
	return 0.0;
}


double get_x(double dX, double Xmin, long unsigned i)
{
	return Xmin+i*dX+dX/2;
}

double get_uv0(double dX, double Xmin, long unsigned i, string mode)
{
//	double x = Xmin+i*dX+dX/2;

	if(mode=="her3")
	{
		return 1;
	}
	else
	{
		return 0;
	}
	
}



int main(int argc, char* argv[])
{
	timer time_total;

	osc_par_set OP("gauss_std");


//	OP.cout_pars();

	int_par_set IP("Xtest");
//	IP.cout_pars();


	all_par_set AP(OP,IP);

	AP.check_cmd_line(argc,argv);

//	AP.cout_pars();


	init_cond IC(AP,"her",3);

//	IC.v.print();


	cn_solver CN(AP);

	vec test_vec2(2*AP.IP.Xpts.par_int, fill::zeros);	
	
	test_vec2 = CN.get_step(IC.v,0);

	test_vec2.print();

	test();

/*


	double Tmin = 0.0;
	double Tmax = 8.0;
	long unsigned Tpts = 7;

	double dT = (Tmax - Tmin)/Tpts;


	double Xmin = -1.5;
	double Xmax = 1.5;
	long unsigned Xpts = 7;

	double dX = (Xmax - Xmin)/Xpts;

	vec uv(2*Xpts,fill::zeros);
	vec new_uv(Xpts,fill::zeros);


	for(long unsigned i=0; i<2*Xpts; i++)
	{
		if(i<Xpts)
		{
			uv(i) = 0;
		}
		else
		{
			uv(i) = 0;
		}
		 
	}




	double m = 1.0;
	double w = 1.0;

	double r1 = dT/(4*m*dX*dX);
	double r2 = m*w*w*dT/4;
	double r3 = dT/2;


	sp_mat L(Xpts,Xpts);
	sp_mat R(Xpts,Xpts);
	
	sp_mat uv_map(2,2);
	uv_map(0,1) = 1;
	uv_map(1,0) = -1;
	
	int j=1;

	for(unsigned long i=0; i<Xpts; i++)
	{
		double x = get_x(dX,Xmin,i);
		double t = Tmin+j*dT;
		
		if(i<Xpts-1)
		{
			L(i,i+1) = r1;
			L(i+1,i) = r1;

			R(i,i+1) = -r1;
			R(i+1,i) = -r1;
		}

		L(i,i) = -2*r1;
		L(i,i) += r2*x*x;

		R(i,i) = 2*r1;
		R(i,i) += -r2*x*x;


		L(i,i) += -r3*barrier(x)*step(t);
		R(i,i) += r3*barrier(x)*step(t);
	}


	sp_mat LL = kron(uv_map,L);
	sp_mat RR = kron(uv_map,R);

	sp_mat I(2*Xpts,2*Xpts);
	I.eye();

	LL = LL + I;
	mat mLL(LL);
	
	RR = RR + I;
	mat mRR(RR);

	mat RES = mLL.i()*mRR;
	*/

	time_total.stop();
	time_total.print_elaps();

	return 0;
}



