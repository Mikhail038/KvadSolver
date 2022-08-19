//Test File

#include "Core_EquationSolver.h"
#include "Core_EquationSolver.cpp"

#ifndef TEST_EQUATION_SOLVER_CPP
#define TEST_EQUATION_SOLVER_CPP


void unittest (void);
void input (FILE *InputFile, EquationTests *p_equtest) ;
void exam (FILE *InputFile, FILE *OutputFile, int StartCheckRes, TestAnswers *p_answers);
void choose_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber, TestAnswers *p_answers);
int linear_test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber);
int square_test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber);
bool check_answers (FILE *OutputFile, Solutions *p_mastersol, EquationTests *p_equtest,int testnumber);

void unittest()
{
    FILE *OutputFile = NULL, *InputFile = NULL;

    enum TestCases StratCheckRes = NoFile;

    TestAnswers answers = {}; TestAnswers *p_answers = &answers;

    InputFile = fopen ("COEFS.txt", "r");

    int TestsNumber = -1;

    fscanf (InputFile, "%d", &TestsNumber);

    if (TestsNumber == -1)
    {
        StratCheckRes = NoFile;

        exam (InputFile, OutputFile, StratCheckRes, p_answers);
    }
    else if (TestsNumber == 0)
    {
        StratCheckRes = NoCoefs;

        exam (InputFile, OutputFile, StratCheckRes, p_answers);
    }
    else
        {
            StratCheckRes = Normal;

            OutputFile = fopen ("RESULTS.txt", "w");

            EquationTests equtest = {}; EquationTests *p_equtest = &equtest;

            for (int testnumber=0; testnumber<TestsNumber; testnumber++)
            {
                input (InputFile, p_equtest);

                choose_master (OutputFile, p_equtest, testnumber, p_answers);
            }

            exam (InputFile, OutputFile, StratCheckRes, p_answers);
        }
}

bool check_answers (FILE *OutputFile, Solutions *p_mastersol, EquationTests *p_equtest,int testnumber)
{
    fprintf (OutputFile, "Test ¹%d  RIGHT ANSWERS: %d %f %f PROGRAMM ANSWERS: %d %f %f ", testnumber + 1,
    p_mastersol->num, p_mastersol->x1, p_mastersol->x2, p_equtest->tnum, p_equtest->tx1, p_equtest->tx2);

    if ( ((p_mastersol->x1 == p_equtest->tx1) && (p_mastersol->x2 == p_equtest->tx2) && (p_mastersol->num == p_equtest->tnum)) ||
    (((p_mastersol->x1 == p_equtest->tx2) && (p_mastersol->x2 == p_equtest->tx1) && (p_mastersol->num == p_equtest->tnum))) )
    {
        fprintf (OutputFile, "PASSED\n");
        return true;
    }
    else
    {
        fprintf (OutputFile, "FAILED  !!!\n");
        return false;
    }
}

void input (FILE *InputFile, EquationTests *p_equtest)
{
    fscanf (InputFile, "%f %f %f %d %f %f", &(p_equtest->ta), &(p_equtest->tb),
    &(p_equtest->tc), &(p_equtest->tnum), &(p_equtest->tx1), &(p_equtest->tx2));
}

void choose_master (FILE *OutputFile, EquationTests *p_equtest,int testnumber, TestAnswers *p_answers)
{
    if (is_zero(p_equtest->ta))
    {
        p_answers->ok += linear_test_master (OutputFile, p_equtest, testnumber);
        p_answers->all++;
    }
    else
    {
        p_answers->ok += square_test_master (OutputFile, p_equtest, testnumber);
        p_answers->all++;
    }
}

int linear_test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber)
{
    Solutions mastersol = {}; Solutions *p_mastersol = &mastersol;
    linear_solver (p_equtest->tb, p_equtest->tc, p_mastersol);
    if (check_answers (OutputFile, p_mastersol, p_equtest, testnumber))
        return 1;
    else
        return 0;
}

int square_test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber)
{
    Solutions mastersol = {}; Solutions *p_mastersol = &mastersol;
    square_solver (p_equtest->ta, p_equtest->tb, p_equtest->tc, p_mastersol);
    if (check_answers (OutputFile, p_mastersol, p_equtest, testnumber))
        return 1;
    else
        return 0;
}

void exam (FILE *InputFile, FILE *OutputFile, int StartCheckRes, TestAnswers *p_answers)
{
    fclose (InputFile);
    fclose (OutputFile);
    switch (StartCheckRes)
    {
    case NoFile:
        printf ("TEST FAILED: NO FILE FOUND ""COEFS.txt"" ");
        break;
    case NoCoefs:
        printf ("TEST FAILED: NO COEFFICIENTS FOUND IN ""COEFS.txt"" ");
        break;
    case Normal:
        printf ("TESTS RESULT: %d OF %d RIGHT ANSWERS", p_answers->ok, p_answers->all);
        break;
    }
}

#endif // TEST_EQUATION_SOLVER_CPP

