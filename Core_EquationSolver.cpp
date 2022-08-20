//Core File


#ifndef CORE_EQUATION_SOLVER_CPP
#define CORE_EQUATION_SOLVER_CPP

#include "Core_EquationSolver.h"

bool assert_solutions (Solutions *p_solution)
{
    if (isfinite (p_solution->x1) && isfinite (p_solution->x2) && isfinite ((float)p_solution->num))
        return true;
    else return false;
}

void clear_input (void)
{
    while (getchar() != '\n');
}

void coefficients_input (float *p_a, float *p_b, float *p_c)
{
    assert ((p_a != NULL) && (p_b != NULL) && (p_c != NULL));

    printf ("Enter three coefficients of equation: ");
    while (scanf ("%f %f %f", p_a, p_b, p_c) != 3)
    {
        clear_input ();
        printf("Please enter three numbers: ");
    }
}

bool is_zero (float x)
{
    assert (isfinite (x));

    const approximate_zero = 1e-5;

    if (fabs (x) <= approximate_zero)
        return true;
    else return false;
}

void linear_solver (float b, float c, Solutions *p_solution)
{
    assert (p_solution != NULL);
    assert (isfinite (b) && isfinite (c));
    assert (assert_solutions (p_solution));

    p_solution->num = 0;
    p_solution->x1 = 0;
    p_solution->x2 = 0;

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
    assert (p_solution != NULL);
    assert (isfinite (a) && isfinite (b) && isfinite (c));
    assert (assert_solutions (p_solution));

    p_solution->num = 0; p_solution->x1 = 0; p_solution->x2 = 0;

    const discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        p_solution->num = NoSolutions;
    else if (is_zero(b) && is_zero(c))
    {
        p_solution->num = OneSolution;
        p_solution->x1 = 0;
    }
    else if (is_zero(discriminant))
    {
        const doubled_a = 2 * a;

        p_solution->num = OneSolution;
        p_solution->x1 = -b / doubled_a;
    }
    else
    {
        const doubled_a = 2 * a;
        const sqr_discr = sqrt (discriminant);

        p_solution->num = TwoSolutions;
        p_solution->x1 = (-b - sqr_discr) / doubled_a;
        p_solution->x2 = (-b + sqr_discr) / doubled_a;
    }
}

void solutions_output (Solutions *p_solution)
{
    assert (p_solution != NULL);
    assert (assert_solutions (p_solution));

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
        default:
            break;
    }
}

#endif
