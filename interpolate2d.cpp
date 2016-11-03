#include <string>
#include <vector>
#include <iostream>
#include <math.h>

#include "matrix.hpp"
#include "Lagrange.hpp"
//#include "test_Lagrange2d.cpp"

using namespace std;

double f(double x, double y){return 1/(1+x*x+y*y);}

Matrix Chebyshev_nodes(int L, int m){
	/*
		The (m + 1) Chebyshev nodes over an interval [−L, L] may be computed
		via the formula

		xi = Lcos ((2i + 1)π)/(2m + 2 )), i = 0 ... m
	*/
	
	Matrix Li = Linspace(-L, L, 1, m+1);
	Matrix nodes(m+1);

	for (int i=0; i<m+1; i++){
		double xi = Li[i][0] * cos ( ((2*i + 1)* M_PI) / (2*m + 2) );
		nodes[i][0] = xi;
	}

	return nodes;
}

void interpolate2D(int m, int n, string output_fname, bool Chebyshev = false){

	//settings
	int start_interval = -4;
	int end_interval = 4;
	int a_length = 201;
	int b_length = 101;

	/*

		x nodes and y nodes should  have the option of being evently spaced
		or Chebyshev nodes with given formula
	*/
	/*
		Create a set of (m + 1) evenly-spaced nodes, x, over the interval [−4, 4].
		Create a set of (n + 1) evenly-spaced nodes, x, over the interval [−4, 4].
	*/
	Matrix xnodes = Linspace(start_interval, end_interval, 1, m+1);
	Matrix ynodes = Linspace(start_interval, end_interval, 1, n+1);

	if (Chebyshev){
		xnodes = Chebyshev_nodes(end_interval, m);
		ynodes = Chebyshev_nodes(end_interval, n);
	}

	/*
		Create a matrix, f ∈ (m+1)×(n+1) that contains the function values f(xi,yj).
	*/
	Matrix F(m+1,n+1);
	for (int i=0; i<m+1; i++){
		for (int j=0; j<n+1; j++)
			F[j][i] = f(xnodes[i][0], ynodes[j][0]);
	}

	/*
		Create an array of 201 evenly-spaced evaluation points, a, over the interval [−4, 4].
		Output this to disk as the file avals.txt.

		Create an array of 101 evenly-spaced evaluation points, b, over the interval [−4, 4].
		Output this to disk as the file bvals.txt.
	*/
	Matrix as = Linspace(start_interval, end_interval, 1, a_length);
	as.Write("avals.txt");

	Matrix bs = Linspace(start_interval, end_interval, 1, b_length);
	bs.Write("bvals.txt");
	
	/*
		Use your Lagrange2D() function to evaluate the polynomial interpolant p(ai,bj) at
		the 201 × 101 evaluation points, storing the result in a matrix p6 ∈ 201×101.

		Output p6 to disk to a file named p6 uni.txt using the Matrix::Write routine.
	*/
	Matrix p6(as.Cols(), bs.Cols());
	for (int i=0; i<as.Cols(); i++){
		for (int j=0; j<bs.Cols(); j++)
			p6(i,j) = Lagrange2D(xnodes, ynodes, F, as[i][0], bs[j][0]);
	}
	p6.Write(output_fname.c_str());

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

}