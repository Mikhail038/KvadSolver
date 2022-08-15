#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*void lin (float b,float c);
void kvd (float a,float b,float c) ; */

void lin (float b,float c)
{
    if (b == 0) printf ("The are NO solutions");
    else if (c == 0) printf ("The solution is: 0");
    else printf ("The solution is: %f", -c/b );
}

void kvd (float a,float b,float c)
{
    int d = b*b - 4*a*c;

    if (d < 0) printf ("The are NO solutions (for real numbers)");
    else if (d == 0) printf ("The solution is: %f", -b/(2*a) );
    else printf("The solutions are: %f and %f", (-b - sqrt(d))/(2*a), (-b + sqrt(d))/(2*a) );
}

int main (void)
{
    float a, b, c;

    printf ("Enter the coefficients of equation: ");
    scanf ("%f %f %f", &a, &b, &c);

    if (a == 0) lin (b,c);
    else kvd (a,b,c);

    return 0;
}

/*void lin (float b,float c)
{
    if (b == 0) printf ("The are NO solutions");
    else if (c == 0) printf ("The solution is: 0");
    else printf ("The solution is: %f", -c/b );
}

void kvd (float a,float b,float c)
{
    int d = b*b - 4*a*c;
    if (d < 0) printf ("The are NO solutions (for real numbers)");
    else if (d == 0) printf ("The solution is: %f", -b/(2*a) );
    else printf("The solutions are: %f and %f", (-b - sqrt(d))/(2*a), (-b + sqrt(d))/(2*a) );
}*/

