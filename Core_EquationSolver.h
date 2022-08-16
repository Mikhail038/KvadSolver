//Header File

#ifndef CORE_EQUATION_SOLVER_H
#define CORE_EQUATION_SOLVER_H


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>


enum Cases
{
    InfiniteSolutions = -1,
    NoSolutions =        0,
    OneSolution =        1,
    TwoSolutions =       2
};

typedef struct Solutions
{
    float x1;
    float x2;
    enum Cases num;
} Solutions;


void coefficients_input (float *a, float *b, float *c);
bool is_zero (float x);
void linear_solver (float b, float c, Solutions *p_solution);
void square_solver (float a, float b, float c, Solutions *p_solution);
void solutions_output (Solutions *p_solution);


#endif
