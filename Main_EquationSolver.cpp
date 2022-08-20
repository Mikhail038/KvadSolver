//Main File

#include "Core_EquationSolver.h"
#include "Test_EquationSolver.h"
#include "Core_EquationSolver.cpp"
#include "Test_EquationSolver.cpp"


int main ()
{
    int choise = 0;

    printf ("0 - NORMAL 1 - TEST: ");
    scanf ("%d", &choise);

    if (choise == 0)
    {
        Solutions solution = {};
        Solutions *p_solution = &solution;
        float a = 0, b = 0, c = 0;
        bool cycle = false;
        do
        {
            coefficients_input (&a, &b, &c);

            if (is_zero(a))
                linear_solver (b, c, p_solution);
            else
                square_solver (a, b, c, p_solution);

            solutions_output (p_solution);


            printf ("\nAgain? 1 - YES 0 - NO : ");
            scanf ("%d", &cycle);
        } while (cycle);
    }
    else
        unittest();

    return 0;
}


