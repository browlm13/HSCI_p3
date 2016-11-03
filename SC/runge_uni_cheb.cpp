/*
	runge_uni_cheb.cpp
	Laruence M. Brown
  	Math 3316
   	3 November 2016

									Runge Phenominon 
						with uniformly and Chebyshev spaced nodes
*/

#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include "Matrix.hpp"
#include "Lagrange.hpp"

using namespace std;

//settings
#define START_GRID -4
#define END_GRID 4
#define A_LEN 201
#define B_LEN 101

//function prototypes
double 		f(double x, double y);
Matrix 		Chebyshev_nodes(int L, int m);
void 		interpolate2D(int m, int n, Matrix a, Matrix b, string output_fname, bool Chebyshev);

int main(){

	/*
		Create an array of 201 evenly-spaced evaluation points, a, over the interval [−4, 4].
		Output this to disk as the file avals.txt.

		Create an array of 101 evenly-spaced evaluation points, b, over the interval [−4, 4].
		Output this to disk as the file bvals.txt.
	*/
	Matrix as = Linspace(START_GRID, END_GRID, 1, A_LEN);
	as.Write("avals.txt");

	Matrix bs = Linspace(START_GRID, END_GRID, 1, B_LEN);
	bs.Write("bvals.txt");

	/*
		Fill a matrix runge ∈ 201×101 with the correct values of f(ai, bj), and output this to disk
		to a file named Runge.txt.
	*/
	Matrix Runge(as.Cols(), bs.Cols());
	for( int i = 0 ; i < as.Cols(); i++){
		for ( int j=0 ; j < bs.Cols(); j++)
			Runge[j][i] = f(as[i][0], bs[j][0]);
	}
	Runge.Write("Runge.txt");

	interpolate2D(6,6, as, bs, "p6_uni.txt", false);
	interpolate2D(24,24, as, bs,"p24_uni.txt", false);
	interpolate2D(6,6, as, bs,"p6_Cheb.txt", true);
	interpolate2D(24, 24, as, bs, "p24_Cheb.txt", true);

	return 0;
}

//Runge Function
double f(double x, double y){
	return 1 / (1 + x*x + y*y);
}

Matrix Chebyshev_nodes(int m){
	/*
		The (m + 1) Chebyshev nodes over an interval [−L, L] may be computed
		via the formula

		xi = Lcos ((2i + 1)π)/(2m + 2 )), i = 0 ... m
	*/
	Matrix x(1,m+1);
	for(int i =0 ;i <m+1; i++){
		x[i][0]= END_GRID * cos( (2*(i+1)*M_PI)/(2*m+2) );
	}
	return x;
}

void interpolate2D(int m, int n, Matrix a, Matrix b, string output_fname, bool Chebyshev){
	/*
		Create a set of (m + 1) evenly-spaced nodes, x, over the interval [−4, 4].
		Create a set of (n + 1) evenly-spaced nodes, x, over the interval [−4, 4].
	*/
	Matrix x = Linspace(START_GRID, END_GRID, 1, m+1);
	Matrix y = Linspace(START_GRID, END_GRID, 1, n+1);

	if (Chebyshev){
		x = Chebyshev_nodes(m);
		y = Chebyshev_nodes(n);
	}

	/*
		Create a matrix, f ∈ (m+1)×(n+1) that contains the function values f(xi,yj).
	*/
	Matrix z(m+1,n+1);
	for (int i=0; i<m+1; i++){
		for (int j=0; j<n+1; j++)
			z[i][j] = f(x[i][0], y[j][0]);
	}

	/*
		Use your Lagrange2D() function to evaluate the polynomial interpolant p(ai,bj) at
		the 201 × 101 evaluation points, storing the result in a matrix p6 ∈ 201×101.

		Output p6 to disk to a file named p6 uni.txt using the Matrix::Write routine.
	*/
	Matrix pn(a.Cols(), b.Cols());
	for (int i=0; i<a.Cols(); i++){
		for (int j=0; j<b.Cols(); j++){
			pn(i,j) = Lagrange2D(x, y, z, a[i][0], b[j][0]);
		}
	}
	pn.Write(output_fname.c_str());
}
