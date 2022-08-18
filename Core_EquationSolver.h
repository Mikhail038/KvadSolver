//Header File


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

#ifndef CORE_EQUATION_SOLVER_H
#define CORE_EQUATION_SOLVER_H


enum Cases
{
    InfiniteSolutions = -1,
    NoSolutions =        0,
    OneSolution =        1,
    TwoSolutions =       2
};

enum TestCases
{
    NoFile = -1,
    NoCoefs = 0,
    Normal =  1
};

typedef struct Solutions
{
    float x1;
    float x2;
    enum Cases num;
} Solutions;

typedef struct EquationTests
{
    float ta, tb, tc;
    float tx1, tx2;
    enum Cases tnum;
} EquationTests;

typedef struct TestAnswers
{
    int ok;
    int all;
} TestAnswers;

Solutions solution = {}; Solutions *p_solution = &solution;

void coefficients_input (float *p_a, float *p_b, float *p_c);
bool is_zero (float x);
void linear_solver (float b, float c, Solutions *p_solution);
void square_solver (float a, float b, float c, Solutions *p_solution);
void solutions_output (Solutions *p_solution);


#endif
