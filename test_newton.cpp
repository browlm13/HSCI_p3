/*

	polynomial interpollation with newton form

*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;


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


/*
	functions to test
*/

//actual function value
double f(double x){ return ((3.1) * pow(x,4)) + ((2.3) * pow(x,3)) - ((6.6) * pow(x,2)) + (8.7 *x) + 7.9;}

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

double Newton_nestedform(vector<double> a, vector<double> xnodes, double x){
    double pn=0.0;
    for(int i=0 ; i< a.size(); i++)
        pn+=Newton_basis(xnodes,i, x)*a[i];
    return pn;
}

vector<double> Newton_coefficients(vector<double> xnodes, vector<double> ynodes){
    vector<double> as;
    for(int i = 0; i< xnodes.size(); i++){
        double numerator = ynodes[i] - Newton_nestedform(as,xnodes, xnodes[i]);
        double denomiator =(Newton_basis(xnodes,i,xnodes[i]));

        as.push_back((numerator)/denomiator);
    }
    return as;
}
int main(){

	//data set
	vector<double> xnodes = {-2, -1, 0, 1 ,2};		//given xs
	vector<double> ynodes = gen_ynodes(xnodes);		//given ys

	//get coeffients
	vector<double> as = Newton_coefficients(xnodes, ynodes);

	vector<double> xs = Linspace(-3,3,201); //inputs to function
	vector<double> ps;						//interpolated
	vector<double> fxs;						//actual
	vector<double> err;						//error
	for (int i=0; i<xs.size(); i++){

		//compute actual value
		fxs.push_back(f(xs[i]));

		/*
			Newton interpolation
		*/
		ps.push_back(Newton_nestedform(as,xnodes,xs[i]));

		//compute error
		err.push_back(fxs[i]-ps[i]);
	}

	//write inputs to file
	write(xs, "xs.txt");

	//write actual function values
	write(fxs, "fxs.txt");

	//write Newton Ploynomial function values
	write(ps, "ps.txt");

	//write error values
	write(err, "err.txt");

	return 0;
}