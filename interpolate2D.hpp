#ifndef INTERPOLATE2D_DEFINED__
#define INTERPOLATE2D_DEFINED__

#include <string>
#include "matrix.hpp"

double f(double x, double y);
Matrix Chebyshev_nodes(int L, int m);
void interpolate2D(int m, int n, string output_fname, bool Chebyshev);

#endif  // INTERPOLATE2D_DEFINED__