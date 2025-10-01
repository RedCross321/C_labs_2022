/*

e^sin(x), 0 ≤ x ≤ 1/4
e^x - 1/sqrt(x), 1/4 < x ≤ 1/2

gcc 3.c -o 3 -lm
*/

#include <stdio.h>
#include <math.h>

void while_loop(double h)
{
    double x = 0, f, i;

    printf("do while method:");
    printf("\nx\t\tf(x)\n- - - - - - - - - - - -\n");
    i = 0.5 / h;
    do
    {
        if ( x <= 0.25 )
            f = exp(sin(x));
        else
            f = exp(x) - 1/(sqrt(x));
        printf("%lf      %lf\n", x, f);
        x += h;
        i--;
    } while (0 <= i);
}

void for_loop(double h)
{
    double x = 0, f;

    printf("for method:");
    printf("\nx\t\tf(x)\n- - - - - - - - - - - -\n");
    for (int i = 0; i <= 0.5 / h; i++)
    {
        if (x <= 0.25)
            f = exp(sin(x));
        else
            f = exp(x) - 1/(sqrt(x));
        printf("%lf      %lf\n", x, f);
        x += h;
    }
}

int main ()
{
    double h;

    printf ("Enter 0 < h < 0.5 (step) -> ");
    scanf ("%lf", &h);

    if (h > 0.0 && h <= 0.5)
    {
        while_loop(h);
        printf("\n");
        for_loop(h);
    }
    else
    {
        printf("Value is incorrect!\n");
    }

    return 0;
}
