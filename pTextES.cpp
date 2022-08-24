//Test File


#ifndef P_TEXT_E_S_CPP
#define P_TEXT_E_S_CPP

#include "pCoreES.h"
#include "pTextES.h"



bool check_answers (EquationTests* p_equtest, Solutions* p_mastersol)
{
    return (((compare_floats (p_mastersol->x1,p_equtest->tx1))
        && (compare_floats (p_mastersol->x2,p_equtest->tx2))
        && (compare_floats ((float) p_mastersol->num,(float) p_equtest->tnum))) ||
           ((compare_floats (p_mastersol->x1,p_equtest->tx2))
        && (compare_floats (p_mastersol->x2,p_equtest->tx1))
        && (compare_floats ((float) p_mastersol->num,(float) p_equtest->tnum))));
}


bool compare_floats (const float a, const float b)
{
    const float approximate_zero = float(1e-5);
    if (fabs(a - b) <= approximate_zero)
        return true;
    else return false;
}


void sclear (FILE* InputFile)
{
    vMCA((InputFile != NULL), NULL_POINTER);

    char junk[100] = {};
    fgets (junk, 100, InputFile);
}

void unit_test (void)
{
    FILE *OutputFile = NULL,
         *InputFile  = NULL;

    TestAnswers answers = {};
    TestAnswers* p_answers = &answers;

    InputFile = fopen ("COEFS.txt", "r");
    vMCA((InputFile != NULL), FILE_NOT_OPENED );

    int TestsNumber = -1;
    fscanf (InputFile, "%d", &TestsNumber);
    vMCA((TestsNumber >= 0), SPECIAL_ERROR);

    sclear (InputFile);

    OutputFile = fopen ("RESULTS.txt", "w");
    vMCA ((OutputFile != NULL), FILE_NOT_OPENED);

    EquationTests equtest = {};
    EquationTests* p_equtest = &equtest;

    for (int TestCounter = 0; TestCounter < TestsNumber; TestCounter++)
    {
        if (input (InputFile, p_equtest))
        {
            p_answers->ok += test_master (OutputFile, p_equtest, TestCounter);
        }
        else
        {
            fprintf (OutputFile, "Test #%d  WRONG DATA!!!\n", TestCounter + 1);

            sclear (InputFile);
        }
        p_answers->all++;
    }
    fclose (InputFile);
    fclose (OutputFile);

    printf ("TESTS RESULT: %d OF %d RIGHT ANSWERS", p_answers->ok, p_answers->all);
}

bool input (FILE* InputFile, EquationTests* p_equtest)
{
    MCA((InputFile != NULL), NULL_POINTER);
    MCA((p_equtest != NULL), NULL_POINTER);
    assert_p_equtest;

    if (fscanf (InputFile, "%f %f %f %d %f %f", &(p_equtest->ta),
      &(p_equtest->tb),&(p_equtest->tc), (int*)&(p_equtest->tnum),
      &(p_equtest->tx1), &(p_equtest->tx2)) == 6)
    {
        sclear (InputFile);
        return true;
    }
    return false;
}

int test_master (FILE* OutputFile, EquationTests* p_equtest, const int TestCounter)
{
    MCA((OutputFile != NULL), NULL_POINTER);
    MCA((p_equtest != NULL), NULL_POINTER);
    MCA((isfinite ((float) TestCounter)), IS_NOT_FINITE);
    assert_p_equtest;


    Solutions mastersol = {};
    Solutions *p_mastersol = &mastersol;

    if (is_zero (p_equtest->ta))
        linear_solver (p_equtest->tb, p_equtest->tc, p_mastersol);
    else
        square_solver (p_equtest->ta, p_equtest->tb, p_equtest->tc, p_mastersol);


    fprintf (OutputFile, "Test #%d  RIGHT ANSWERS: %d %f %f PROGRAMM ANSWERS: %d %f %f ",
        TestCounter + 1, p_mastersol->num, p_mastersol->x1, p_mastersol->x2,
        p_equtest->tnum, p_equtest->tx1, p_equtest->tx2);

    if (check_answers (p_equtest, p_mastersol))
    {
        fprintf (OutputFile, "PASSED\n");
        return 1;
    }
    else
    {
        fprintf (OutputFile, "FAILED  !!!\n");
        return 0;
    }
}

#endif // P_TEXT_ES_CPP


