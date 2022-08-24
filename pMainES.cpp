//Main File

#include "pCoreES.h"
#include "pTextES.h"

int main ()
{

    int choise = 0;

    printf ("0 - NORMAL 1 - TEST: ");
    scanf ("%d", &choise);

    if (choise == 0)
    {
        Solutions solution = {};
        Solutions* p_solution = &solution;
        //printf ("pointer %p\n", p_solution);

        float a = 0, b = 0, c = 0;
        unsigned int running = 0;

        do
        {
            coefficients_input (&a, &b, &c);

            equation_solver (a, b, c, p_solution);

            solutions_output (p_solution);

            printf ("\n" "Again? 1 - YES 0 - NO : ");
            scanf ("%u", &running);

        } while (running);
    }
    else
        unit_test ();

    return 0;
}












