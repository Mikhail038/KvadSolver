//Core File


#ifndef P_CORE_E_S_CPP
#define P_CORE_E_S_CPP

#include "pCoreES.h"

void equation_solver (const float a,const float b, const float c, Solutions* p_solution)
{
    if (is_zero(a))
        linear_solver (b, c, p_solution);
    else
        square_solver (a, b, c, p_solution);
}

void clear_input (void)
{
    while (getchar() != '\n');
}

void coefficients_input (float* p_a, float* p_b, float* p_c)
{
    vMCA((p_a != NULL), NULL_POINTER);
    vMCA((p_b != NULL), NULL_POINTER);
    vMCA((p_c != NULL), NULL_POINTER);

    printf ("Enter three coefficients of equation: ");
    while (scanf ("%f %f %f", p_a, p_b, p_c) != 3)
    {
        clear_input ();
        printf("Please enter three numbers: ");
    }
}

bool is_zero (const float x)
{
    MCA ((isfinite(x)), IS_NOT_FINITE);

    const float approximate_zero = (float)1e-5;

    return (fabs (x) <= approximate_zero);
}

void linear_solver (const float b,const float c, Solutions* p_solution)
{
    vMCA((p_solution != NULL), NULL_POINTER);
    vMCA((isfinite (b)), IS_NOT_FINITE);
    vMCA((isfinite (c)), IS_NOT_FINITE);
    v_assert_p_solution;

    p_solution->num = NoSolutions;
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

void square_solver (const float a, const float b, const float c, Solutions* p_solution)      // const везде
{
    vMCA((p_solution != NULL), NULL_POINTER);
    vMCA((isfinite(a)), IS_NOT_FINITE);
    vMCA((isfinite(b)), IS_NOT_FINITE);
    vMCA((isfinite(c)), IS_NOT_FINITE);
    v_assert_p_solution;

    p_solution->num = NoSolutions;
    p_solution->x1 = 0;
    p_solution->x2 = 0;

    const float discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        p_solution->num = NoSolutions;
    else if (is_zero(b) && is_zero(c))
    {
        p_solution->num = OneSolution;
        p_solution->x1 = 0;
    }
    else if (is_zero(discriminant))
    {
        const float doubled_a = 2 * a;

        p_solution->num = OneSolution;
        p_solution->x1 = -b / doubled_a;
    }
    else
    {
        const float doubled_a = 2 * a;
        const float sqr_discr = sqrtf (discriminant);

        p_solution->num = TwoSolutions;
        p_solution->x1 = (-b - sqr_discr) / doubled_a;
        p_solution->x2 = (-b + sqr_discr) / doubled_a;
    }
}

void solutions_output (Solutions* p_solution)
{
    vMCA((p_solution != NULL), NULL_POINTER);
    v_assert_p_solution;

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

