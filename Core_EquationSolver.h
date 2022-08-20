//Header File


#ifndef CORE_EQUATION_SOLVER_H
#define CORE_EQUATION_SOLVER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>


enum Cases ///  Variable, that keeps data about number of roots and their existing
{
    InfiniteSolutions = -1,
    NoSolutions =        0,
    OneSolution =        1,
    TwoSolutions =       2
};

typedef struct Solutions  /// Variable, that keeps data about solution of equation (in main program)
{
    float x1;
    float x2;
    enum Cases num;
} Solutions;

/// Main program functions
bool assert_solutions (Solutions *p_solution);
void clear_input (void);
void coefficients_input (float *p_a, float *p_b, float *p_c); /// Function for inputting 3 float coefficients. If input is wrong function asks for data again
bool is_zero (float x); /// Function, that compares float and zero. TRUE: float == 0, FALSE: float != 0
void linear_solver (float b, float c, Solutions *p_solution); /// Function, that solves linear equation
void square_solver (float a, float b, float c, Solutions *p_solution); /// Function, that solves square equation
void solutions_output (Solutions *p_solution); /// Function for outputting data about solution of equation



#endif
