/*

	test_newton.cpp
	Laruence M. Brown
  	Math 3316
   	3 November 2016

									polynomial interpolation
										  newton form

*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

/*
	function prototypes
*/
double 			f(double x);
double 			Newton_nestedform(vector<double> a, vector<double> xnodes, double x);
double 			Newton_basis(vector<double> xnodes, int n, double x);
vector<double> 	Newton_coefficients(vector<double> xnodes, vector<double> ynodes);
vector<double> 	gen_ynodes(vector<double> xnodes);

vector<double> 	Linspace(double a, double b, int n);
double 			sum_vector(vector<double> v);
int 			write(std::vector<double> v, const char *outfile);
void 			print_vector(vector<double> v);


int main(){

	//data set
	vector<double> xnodes = {-2, -1, 0, 1 ,2};					//given xs
	vector<double> ynodes = gen_ynodes(xnodes);					//given ys
	vector<double> as = Newton_coefficients(xnodes, ynodes);	//get coeffients
	vector<double> xs = Linspace(-3,3,201); 					//inputs to function
	vector<double> ps;											//interpolated
	vector<double> fxs;											//actual
	vector<double> err;											//error

	for (int i=0; i<xs.size(); i++){

		//compute f(xi) values
		fxs.push_back(f(xs[i]));

		//compute pn(xi) values
		ps.push_back(Newton_nestedform(as,xnodes,xs[i]));

		//compute error values, |f(xi) - pn(xi)|
		err.push_back(fxs[i]-ps[i]);
	}

	//write to files
	write(xs, "xs.txt");	//inputs
	write(fxs, "fxs.txt");	//f(xi)
	write(ps, "ps.txt");	//pn(xi)
	write(err, "err.txt");	//|f(xi) - pn(xi)|

	return 0;
}

//f(xi) = yi
double f(double x){ 
	//f(x) = 3.1x^4 + 2.3x^3 − 6.6x^2 + 8.7x + 7.9
	return ((3.1) * pow(x,4)) + ((2.3) * pow(x,3)) - ((6.6) * pow(x,2)) + (8.7 *x) + 7.9;
}

//applies function to each element in vector, returns new vector
vector<double> gen_ynodes(vector<double> xnodes){
	//gernerate y nodes: f(x) = 3.1x^4 + 2.3x^3 − 6.6x^2 + 8.7x + 7.9
	vector<double> ynodes;
	for (int i=0; i<xnodes.size(); i++)
		ynodes.push_back(f(xnodes[i]));
	return ynodes;
}

double Newton_basis(vector<double> xnodes, int n, double x){
	//phi_n+1(x) = (xn - x0)(xn - x1) ... (xn - xn-1)
    double phi= 1.0;
    for(int i=0 ; i < n; i++)
        phi*= (x-xnodes[i]);
    return phi;
}

//calulates pn(x) given coefficient matrix and xnodes
double Newton_nestedform(vector<double> a, vector<double> xnodes, double x){
	//p_n(x)= a_0 + a_1(x-x_0)+ a_2(x-x_0)(x-x_1) + ... + a_n(x-x_0)(x-x_1)...(x-x_{n-1})
    double pn=0.0;
    for(int i=0 ; i< a.size(); i++)
        pn+=Newton_basis(xnodes,i, x)*a[i];
    return pn;
}

//calculates a0, a1, ... , an+1 coefficents for newton polynomial given data set
vector<double> Newton_coefficients(vector<double> xnodes, vector<double> ynodes){
	//a_{n+1} = \frac {y_{n+1} − p_n(x_{n+1})} {(x_{n+1} − x_0)(x_{n+1} − x_1)· · ·(x_{n+1} − x_n)}
    vector<double> as;
    for(int i = 0; i< xnodes.size(); i++){
        double numerator = ynodes[i] - Newton_nestedform(as,xnodes, xnodes[i]);
        double denomiator = (Newton_basis(xnodes,i,xnodes[i]));
        as.push_back((numerator)/denomiator);
    }
    return as;
}

/*
	additional functions
*/

//create a new vector of linearly space data
vector<double> Linspace(double a, double b, int n){
	if (n<2) cerr << "Linspace::length must be > 1\n";
	vector<double> v(n);
	
	double h = (b-a)/(n-1);
	for (int i=0; i<n; i++)
	 	v[i] = a + i*h;

	return v;
}

//colapse vector to double, (sum entries)
double sum_vector(vector<double> v){
	double  sum = 0;
	for (int i=0; i<v.size(); i++)
		sum += v[i];
	return sum;
}

//write a vector to a file
int write(std::vector<double> v, const char *outfile) { 

  // open output file
  FILE *fptr = NULL;
  fptr = fopen(outfile, "w");
  if (fptr == NULL) {
    cerr << "Write:: error, unable to open " << outfile << " for writing\n";
    return 1;
  }

  // print data to file
  for (size_t i=0; i<v.size(); i++) {
      fprintf(fptr, "  %.16g", v[i]);
  }

  // close output file and return
  fclose(fptr);
  return 0;
}

//log vector
void print_vector(vector<double> v){
	for (int i=0; i<v.size(); i++)
		cout << v[i] << " ";
	cout << endl;
}
