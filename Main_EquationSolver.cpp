//Main File

#include "Core_EquationSolver.h"
#include "Core_EquationSolver.cpp"
#include "Test_EquationSolver.cpp"


int main ()
{
    int choise = 0;

    printf ("0 - NORMAL 1 - TEST: ");
    scanf ("%d", &choise);

    if (choise == 0)
    {

        float a = 0, b = 0, c = 0;

        coefficients_input (&a, &b, &c);

        if (is_zero(a))
        {
            linear_solver (b, c, p_solution);
        }
        else
            square_solver (a, b, c, p_solution);

        solutions_output (p_solution);
    }
    else
        unittest();

    return 0;
}








