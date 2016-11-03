/* Daniel R. Reynolds
   SMU Mathematics
   Math 3316
   1 October 2015 */

// Inclusions
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>

#include "matrix.hpp"
#include "Lagrange.hpp"

using namespace std;

// function prototypes
//double Lagrange2D(Matrix& x, Matrix& y, Matrix& z, double a, double b);


// This routine tests the function lagrange2D.cpp.
//int main(int argc, char* argv[]) {
int main() {

  // create Lambda function for f(x,y)
  auto f = [](const double x, const double y) -> double { 
    return (sinh(2.0*x)*cos(3.0*y));
  };


  ///////////////
  // first, test with 11 nodes in each direction
  int m = 10;                               // set m
  int n = 10;                               // set n
  Matrix x = Linspace(-2.0, 2.0, m+1, 1);   // set nodes
  Matrix y = Linspace(-2.0, 2.0, n+1, 1);
  Matrix z(m+1,n+1);                        // initialize data
  for (int j=0; j<=n; j++)  
    for (int i=0; i<=m; i++)
      z(i,j) = f(x(i), y(j));               // fill data

  // set evaluation points (a,b) in a mesh over the domain
  Matrix a = Linspace(-2.0, 2.0, 75, 1);
  Matrix b = Linspace(-2.0, 2.0, 75, 1);

  // output evaluation points to disk
  a.Write("a.txt");
  b.Write("b.txt");

  // evaluate the polynomial at the points (a,b), storing in p
  Matrix p(75,75);
  for (int j=0; j<75; j++) 
    for (int i=0; i<75; i++)
        p(i,j) = Lagrange2D(x, y, z, a[0][i], b[0][j]);

  // output p to disk
  p.Write("p10.txt");

  // evaluate the true function at the points (a,b), storing in ftrue
  Matrix ftrue(75,75);
  for (int j=0; j<75; j++) 
    for (int i=0; i<75; i++) 
      ftrue(i,j) = f(a(i), b(j));

  // output true function to disk
  ftrue.Write("ftrue.txt");


  ///////////////
  // repeate test with 21 nodes in each direction
  m = 20;                                    // set m
  n = 20;                                    // set n
  Matrix x2 = Linspace(-2.0, 2.0, m+1, 1);   // set nodes
  Matrix y2 = Linspace(-2.0, 2.0, n+1, 1);
  Matrix z2(m+1,n+1);                        // initialize data
  for (int j=0; j<=n; j++)  
    for (int i=0; i<=m; i++)
      z2(i,j) = f(x2(i), y2(j));             // fill data

  // evaluate the polynomial at the points (a,b), storing back in p
  for (int j=0; j<75; j++) 
    for (int i=0; i<75; i++)
      p(i,j) = Lagrange2D(x2, y2, z2, a[0][i], b[0][j]);

  // output p to disk
  p.Write("p20.txt");

  return 0;

} // end routine
