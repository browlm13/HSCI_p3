#include <string>

//#include "matrix.hpp"
//#include "Lagrange.hpp"
//#include "test_Lagrange2d.cpp"
#include "interpolate2D.hpp"

using namespace std;

int main(){

	//uniform

	int n = 6;
	int m = 6;
	string fname = "p6_uni.txt";

	interpolate2D(n,m,fname, false);

	n = 24;
	m = 24;
	fname = "p24_uni.txt";

	interpolate2D(n,m,fname, false);

	return 0;
}
