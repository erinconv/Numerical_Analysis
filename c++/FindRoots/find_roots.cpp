#include <iostream>
#include <cmath>
#include "FindRoots_Methods.hpp"

/*
 *------------ Solutions of equations in one variable ------------*
 *Reference:
 *Burden, R. L. and Faires, J. D. (2001). Numerical analysis (7th).
 *Prindle Weber and Schmidt, Boston.
 *----------------------------------------------------------------*
 */


float func(float x)
{
    float val = std::cos(x) - x;
    return val;
}
float dfunc(float x)
{
    float val = -std::sin(x) - 1;
    return val;
}

int main()
{
    float a = 0, b = M_PI / 4, TOL = 1e-10;
    SolutionMethod Solve(&func, &dfunc, a, b, TOL);
    Solve.get_BisectRoot();
    Solve.get_NewtonRoot();
    Solve.get_FalseRoot();
    Solve.get_SecantRoot();
}
