/* Daniel R. Reynolds
   SMU Mathematics
   Math 3316
   1 October 2015 */

// Inclusions
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "matrix.hpp"

using namespace std;


// function prototypes
double Lagrange(Matrix& x, Matrix& y, double z);


// This routine tests the function lagrange.cpp
int main(int argc, char* argv[]) {

  // simple Lambda function for f(x)
  auto f = [](const double x) -> double { 
    return (cosh(2.0*x*x));
  };

  // array of n values for testing
  vector<size_t> nvals = {10, 20};

  // loop over tests
  for (size_t k=0; k<nvals.size(); k++) {

    // set n, output test information
    int n = nvals[k];    
    cout << endl << "interpolants and errors using " << n+1 << " nodes:\n";

    // set arrays of nodes and data values
    Matrix x = Linspace(0.0, 1.0, n+1, 1);  // set column vector of nodes
    Matrix y(n+1);                          // initialize data
    for (int i=0; i<=n; i++)                // fill data
      y(i) = f(x(i));

    // set evaluation points z as midpoints between nodes
    double dx = 1.0/n;                   // set node spacing
    Matrix z = Linspace(dx/2.0, 1.0-dx/2.0, n, 1);
  
    // evaluate the Lagrange polynomial at the points z, storing in p
    Matrix p(n);
    for (int i=0; i<n; i++) 
      p(i) = Lagrange(x, y, z(i));

    // output errors at each point
    cout << "      z        f(z)               p(z)             err\n";
    for (int i=0; i<n; i++) 
      printf("   %6.3f   %16.13f   %16.13f   %7.2g\n", 
	     z(i), f(z(i)), p(i), fabs(f(z(i))-p(i)));
  }

} // end routine
