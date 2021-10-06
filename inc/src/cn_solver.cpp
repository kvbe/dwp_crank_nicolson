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

double barrier_gauss(double x, osc_par_dbl_set op)
{
    double res = op.b0*exp(-0.5*x*x/(op.sb*op.sb))/(op.sb*sqrt(2*M_PI));
    return res;
}

double barrier_lorentz(double x, osc_par_dbl_set op)
{
    double res = (op.b0/M_PI)*op.sb/(x*x+op.sb*op.sb);
    return res;
}

double step_tanh(double t, osc_par_dbl_set op)
{
    double res = (1.0+tanh(op.sr*t))*0.5;
    return res;
}

double step_erf(double t, osc_par_dbl_set op)
{
    double res = (1.0+erf(op.sr*t))*0.5;
    return res;
}

vec cn_solver::get_step(arma::vec vec_in, double t)
{
    osc_par_dbl_set op(AP);
    int_par_dbl_set ip(AP);

   	double r1 = ip.dT/(4*op.m*ip.dX*ip.dX);
	double r2 = op.m*op.w2*ip.dT/4;
	double r3 = ip.dT/2;

	sp_mat Lmat(ip.Xpts,ip.Xpts);
	sp_mat Rmat(ip.Xpts,ip.Xpts);
	
	sp_mat complex_map(2,2);
	complex_map(0,1) = 1;
	complex_map(1,0) = -1;

    for(unsigned long i=0; i<ip.Xpts; i++)
	{ 
		double x = ip.Xmin + i*ip.dX + ip.dX/2;;
		
		if(i<ip.Xpts-1)
		{
			Lmat(i,i+1) = r1;
			Lmat(i+1,i) = r1;

			Rmat(i,i+1) = -r1;
			Rmat(i+1,i) = -r1;
		}

		Lmat(i,i) = -2*r1;
		Lmat(i,i) += r2*x*x;

		Rmat(i,i) = 2*r1;
		Rmat(i,i) += -r2*x*x;

        
		Lmat(i,i) += -r3*barrier_gauss(x,op)*step_tanh(t,op);//sure? not t+dt?
		Rmat(i,i) += r3*barrier_gauss(x,op)*step_tanh(t,op);
	}


	sp_mat Lspmat2 = kron(complex_map,Lmat);
	sp_mat Rspmat2 = kron(complex_map,Rmat);

	sp_mat I(2*ip.Xpts,2*ip.Xpts);
	I.eye();

	Lspmat2 += I;
	mat Lmat2(Lspmat2);
	
	Rspmat2 += I;
	mat Rmat2(Rspmat2);

 //   vec vec_out(2*ip.Xpts,fill::ones);

//	vec vec_out = ;

    return Lmat2.i()*Rmat2*vec_in;
}
