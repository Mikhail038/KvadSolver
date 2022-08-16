#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum Cases
{
InfiniteSolutions = -1,
NoSolutions = 0,
OneSolution = 1,
TwoSolutions = 2
};

struct ASolutions
{
    float x1;
    float x2;
    enum Cases n;
};

typedef struct ASolutions SSolutions;

void coefficients_input (float *a, float *b, float *c);
int zero_comparation (float x);
void linear_solver (float b, float c, SSolutions *p_solution);
void square_solver (float a, float b, float c, SSolutions *p_solution);
void solutions_output (SSolutions solution);




int main (void)
{
    SSolutions solution;
    float a = 0, b = 0, c = 0;

    coefficients_input (&a, &b, &c);

    if (zero_comparation (a) == 0)
        linear_solver (b, c, &solution);
    else
        square_solver (a, b, c, &solution);

    solutions_output (solution);

    return 0;
}

void coefficients_input (float *p_a, float *p_b, float *p_c)
{
    printf ("Enter three coefficients of equation: ");
    while (scanf ("%f %f %f", p_a, p_b, p_c) != 3)
    {
        while (getchar() != '\n')
            printf ("");
        printf("Please enter three numbers: ");
        //fflush (stdin);
    }
}

int zero_comparation (float x)
{
    float approximate_zero = 1e-5;

    if (fabs (x) < approximate_zero)
        return 0;
    else return 1;
}

void linear_solver (float b, float c, SSolutions  *p_solution)
{
    if ((zero_comparation (b) == 0) && (zero_comparation (c) == 0) )
        p_solution->n = InfiniteSolutions;
    else if (zero_comparation (b) == 0)
        p_solution->n = NoSolutions;
    else if (zero_comparation (c) == 0)
    {
        p_solution->n = OneSolution;
        p_solution->x1 = 0;
    }
    else
    {
        p_solution->n = OneSolution;
        p_solution->x1 = -c/b;
    }
}

void square_solver (float a, float b, float c, SSolutions *p_solution)
{
    float discriminant = b*b - 4*a*c;
    float doubled_a = 2*a;
    float sqr_discr = sqrt (discriminant);

    if (discriminant < 0)
        p_solution->n = NoSolutions;
    else if (zero_comparation (discriminant) == 0)
    {
        p_solution->n = OneSolution;
        p_solution->x1 = -b/doubled_a;
    }
    else
    {
        p_solution->n = TwoSolutions;
        p_solution->x1 = (-b - sqr_discr)/doubled_a ;
        p_solution->x2 = (-b + sqr_discr)/doubled_a;
    }
}

void solutions_output (SSolutions solution)
{
    switch (solution.n)
    {
    case OneSolution :
        printf ("There is one solution: %f", solution.x1);
        break;
    case TwoSolutions :
        printf ("There are two solutions: %f and %f", solution.x1, solution.x2);
        break;
    case NoSolutions :
        printf ("There are no solutions");
        break;
    case InfiniteSolutions :
        printf ("There are infinite solutions");
        break;
    }
}










