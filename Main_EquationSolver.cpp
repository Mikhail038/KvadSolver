//Main File

#include "Core_EquationSolver.h"
#include "Core_EquationSolver.cpp"



int main ()
{
    Solutions solution = { .x1 = 0, .x2 = 0, .num = NoSolutions};
    float a = 0, b = 0, c = 0;

    coefficients_input (&a, &b, &c);

    if (is_zero(a))
        linear_solver (b, c, &solution);
    else
        square_solver (a, b, c, &solution);

    solutions_output (&solution);

    return 0;
}








