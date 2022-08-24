//Header File


#ifndef P_CORE_E_S_H
#define P_CORE_E_S_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
                    /*    #define another_smth {
                                                if (...)
                                                }
                       #define SMTH do {
                                              if (...)
                                    } while (0)     */

enum ErrorCode
{
    NULL_POINTER    = 0,
    IS_NOT_FINITE   = 1,
    FILE_NOT_OPENED = 2,
    SPECIAL_ERROR   = 3
};

#define print_err(ErrorCode)                                                           \
        do                                                                             \
        {                                                                              \
            const char* error_name = nullptr;                                          \
            switch ((int)ErrorCode)                                                    \
            {                                                                          \
                case 0:                                                                \
                    error_name = "NULL_POINTER";                                       \
                    break;                                                             \
                case 1:                                                                \
                    error_name = "IS_NOT_FINITE";                                      \
                    break;                                                             \
                case 2:                                                                \
                    error_name = "FILE_NOT_OPENED";                                    \
                    break;                                                             \
                case 3:                                                                \
                    error_name = "SPECIAL_ERROR";                                      \
                    break;                                                             \
                default:                                                               \
                    error_name = "UNDEFINED_ERROR";                                    \
                    break;                                                             \
            }                                                                          \
            printf("\n" "ERROR_%s___LINE_%d_FILE_%s\n_____IN_FUNTION___%s\n", error_name, __LINE__, __FILE__, __PRETTY_FUNCTION__);  \
        } while (0)

#define vMCA(condition, ErrorCode)                                                     \
        do                                                                             \
        {                                                                              \
            if (!(condition))                                                              \
            {                                                                              \
                print_err (ErrorCode);                                                     \
                return;                                                                    \
            }                                                                              \
        } while (0)


#define MCA(condition, ErrorCode)                                                      \
        do                                                                             \
        {                                                                              \
            if (!(condition))                                                              \
            {                                                                              \
                print_err ((ErrorCode));                                                   \
                return 0;                                                                  \
            }                                                                              \
        } while (0)

#define v_assert_p_solution                                                             \
        do                                                                              \
        {                                                                               \
            vMCA ((isfinite ((float)p_solution->num)), IS_NOT_FINITE);                  \
            vMCA ((isfinite (p_solution->x1)), IS_NOT_FINITE);                          \
            vMCA ((isfinite (p_solution->x2)), IS_NOT_FINITE);                          \
        } while (0)

#define assert_p_solution                                                              \
        do                                                                             \
        {                                                                              \
            MCA ((isfinite ((float)p_solution->num)), IS_NOT_FINITE);                  \
            MCA ((isfinite (p_solution->x1)), IS_NOT_FINITE);                          \
            MCA ((isfinite (p_solution->x2)), IS_NOT_FINITE);                          \
        } while (0)



/*!
    @brief Variable, that keeps data about number of roots and their existing
*/
enum Cases
{
    InfiniteSolutions = -1,
    NoSolutions       =  0,
    OneSolution       =  1,
    TwoSolutions      =  2
};

/*!
    @brief Structure, that keeps data about equation in main mode
*/
typedef struct Solutions
{
    float x1 = 0;
    float x2 = 0;
    enum Cases num = NoSolutions;
} Solutions;

/*!
    @brief Function, that clears useless information in console input
*/
void clear_input (void);


/*!
    @brief Function for inputting 3 float coefficients. If they are inputted badly, function asks for data again

    @param[in] p_a pointer to the a (a*x^2) coefficient
    @param[in] p_b pointer to the b (b*x) coefficient
    @param[in] p_c pointer to the c (c) coefficient
*/
void coefficients_input (float* p_a, float* p_b, float* p_c);

/*!
    @brief Function, that compares float and zero. TRUE: float == 0, FALSE: float != 0

    @param[in] x variable, that u check

    @return false: float var is zero, true: float var is not zero
*/
bool is_zero (float x);

/*!
    @brief Function that cheks a-coefficient and then run another functions, which solve equation

    @param[in] a a (a*x^2) coefficient
    @param[in] b b (b*x) coefficient
    @param[in] c c (c) coefficient
    @param[out] p_solution pointer to structure, that keeps data about equation solution
*/
void equation_solver (const float a,const float b, const float c, Solutions* p_solution);

/*!
    @brief Function that solves linear equation

    @param[in] b b (b*x) coefficient
    @param[in] c c (c) coefficient
    @param[out] p_solution pointer to structure, that keeps data about equation solution
*/
void linear_solver (float b, float c, Solutions* p_solution);

/*!
    @brief Function that solves square equation

    @param[in] a a (a*x^2) coefficient
    @param[in] b b (b*x) coefficient
    @param[in] c c (c) coefficient
    @param[out] p_solution pointer to structure, that keeps data about equation solution
*/
void square_solver (float a, float b, float c, Solutions* p_solution);

/*!
    @brief Function that outputs number of solutions and roots, if they exist

    @param[in] p_solution pointer to structure, that keeps data about equation solution
*/
void solutions_output (Solutions* p_solution);



#endif

