//Test File


#ifndef TEST_CPP
#define TEST_CPP

#include "Core.h"
#include "Test.h"


void f_cmd_test (CmdInputStruct* data)
{
    if ((data->inpF == NULL) && (data->outF == NULL))
    {
        if (data->argc == (data->i + 4))
            parse (data->argc, data->argv, ++data->i, data);
        else
        {
            data->inpF =   "COEFS.txt";
            data->outF = "RESULTS.txt";
        }
        unit_test (data->inpF, data->outF);
        return;
    }
    //printf ("%s %s\n", data->inpF, data->outF);
}

bool check_answers (EquationTests* p_equtest, Solutions* p_mastersol)
{
    return (((compare_floats (p_mastersol->x1,p_equtest->tx1))
        && (compare_floats   (p_mastersol->x2,p_equtest->tx2))
        && (compare_floats ((double) p_mastersol->num,(double) p_equtest->tnum))) ||
           ((compare_floats  (p_mastersol->x1,p_equtest->tx2))
        && (compare_floats   (p_mastersol->x2,p_equtest->tx1))
        && (compare_floats ((double) p_mastersol->num,(double) p_equtest->tnum))));
}

bool compare_floats (const double a, const double b)
{
    const double approximate_zero = double(1e-5);
    return (fabs(a - b) <= approximate_zero);
}

void sclear (FILE* InputFile)
{
    vMCA((InputFile != NULL), NULL_POINTER);

    //char junk[1] = {};
    while (fgetc(InputFile) != '\n') {};
    //fgets (junk, 100, InputFile);
}

void unit_test (const char* TstFileName, const char* ResFileName)
{
    FILE *OutputFile = NULL,
         *InputFile  = NULL;

    TestAnswers answers = {};
    TestAnswers* p_answers = &answers;

    InputFile = fopen (TstFileName, "r");
    vMCA((InputFile != NULL), FILE_NOT_OPENED );

    int TestsNumber = -1;
    fscanf (InputFile, "%d", &TestsNumber);
    vMCA((TestsNumber >= 0), SPECIAL_ERROR);

    sclear (InputFile);

    OutputFile = fopen (ResFileName, "w");
    vMCA ((OutputFile != NULL), FILE_NOT_OPENED);

    EquationTests equtest = {};
    EquationTests* p_equtest = &equtest;

    for (int TestCounter = 0; TestCounter < TestsNumber; TestCounter++)
    {
        printf ("!\n");
        if (input (InputFile, p_equtest))
        {
            printf ("1\n");
            p_answers->ok += test_master (OutputFile, p_equtest, TestCounter);
        }
        else
        {
            printf ("2\n");
            fprintf (OutputFile, "Test #%d  WRONG DATA!!!\n", TestCounter + 1);

            sclear (InputFile);
        }
        p_answers->all++;
        printf ("%d!!%d\n", TestCounter, TestsNumber);
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

    if (fscanf (InputFile, "%lg %lg %lg %i %lg %lg", &(p_equtest->ta),
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
    MCA((isfinite ((double) TestCounter)), IS_NOT_FINITE);
    assert_p_equtest;


    Solutions mastersol = {};
    Solutions *p_mastersol = &mastersol;

    if (is_zero (p_equtest->ta))
        linear_solver (p_equtest->tb, p_equtest->tc, p_mastersol);
    else
        square_solver (p_equtest->ta, p_equtest->tb, p_equtest->tc, p_mastersol);


    fprintf (OutputFile, "Test #%d  RIGHT ANSWERS: %d %g %g PROGRAMM ANSWERS: %d %g %g",
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

#endif // TEST_CPP


