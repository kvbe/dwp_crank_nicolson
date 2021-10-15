#include <armadillo>
#include <array>
#include <vector>
#include <string>


#include "../hdr/time_stepper.hpp"


using namespace std;
using namespace arma;

time_stepper::time_stepper(int argc, char* argv[])
{
	all_par_set AP(argc, argv);
	cn_solver CN(AP);
	init_cond IC(argc, argv);
}