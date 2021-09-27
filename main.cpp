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



int main(int argc, char* argv[])
{
	timer time_total;

	mat X(10,10,fill::eye);
	X.print();

//	mat Y = X.i();
//	Y.print();


	double Tmin = 0.0;
	double Tmax = 8.0;
	long unsigned Tpts = 7;

	double dT = (Tmax - Tmin)/Tpts;


	double Xmin = -1.5;
	double Xmax = 1.5;
	long unsigned Xpts = 7;

	double dX = (Xmax - Xmin)/Xpts;



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
		double x = Xmin+i*dX+dX/2;
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
	RR = RR + I;

	mat mLL(LL);
	mat mRR(RR);

//	mat RES;
//	mat X = mLL.i();

	mLL.print();
	cout << "\n\n";
	mRR.print();
	cout << "\n\n";

	cout << r1 << endl;




	time_total.stop();
	time_total.print_elaps();
	return 0;
}



