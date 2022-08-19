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

/*enum TestCases /// Variable, that keeps data about COEFS.txt file (file with test information)
{
    NoFile = -1,
    NoCoefs = 0,
    Normal =  1
};*/

typedef struct Solutions  /// Variable, that keeps data about solution of equation (in main program)
{
    float x1;
    float x2;
    enum Cases num;
} Solutions;

typedef struct EquationTests /// Variable, that keeps data about solution of equation (in test program)
{
    float ta, tb, tc;
    float tx1, tx2;
    enum Cases tnum;
} EquationTests;

typedef struct TestAnswers /// Variable, that keeps data about number of right answers and number of tests
{
    int ok;
    int all;
} TestAnswers;

/// Main program functions
void coefficients_input (float *p_a, float *p_b, float *p_c); /// Function for inputting 3 float coefficients. If input is wrong function asks for data again
bool is_zero (float x); /// Function, that compares float and zero. TRUE: float == 0, FALSE: float != 0
void linear_solver (float b, float c, Solutions *p_solution); /// Function, that solves linear equation
void square_solver (float a, float b, float c, Solutions *p_solution); /// Function, that solves square equation
void solutions_output (Solutions *p_solution); /// Function for outputting data about solution of equation

///Test program functions
void unittest (void); /// Function, that opens data-file with test information, reads tests number and calls another functions in a cycle
bool input (FILE *InputFile, EquationTests *p_equtest); /// Function for inputting equation coefficients and solution data from data-file. Returns number of inputted variables
//void choose_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber, TestAnswers *p_answers); /// Function, that calls functions for solving and checking answers, also counts number of tests
//int linear_test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber); /// Function, that calls another functions to solve linear equation and check solutions. Returns 1 if solutions are equal and 0 if the are not
//int square_test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber); /// Function, that calls another functions to solve square equation and check solutions. Returns 1 if solutions are equal and 0 if the are not
int test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber);
bool check_answers (FILE *OutputFile, Solutions *p_mastersol, EquationTests *p_equtest,int testnumber); /// Function, that compares solutions from data-file and program solutions. TRUE: solutions are equal, FALSE solutions are not equal
//void exam (FILE *InputFile, FILE *OutputFile, int StartCheckRes, TestAnswers *p_answers); /// Function for outputting information about tests


#endif
