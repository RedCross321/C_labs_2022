//e^sin(x), 0 ≤ x ≤ 1/4
//e^x - 1/sqrt(x), 1/4 < x ≤ 1/2
#include <stdio.h>
#include <math.h>
int main ()
{
    double x = 0, h, f1, f2;
    printf ("Enter h (step) -> ");
    scanf ("%lf", &h);
    printf("\nx             f(x)\n- - - - - - - - - - - -\n");
    do
    {
        if ( x <= 0.25)
        {
            f1 = exp(sin(x));
            printf("%lf      %lf\n", x, f1);
            x += h;
        }
        else
        {
            f2 = exp(x) - 1/(sqrt(x));
            printf("%lf      %lf\n", x, f2);
            x += h;
        }
    } while (x <= 0.5);
    return 0;
}