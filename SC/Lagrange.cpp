/* Daniel R. Reynolds
   SMU Mathematics
   Math 3316
   30 September 2015 */

// Inclusions
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "matrix.hpp"

using namespace std;


// Utility function to evaluate a given Lagrange basis function at a point, phi_i(z).
//
// Usage: l = Lagrange_basis(x, i, z);
//
// inputs:   x     Matrix of length n+1, containing the interpolation nodes
//           i     integer indicating which Lagrange basis function to evaluate
//           z     double location to evaluate basis function
// outputs:  p     value of phi_i(z)
// 
double Lagrange_basis(Matrix& x, int i, double z) {
  double l = 1.0;              // initialize basis function
  for (size_t j=0; j<x.Size(); j++)
     //if (j != i && x(i) != x(j))
    if (j != i)
       l *= (z - x(j)) / (x(i) - x(j));
  return l;
}

// This routine evaluates the Lagrange interpolating polynomial, 
// defined over a set of data points (x_i,y_i), i=0,...,n, at a point z.
//
// Usage: p = Lagrange(x, y, z);
//
// inputs:   x     Matrix of length n+1, containing the interpolation nodes
//           y     Matrix of length n+1, containing the interpolation data
//           z     double location to evaluate polynomial
// outputs:  p     value of p(z)
// 
double Lagrange(Matrix& x, Matrix& y, double z) {

  // check input arguments (lengths of x and y)
  if (x.Size() != y.Size()) {
    cerr << "Lagrange error: x and y have different lengths!\n";
    return 0.0;
  }

  // evaluate p
  double p = 0.0;                       // initialize result
  for (size_t i=0; i<x.Size(); i++)     // loop over data values
    p += y(i)*Lagrange_basis(x, i, z);  // update result with next term

  // return final result
  return p;

} // end of function

/*
    Laurence Browns Lagrange2D function
*/
double Lagrange2D(Matrix x, Matrix y, Matrix f, double a, double b){
  double result = 0.0;

  for (int i=0; i<x.Size(); i++){
    for (int j=0; j<y.Size(); j++){
      result += f(i, j) * Lagrange_basis(x, i, a) * Lagrange_basis(y, j, b);

      /*
      cout << "f(i,j):" << f(i, j) << endl;
      cout << "Lagrange_basis(x,i,a):" << Lagrange_basis(x, i, a) << endl;
      cout << "Lagrange_basis(y,j,b):" << Lagrange_basis(y, j, b) << endl;
      cout << "result:" << result << endl;
      */

    }
  }

  return result;
}
