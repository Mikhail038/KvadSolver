//Main File

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Core_EquationSolver.h"
#include "Core_EquationSolver.c"



int main (void)
{
    Solutions solution;
    float a = 0, b = 0, c = 0;

    coefficients_input (&a, &b, &c);

    if (is_zero(a))
        linear_solver (b, c, &solution);
    else
        square_solver (a, b, c, &solution);

    solutions_output (&solution);

    return 0;
}











