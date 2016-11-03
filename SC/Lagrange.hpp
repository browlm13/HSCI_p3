#ifndef LAGRANGE_DEFINED__
#define LAGRANGE_DEFINED__

double Lagrange_basis(Matrix& x, int i, double z);
double Lagrange(Matrix& x, Matrix& y, double z);
double Lagrange2D(Matrix x, Matrix y, Matrix f, double a, double b);

#endif  // LAGRANGE_DEFINED__