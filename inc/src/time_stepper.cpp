#include <armadillo>
#include <array>
#include <vector>
#include <string>


#include "../hdr/time_stepper.hpp"


using namespace std;
using namespace arma;

time_stepper::time_stepper(int argc, char* argv[])
{
	all_par_set init_AP(argc, argv);
	cn_solver init_CN(init_AP);
	init_cond init_IC(argc, argv);

	this->AP = init_AP;
	this->CN = init_CN;
	this->IC = init_CN;
}

vector<vector<double> > time_stepper::get_batch()
{
	if(this->AP.IP.divide_in_batches==1)
	{}

	vector<vector<double> > a;
	return a
}