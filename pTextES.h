//Test Header File


#ifndef TEST_EQUATION_SOLVER_H
#define TEST_EQUATION_SOLVER_H

#include "pCoreES.h"

#define v_assert_p_equtest                                                              \
        do                                                                              \
        {                                                                               \
            vMCA((isfinite (p_equtest->ta)), "P_EQUTEST_TA_IS_NOT_FINITE");            \
            vMCA((isfinite (p_equtest->tb)), "P_EQUTEST_TB_IS_NOT_FINITE");            \
            vMCA((isfinite (p_equtest->tc)), "P_EQUTEST_TC_IS_NOT_FINITE");            \
            vMCA((isfinite ((float)p_equtest->tnum)), "P_EQUTEST_NUM_IS_NOT_FINITE");  \
            vMCA((isfinite (p_equtest->tx1)), "P_EQUTEST_TX1_IS_NOT_FINITE");          \
            vMCA((isfinite (p_equtest->tx2)), "P_EQUTEST_TX2_IS_NOT_FINITE");          \
        } while (0)

#define assert_p_equtest                                                                \
        do                                                                              \
        {                                                                               \
            MCA((isfinite (p_equtest->ta)), "P_EQUTEST_TA_IS_NOT_FINITE");             \
            MCA((isfinite (p_equtest->tb)), "P_EQUTEST_TB_IS_NOT_FINITE");             \
            MCA((isfinite (p_equtest->tc)), "P_EQUTEST_TC_IS_NOT_FINITE");             \
            MCA((isfinite ((float)p_equtest->tnum)), "P_EQUTEST_NUM_IS_NOT_FINITE");   \
            MCA((isfinite (p_equtest->tx1)), "P_EQUTEST_TX1_IS_NOT_FINITE");           \
            MCA((isfinite (p_equtest->tx2)), "P_EQUTEST_TX2_IS_NOT_FINITE");           \
        } while (0)


/*!
    @brief Structure, that keeps data about number of right answers and number of tests
*/
typedef struct TestAnswers
{
    int ok = 0;
    int all = 0;
} TestAnswers;

/*!
    @brief Structure, that keeps data about equation in testing mode
*/
typedef struct EquationTests
{
    float ta = 0, tb = 0, tc = 0;
    float tx1 = 0, tx2 = 0;
    enum Cases tnum = NoSolutions;
} EquationTests;




/*!
    @brief Function, that compares 2 floats

    @param[in] a first float var
    @param[in] b second float var

    @return false - floats are not equal, true - floats are equal
*/
bool compare_floats (float a, float b);

/*!
    @brief Function, that compares 2 structures: test answers and program answers

    @param[in] p_equtest pointer to test answers
    @param[in] p_mastersol pointer to program answers

    @return false - answers are not equal, true - answers are equal
*/
bool check_answers (EquationTests* p_equtest, Solutions* p_mastersol);


/*!
    @brief Function, that goes through file until it founds '\n', then it stops

    @param[in] InputFile Opened file
*/
void sclear (FILE* InputFile);

/*!
    @brief Unit test driver

    @note program opens COEFS.txt, takes from it test data, puts results of tests in RESULTS.txt

*/
void unit_test (void);

/*!
    @brief Function, that inputs information from test-file

    @param[in] InputFile test-file
    @param[out] p_equtest pointer to structure, that keeps test-data (a,b,c,num,x1,x2)

    @return false - data in text file is incorrect, true - data is correct
*/
bool input (FILE* InputFile, EquationTests* p_equtest);

/*!
    @brief Function, that checks function and test answers

    @param[out] OutputFile file for outputting test results
    @param[out] p_equtest pointer to structure, that keeps test-data (a,b,c,num,x1,x2)
    @param[out] TestCounter  variable that keeps information about number of test

    @return 1 - test is passed, 0 test is failed
*/
int test_master (FILE* OutputFile, EquationTests* p_equtest, int TestCounter);

//void choose_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber, TestAnswers *p_answers); /// Function, that calls functions for solving and checking answers, also counts number of tests
//int linear_test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber); /// Function, that calls another functions to solve linear equation and check solutions. Returns 1 if solutions are equal and 0 if the are not
//int square_test_master (FILE *OutputFile, EquationTests *p_equtest, int testnumber); /// Function, that calls another functions to solve square equation and check solutions. Returns 1 if solutions are equal and 0 if the are not
//bool check_answers (FILE *OutputFile, Solutions *p_mastersol, EquationTests *p_equtest,int testnumber); /// Function, that compares solutions from data-file and program solutions. TRUE: solutions are equal, FALSE solutions are not equal
//void exam (FILE *InputFile, FILE *OutputFile, int StartCheckRes, TestAnswers *p_answers); /// Function for outputting information about tests

#endif

