//e^sin(x), 0 ≤ x ≤ 1/4
//e^x - 1/sqrt(x), 1/4 < x ≤ 1/2
#include <stdio.h>
#include <math.h>
int main ()
{
    double x = 0, h, f, i, n;
    printf ("Enter h (step) -> ");
    scanf ("%lf", &h);
    printf("\nx             f(x)\n- - - - - - - - - - - -\n");
    i = 0.5 / h;
    do
    {
        if ( n < (i / 2))
        {
            f = exp(sin(x));
            printf("%lf      %lf\n", x, f);
            x += h;
            n++;
        }
        else
        {
            f = exp(x) - 1/(sqrt(x));
            printf("%lf      %lf\n", x, f);
            x += h;
            n++;
        }
    } while (n < i);
    return 0;
}