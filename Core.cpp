//Core File


#ifndef CORE_CPP
#define CORE_CPP

#include "Core.h"

Command Arr_Commands[NumberOfCmdCommands] =
{
    {'h', "--help"   , HELP,    &f_cmd_help, "-h""  --help     "
    "     This mode shows all available modes                                                      !\n"},
    {'t', "--test"   , TEST,    &f_cmd_test, "-t""  --test     "
    "     This mode runs program in test mode                                                      T\n"},
    {'i', "--input"  , INPUT,   &f_cmd_inp,  "-i""  --input    "
    "     This flag allow u to choose input and output files (needs -t first) (enter 2 file names) i\n"},
    {'r', "--run"    , RUN,     &f_cmd_run,  "-r""  --run      "
    "     This mode runs program in interactive mode                                               R\n"},
    {'c', "--console", CMDMODE, &f_cmd_con,  "-c""  --console  "
    "     This mode runs program in console mode (enter 3 numbers)                                 C\n"},
    {'m', "--meow"   , MEOW,    &f_cmd_meow, "-m""  --meow     "
    "     This mode just meows                                                                    <3\n"}
};

void f_cmd_inp  (CmdInputStruct* data)
{
    data->inpF = data->argv[++data->i];
    data->outF = data->argv[++data->i];
    f_cmd_test (data);
}

void f_cmd_help (CmdInputStruct* data)
{
    for (int i = 0; i < NumberOfCmdCommands - 1; i++)
    {
        printf ("%s\n", Arr_Commands[i].description);
    }
}

void f_cmd_con (CmdInputStruct* data)
{
    data->a = atof (data->argv[++data->i]);
    data->b = atof (data->argv[++data->i]);
    data->c = atof (data->argv[++data->i]);

    command_main (data->a, data->b, data->c);
}

void f_cmd_run (CmdInputStruct* data)
{
    inter_main ();
}

void f_cmd_meow (CmdInputStruct* data)
{
    printf ("purr...purrr....Meooooow :3");
}

void find_sName (int argc, char** argv, int i, CmdInputStruct* data)
{
    data->argc = argc;
    data->argv = argv;
    data->i    = i;

    for (int j = 0; j < NumberOfCmdCommands; j++)
    {
        if (Arr_Commands[j].sName == argv[i][1])
            Arr_Commands[j].func (data);
    }
}

void find_lName (int argc, char** argv, int i, CmdInputStruct* data)
{
    data->argc = argc;
    data->argv = argv;
    data->i    = i;

    for (int j = 0; j < NumberOfCmdCommands; j++)
    {
        /*char cut_v[sizeof(v[i]) - 2];

        for (int z = 0; z < (sizeof(v[i]) - 1); z++)
            cut_v[z] = v[i][z+2];*/

        if (strcmp (Arr_Commands[j].lName, argv[i]) == 0)
            Arr_Commands[j].func (data);
    }
}

void parse (int argc, char** argv, int i, CmdInputStruct* data)
{
    if (     (argv[i][0] == '-') && (argv[i][1] != '-'))
        find_sName (argc, argv, i, data);
    else if ((argv[i][0] == '-') && (argv[i][1] == '-'))
        find_lName (argc, argv, i, data);
}

void command_main (const double a, const double b, const double c)
{
    Solutions solution = {};
    Solutions* p_solution = &solution;

    equation_solver (a, b, c, p_solution);

    solutions_output (p_solution);
}

void inter_main (void)
{
    unsigned int running = 0;
    do
    {
        Solutions solution = {};
        Solutions* p_solution = &solution;

        double a = 0, b = 0, c = 0;


        coefficients_input (&a, &b, &c);

        equation_solver (a, b, c, p_solution);

        solutions_output (p_solution);

        printf ("\n" "Again? 1 - YES 0 - NO : ");
        scanf ("%u", &running);

    } while (running);
}

void equation_solver (const double a,const double b, const double c, Solutions* p_solution)
{
    if (is_zero(a))
        linear_solver (b, c, p_solution);
    else
        square_solver (a, b, c, p_solution);
}

void clear_input (void)
{
    while (getchar() != '\n');
}

void coefficients_input (const double* p_a, const double* p_b, const double* p_c)
{
    vMCA((p_a != NULL), NULL_POINTER);
    vMCA((p_b != NULL), NULL_POINTER);
    vMCA((p_c != NULL), NULL_POINTER);

    printf ("Enter three coefficients of equation: ");

    while ((scanf ("%lg %lg %lg", p_a, p_b, p_c)) != 3)
    {
        clear_input ();
        printf("Please enter three numbers: ");
    }
}

bool is_zero (const double x)
{
    MCA ((isfinite (x)), IS_NOT_FINITE);

    const double approximate_zero = (double) 1e-5;

    return (fabs (x) <= approximate_zero);
}

void linear_solver (const double b,const double c, Solutions* p_solution)
{
    vMCA((p_solution != NULL), NULL_POINTER);
    vMCA((isfinite (b)), IS_NOT_FINITE);
    vMCA((isfinite (c)), IS_NOT_FINITE);
    v_assert_p_solution;

    p_solution->num = NoSolutions;
    p_solution->x1 = 0;
    p_solution->x2 = 0;

    if (is_zero(b) && is_zero(c))
        p_solution->num = InfiniteSolutions;
    else if (is_zero (b))
        p_solution->num = NoSolutions;
    else if (is_zero (c))
    {
        p_solution->num = OneSolution;
        p_solution->x1 = 0;
    }
    else
    {
        p_solution->num = OneSolution;
        p_solution->x1 = -c / b;
    }
}

void square_solver (const double a, const double b, const double c, Solutions* p_solution)
{
    vMCA((p_solution != NULL), NULL_POINTER);
    vMCA((isfinite (a)), IS_NOT_FINITE);
    vMCA((isfinite (b)), IS_NOT_FINITE);
    vMCA((isfinite (c)), IS_NOT_FINITE);
    v_assert_p_solution;

    p_solution->num = NoSolutions;
    p_solution->x1 = 0;
    p_solution->x2 = 0;

    const double discriminant = b * b - 4 * a * c;

    if (discriminant < 0)
        p_solution->num = NoSolutions;
    else if (is_zero (b) && is_zero (c))
    {
        p_solution->num = OneSolution;
        p_solution->x1 = 0;
    }
    else if (is_zero (discriminant))
    {
        const double doubled_a = 2 * a;

        p_solution->num = OneSolution;
        p_solution->x1 = -b / doubled_a;
    }
    else
    {
        const double doubled_a = 2 * a;
        const double sqr_discr = sqrt (discriminant);

        p_solution->num = TwoSolutions;
        p_solution->x1 = (-b - sqr_discr) / doubled_a;
        p_solution->x2 = (-b + sqr_discr) / doubled_a;
    }
}

void solutions_output (Solutions* p_solution)
{
    vMCA((p_solution != NULL), NULL_POINTER);
    v_assert_p_solution;

    switch (p_solution->num)
    {
        case OneSolution:
            printf ("There is one solution: %lg", p_solution->x1);
            break;
        case TwoSolutions:
            printf ("There are two solutions: %lg and %lg", p_solution->x1, p_solution->x2);
            break;
        case NoSolutions:
            printf ("There are no solutions");
            break;
        case InfiniteSolutions:
            printf ("There are infinite solutions");
            break;
        default:
            printf ("UNKNOWN_ERROR !\n");
            break;
    }
}

#endif // CORE_CPP

