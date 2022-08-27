//Test Header File


#ifndef TEST_H
#define TEST_H

#include "Core.h"

#define v_assert_p_equtest                                                              \
        do                                                                              \
        {                                                                               \
            vMCA((isfinite (p_equtest->ta)), "P_EQUTEST_TA_IS_NOT_FINITE");            \
            vMCA((isfinite (p_equtest->tb)), "P_EQUTEST_TB_IS_NOT_FINITE");            \
            vMCA((isfinite (p_equtest->tc)), "P_EQUTEST_TC_IS_NOT_FINITE");            \
            vMCA((isfinite ((double)p_equtest->tnum)), "P_EQUTEST_NUM_IS_NOT_FINITE");  \
            vMCA((isfinite (p_equtest->tx1)), "P_EQUTEST_TX1_IS_NOT_FINITE");          \
            vMCA((isfinite (p_equtest->tx2)), "P_EQUTEST_TX2_IS_NOT_FINITE");          \
        } while (0)

#define assert_p_equtest                                                                \
        do                                                                              \
        {                                                                               \
            MCA((isfinite (p_equtest->ta)), "P_EQUTEST_TA_IS_NOT_FINITE");             \
            MCA((isfinite (p_equtest->tb)), "P_EQUTEST_TB_IS_NOT_FINITE");             \
            MCA((isfinite (p_equtest->tc)), "P_EQUTEST_TC_IS_NOT_FINITE");             \
            MCA((isfinite ((double)p_equtest->tnum)), "P_EQUTEST_NUM_IS_NOT_FINITE");   \
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
    double ta = 0, tb = 0, tc = 0;
    double tx1 = 0, tx2 = 0;
    enum Cases tnum = NoSolutions;
} EquationTests;




/*!
    @brief Function, that compares 2 doubles

    @param[in] a first double var
    @param[in] b second double var

    @return false - doubles are not equal, true - doubles are equal
*/
bool compare_floats (const double a, const double b);

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
void unit_test (const char* TstFileName, const char* ResFileName);

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



#endif // TEST_H

