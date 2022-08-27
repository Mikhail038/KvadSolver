//Header File


#ifndef CORE_H
#define CORE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>


#define NumberOfCmdCommands 6

typedef struct CmdInputStruct
{
    int argc = 0;
    char** argv = NULL;
    int    i = 0;
    double a = 0,
           b = 0,
           c = 0;
    const char *inpF = NULL,
               *outF = NULL;
} CmdInputStruct;

enum CommandMode
{
    HELP    = 0,
    TEST    = 1,
    INPUT   = 2,
    RUN     = 3,
    CMDMODE = 4,
    MEOW    = 5
};

typedef struct Command
{
    char             sName;
    const char*      lName;
    enum CommandMode mode;
    void   (*func)  (CmdInputStruct*);
    const char*      description;
} Command;




/*!
    @brief Variable, that keeps data about command line arguments
*/
enum CmdArgs
{
    NoArgs       = 0,
    Interactive  = 1,
    Test         = 2,
    CmdInput     = 3,
    TooMuchArgs  = 4,
    CmdInput_few = 5,
    CustomFile   = 6,
    Help         = 7
};

/*!
    @brief Error codes
*/
enum ErrorCode
{
    NULL_POINTER    = 0,
    IS_NOT_FINITE   = 1,
    FILE_NOT_OPENED = 2,
    SPECIAL_ERROR   = 3
};

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
    double x1 = 0;
    double x2 = 0;
    enum Cases num = NoSolutions;
} Solutions;

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
            vMCA ((isfinite ((double)p_solution->num)), IS_NOT_FINITE);                  \
            vMCA ((isfinite (p_solution->x1)), IS_NOT_FINITE);                          \
            vMCA ((isfinite (p_solution->x2)), IS_NOT_FINITE);                          \
        } while (0)

#define assert_p_solution                                                              \
        do                                                                             \
        {                                                                              \
            MCA ((isfinite ((double)p_solution->num)), IS_NOT_FINITE);                  \
            MCA ((isfinite (p_solution->x1)), IS_NOT_FINITE);                          \
            MCA ((isfinite (p_solution->x2)), IS_NOT_FINITE);                          \
        } while (0)

void f_cmd_con (CmdInputStruct* data);

void f_cmd_run (CmdInputStruct* data);

void f_cmd_inp  (CmdInputStruct* data);

void f_cmd_help (CmdInputStruct* data);

void f_cmd_meow (CmdInputStruct* data);

void f_cmd_test (CmdInputStruct* data);

void find_sName (int c, char** v, int i, CmdInputStruct* data);

void find_lName (int c, char** v, int i, CmdInputStruct* data);

void parse      (int c, char** v, int i, CmdInputStruct* data);

/*!
    @brief Function, that solves equation, if coefficients were inputted by console

    @param[in] a   the a (a*x^2) coefficient
    @param[in] b   the b (b*x) coefficient
    @param[in] c   the c (c) coefficient
*/
void command_main (double a, double b, double c);

/*!
    @brief Function, that solves equation, if user inputs coefficients

    @param[in] a   the a (a*x^2) coefficient
    @param[in] b   the b (b*x) coefficient
    @param[in] c   the c (c) coefficient
*/
void inter_main (void);

/*!
    @brief Function, that clears useless information in console input
*/
void clear_input (void);

/*!
    @brief Function for inputting 3 double coefficients. If they are inputted badly, function asks for data again

    @param[in] p_a pointer to the a (a*x^2) coefficient
    @param[in] p_b pointer to the b (b*x) coefficient
    @param[in] p_c pointer to the c (c) coefficient
*/
void coefficients_input (const double* p_a, const double* p_b, const double* p_c);

/*!
    @brief Function, that compares double and zero. TRUE: double == 0, FALSE: double != 0

    @param[in] x variable, that u check

    @return false: double var is zero, true: double var is not zero
*/
bool is_zero (double x);

/*!
    @brief Function that cheks a-coefficient and then run another functions, which solve equation

    @param[in] a a (a*x^2) coefficient
    @param[in] b b (b*x) coefficient
    @param[in] c c (c) coefficient
    @param[out] p_solution pointer to structure, that keeps data about equation solution
*/
void equation_solver (const double a,const double b, const double c, Solutions* p_solution);

/*!
    @brief Function that solves linear equation

    @param[in] b b (b*x) coefficient
    @param[in] c c (c) coefficient
    @param[out] p_solution pointer to structure, that keeps data about equation solution
*/
void linear_solver (const double b, const double c, Solutions* p_solution);

/*!
    @brief Function that solves square equation

    @param[in] a a (a*x^2) coefficient
    @param[in] b b (b*x) coefficient
    @param[in] c c (c) coefficient
    @param[out] p_solution pointer to structure, that keeps data about equation solution
*/
void square_solver (const double a, const double b, const double c, Solutions* p_solution);

/*!
    @brief Function that outputs number of solutions and roots, if they exist

    @param[in] p_solution pointer to structure, that keeps data about equation solution
*/
void solutions_output (Solutions* p_solution);


#endif // CORE_H

