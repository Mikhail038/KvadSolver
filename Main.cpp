
#include "Core.h"
#include "Test.h"


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
        inter_main ();
    }

    return 0;
}












