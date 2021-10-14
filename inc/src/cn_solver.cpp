#include <armadillo>
#include <string>

#include "../hdr/cn_solver.hpp"


using namespace std;
using namespace arma;


double barrier(double x, osc_par_dbl_set op, string barrier_mode)
{
	if(barrier_mode=="gauss")
	{
	    double res = op.b0*exp(-0.5*x*x/(op.sb*op.sb))/(op.sb*sqrt(2*M_PI));
    	return res;
	}
	else if(barrier_mode=="lorentz")
	{
		double res = (op.b0/M_PI)*op.sb/(x*x+op.sb*op.sb);
		return res;
	}
	else
	{
		return 0;
	}
}

double step(double t, osc_par_dbl_set op, string step_mode)
{
	if(step_mode=="tanh")
	{
		double res = (1.0+tanh(op.sr*t))*0.5;
    	return res;
	}
	else if(step_mode=="erf")
	{
	    double res = (1.0+erf(op.sr*t))*0.5;
    	return res;
	}
	else
	{
		return 0;
	}
}

array<sp_mat,2> build_mat(
	double Xpts,
	double Xmin,
	double dX,
	double t,
	double r1,
	double r2,
	double r3,
	osc_par_dbl_set op,
	string barrier_mode,
	string step_mode
)
{
	sp_mat Lmat(Xpts,Xpts);
	sp_mat Rmat(Xpts,Xpts);

	for(unsigned long i=0; i<Xpts; i++)
	{ 
		double x = Xmin + i*dX + dX/2;;
		
		if(i<Xpts-1)
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

        

		Lmat(i,i) += -r3*barrier(x,op,barrier_mode)*step(t,op,step_mode);//sure? not t+dt?

		Rmat(i,i) += r3*barrier(x,op,barrier_mode)*step(t,op,step_mode);
	}

	array<sp_mat,2> RET = {Lmat,Rmat};

	return RET;
}

cn_solver::cn_solver()
{}

cn_solver::cn_solver(all_par_set init_AP)
{
    this->AP = init_AP;
}

cn_solver::cn_solver(int argc, char* argv[])
{
	mode_cmd mode(argc, argv);

	all_par_set init_AP(mode.p_mode_str1, mode.p_mode_str2);
	this->AP = init_AP;

	this->barrier_mode = mode.m_mode_str1;
	this->step_mode = mode.m_mode_str2;
}

cn_solver::cn_solver(all_par_set init_AP, string init_barrier_mode, string init_step_mode)
{
	this->AP = init_AP;
	this->barrier_mode = init_barrier_mode;
	this->step_mode = init_step_mode;
}

cn_solver::cn_solver(string init_osc_mode, string init_int_mode, string init_barrier_mode, string init_step_mode)
{
	all_par_set init_AP(init_osc_mode, init_int_mode);
	this->AP = init_AP;
	
	this->barrier_mode = init_barrier_mode;
	this->step_mode = init_step_mode;
}

vec cn_solver::get_step(arma::vec vec_in, double t)
{
    osc_par_dbl_set op(AP);
    int_par_dbl_set ip(AP);

   	double r1 = ip.dT/(4*op.m*ip.dX*ip.dX);
	double r2 = op.m*op.w2*ip.dT/4;
	double r3 = ip.dT/2;

	sp_mat complex_map(2,2);
	complex_map(0,1) = 1;
	complex_map(1,0) = -1;

	array<sp_mat,2> test = build_mat(
		ip.Xpts,
		ip.Xmin,
		ip.dX,
		t,
		r1,
		r2,
		r3,
		op,
		this->barrier_mode,
		this->step_mode
	);

	sp_mat Lmat(ip.Xpts,ip.Xpts);
	sp_mat Rmat(ip.Xpts,ip.Xpts);

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

        
		Lmat(i,i) += -r3*barrier(x,op,this->barrier_mode)*step(t,op,this->step_mode);//sure? not t+dt?
		Rmat(i,i) += r3*barrier(x,op,this->barrier_mode)*step(t,op,this->step_mode);
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