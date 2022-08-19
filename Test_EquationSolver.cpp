//Test File


#ifndef TEST_EQUATION_SOLVER_CPP
#define TEST_EQUATION_SOLVER_CPP

#include "Core_EquationSolver.h"
#include "Core_EquationSolver.cpp"


void unittest()
{
    FILE *OutputFile = NULL,
    *InputFile = NULL;

    TestAnswers answers = {};
    TestAnswers *p_answers = &answers;

    InputFile = fopen ("COEFS.txt", "r");
    assert (InputFile != NULL);

    int TestsNumber = -1;
    fscanf (InputFile, "%d", &TestsNumber);
    assert (TestsNumber >= 0);

    char junk1[100] = {};
    fgets (junk1, 100, InputFile);

    OutputFile = fopen ("RESULTS.txt", "w");
    assert (OutputFile != NULL);

    EquationTests equtest = {};
    EquationTests *p_equtest = &equtest;

    for (int testnumber = 0; testnumber < TestsNumber; testnumber++)
    {
        if (input (InputFile, p_equtest))
        {
            p_answers->ok += test_master (OutputFile, p_equtest, testnumber);
        }
        else
        {
            fprintf (OutputFile, "Test #%d  WRONG DATA!!!\n", testnumber + 1);

            char junk2[100] = {};
            fgets (junk2, 100, InputFile);
        }
        p_answers->all++;
    }
    fclose (InputFile);
    fclose (OutputFile);

    printf ("TESTS RESULT: %d OF %d RIGHT ANSWERS", p_answers->ok, p_answers->all);
}

bool check_answers (FILE *OutputFile, Solutions *p_mastersol, EquationTests *p_equtest,int testnumber)
{
    fprintf (OutputFile, "Test #%d  RIGHT ANSWERS: %d %f %f PROGRAMM ANSWERS: %d %f %f ", testnumber + 1,
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

bool input (FILE *InputFile, EquationTests *p_equtest)
{
    if (fscanf (InputFile, "%f %f %f %d %f %f", &(p_equtest->ta), &(p_equtest->tb),
    &(p_equtest->tc), &(p_equtest->tnum), &(p_equtest->tx1), &(p_equtest->tx2)) == 6)
    {
        char junk3[100] = {};
        fgets (junk3, 100, InputFile);
        return true;
    }
    return false;
}

int test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber)
{
    Solutions mastersol = {};
    Solutions *p_mastersol = &mastersol;

    if (is_zero(p_equtest->ta))
        {
            linear_solver (p_equtest->tb, p_equtest->tc, p_mastersol);
        }
        else
            square_solver (p_equtest->ta, p_equtest->tb, p_equtest->tc, p_mastersol);

    if (check_answers (OutputFile, p_mastersol, p_equtest, testnumber))
        return 1;
    else
        return 0;
}

#endif // TEST_EQUATION_SOLVER_CPP
