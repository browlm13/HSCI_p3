#include <string>

//#include "matrix.hpp"
//#include "Lagrange.hpp"
#include "interpolate2D.hpp"

using namespace std;

int main(){

	//Chebyshev_nodes

	int n = 6;
	int m = 6;
	string fname = "p6_Cheb.txt";

	interpolate2D(n,m,fname, true);

	n = 24;
	m = 24;
	fname = "p24_Cheb.txt";

	interpolate2D(n,m,fname, true);

	return 0;
}
