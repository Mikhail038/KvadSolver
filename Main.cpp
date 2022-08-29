
#include "Core.h"
#include "Test.h"

/*
int mmain ()
{
    //sin(x) 0.1 � 0 �� 3
    //cos(x) 0.1 � 0 �� 3
    //tan(x) 0.1 � 0 �� 3
    //ctg(x) 0.1 � 0 �� 3
    //������� �� �����

    double x_min = 0, x_max = 3.2;
    double step = 0.1;

    f_table (x_min, x_max, step, &sin, "sin");
    f_table (x_min, x_max, step, &cos, "cos");
    f_table (x_min, x_max, step, &tan, "tan");
    f_table (x_min, x_max, step, &ctg, "ctg");
}*/



int main (int argc, char** argv)
{

    CmdInputStruct data;

    if (argc >= 2)
    {
        parse (argc, argv, 1, &data);
    }
    else
    {
        printf ("Chel ty ne sharish" "\n" "Please run program via console\n");
        //inter_main ();
        unit_test ("COEFS.txt", "RESULTS.txt");
    }

    return 0;
}












