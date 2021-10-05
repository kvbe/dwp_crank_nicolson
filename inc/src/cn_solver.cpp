#include <armadillo>

#include "../hdr/cn_solver.hpp"


using namespace std;
using namespace arma;

cn_solver::cn_solver()
{}

cn_solver::cn_solver(all_par_set init_AP)
{
    this->AP = init_AP;
}

vec cn_solver::get_step(arma::vec vec_in, double t)
{
    osc_par_dbl_set op(AP);
    int_par_dbl_set ip(AP);

   	double r1 = ip.dT/(4*op.m*ip.dX*ip.dX);
	double r2 = op.m*op.w2*ip.dT/4;
	double r3 = ip.dT/2;

    cout << r1*r2*r3 << endl;

	sp_mat Lmat(ip.Xpts,ip.Xpts);
	sp_mat Rmat(ip.Xpts,ip.Xpts);
	
	sp_mat complex_map(2,2);
	complex_map(0,1) = 1;
	complex_map(1,0) = -1;

    for(unsigned long i=0; i<ip.Xpts; i++)
	{
        /*
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
        */
	}



    vec vec_out(3);
    return vec_out;
}
