//Test File

#include "Core_EquationSolver.h"
#include "Core_EquationSolver.cpp"

enum TestCases StratCheckRes;

EquationTests equtest = {}; EquationTests *p_equtest = &equtest;
TestAnswers answers = {}; TestAnswers *p_answers = &answers;
Solutions mastersol = {}; Solutions *p_mastersol = &mastersol;

FILE *OutputFile = NULL;
FILE *InputFile = NULL;

void unittest (void);
void start_check (FILE *InputFile);
void testing (int TestsNumber, FILE *InputFile);
void input (FILE *InputFile, EquationTests *p_equtest) ;
void exam (int StartCheckRes, TestAnswers *p_answers);
void solve_check (EquationTests *p_equtest);
int linear_test_master (EquationTests *p_equtest);
int square_test_master (EquationTests *p_equtest);
bool same_answers (Solutions *p_mastersol, EquationTests *p_equtest);

void unittest()
{
    printf("unittest\n");
    InputFile = fopen ("COEFS.txt", "r");
    start_check (InputFile);
}

bool same_answers (Solutions *p_mastersol, EquationTests *p_equtest)
{
    printf("same_answers\n");
    printf("# %d %f %f %d %f %f\n", p_mastersol->num, p_mastersol->x1, p_mastersol->x2, p_equtest->tnum, p_equtest->tx1, p_equtest->tx2);

    if ( ((p_mastersol->x1 == p_equtest->tx1) && (p_mastersol->x2 == p_equtest->tx2) && (p_mastersol->num == p_equtest->tnum)) ||
    (((p_mastersol->x1 == p_equtest->tx2) && (p_mastersol->x2 == p_equtest->tx1) && (p_mastersol->num == p_equtest->tnum))) )
        return true;
    else return false;
}

void start_check (FILE *InputFile)
{
    printf("start_check\n");
    int TestsNumber = -1;

    fscanf (InputFile, "%d", &TestsNumber);

    if (TestsNumber == 0)
        exam (NoCoefs, p_answers);
    else if (TestsNumber == -1)
        exam (NoFile, p_answers);
    else
        testing (TestsNumber, InputFile);
}

void testing (int TestsNumber, FILE *InputFile)
{
    printf("testing\n");
    OutputFile = fopen ("RESULTS.txt", "w");

    for (int i=0; i<TestsNumber; i++)
    {
        input (InputFile, p_equtest);
        solve_check (p_equtest);
    }
    exam(Normal, p_answers);
}

void input (FILE *InputFile, EquationTests *p_equtest)
{
    printf("input\n");

    fscanf (InputFile, "%f %f %f %d %f %f", &(p_equtest->ta), &(p_equtest->tb),
    &(p_equtest->tc), &(p_equtest->tnum), &(p_equtest->tx1), &(p_equtest->tx2));

    printf ("%f %f %f %d %f %f \n", p_equtest->ta, p_equtest->tb,
    p_equtest->tc, p_equtest->tnum, p_equtest->tx1, p_equtest->tx2 );
}

void solve_check (EquationTests *p_equtest)
{
    printf("solve_check\n");
    if (is_zero(p_equtest->ta))
    {
        p_answers->ok += linear_test_master (p_equtest);
        p_answers->all++;
        printf("! %d\n", p_answers->ok);
    }
    else
    {
        p_answers->ok += square_test_master (p_equtest);
        p_answers->all++;
        printf("!! %d\n", p_answers->ok);
    }
}

int linear_test_master (EquationTests *p_equtest)
{
    printf("ltm\n");

    linear_solver (p_equtest->tb, p_equtest->tc, p_mastersol);
    if (same_answers (p_mastersol, p_equtest)) return 1;
    else return 0;
}

int square_test_master (EquationTests *p_equtest)
{
    printf("stm\n");

    square_solver (p_equtest->ta, p_equtest->tb, p_equtest->tc, p_mastersol);
    if (same_answers (p_mastersol, p_equtest)) return 1;
    else return 0;
}

void exam (int StartCheckRes, TestAnswers *p_answers)
{
    printf ("exam\n");
    fclose (InputFile); fclose (OutputFile);
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

