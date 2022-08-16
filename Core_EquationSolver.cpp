//Core File

#include "Core_EquationSolver.h"

void coefficients_input (float *p_a, float *p_b, float *p_c)
{
    printf ("Enter three coefficients of equation: ");
    while (scanf ("%f %f %f", p_a, p_b, p_c) != 3)
    {
        while (getchar() != '\n');
        printf("Please enter three numbers: ");
    }
}

bool is_zero (float x)
{
    const approximate_zero = 1e-5;

    if (fabs (x) < approximate_zero)
        return true;
    else return false;
}

void linear_solver (float b, float c, Solutions *p_solution)
{
    if (is_zero(b) && is_zero(c))
        p_solution->num = InfiniteSolutions;
    else if (is_zero(b))
        p_solution->num = NoSolutions;
    else if (is_zero(c))
    {
        p_solution->num = OneSolution;
        p_solution->x1 = 0;
    }
    else
    {
        p_solution->num = OneSolution;
        p_solution->x1 = -c / b;
    }
}

void square_solver (float a, float b, float c, Solutions *p_solution)
{
    float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        p_solution->num = NoSolutions;
    else if (is_zero(b) && is_zero(c))
    {
        p_solution->num = OneSolution;
        p_solution->x1 = 0;
    }
    else if (is_zero(discriminant))
    {
        float doubled_a = 2 * a;

        p_solution->num = OneSolution;
        p_solution->x1 = -b / doubled_a;
    }
    else
    {
        float doubled_a = 2 * a;
        float sqr_discr = sqrt (discriminant);

        p_solution->num = TwoSolutions;
        p_solution->x1 = (-b - sqr_discr) / doubled_a;
        p_solution->x2 = (-b + sqr_discr) / doubled_a;
    }
}

void solutions_output (Solutions *p_solution)
{
    switch (p_solution->num)
    {
    case OneSolution:
        printf ("There is one solution: %f", p_solution->x1);
        break;
    case TwoSolutions:
        printf ("There are two solutions: %f and %f", p_solution->x1, p_solution->x2);
        break;
    case NoSolutions:
        printf ("There are no solutions");
        break;
    case InfiniteSolutions:
        printf ("There are infinite solutions");
        break;
    }
}

