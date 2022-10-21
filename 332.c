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
    n = 0.5 / h;
    for (i = 0; i <= n; i++)
    {
        if (i <= (n / 2))
            f = exp(sin(x));
        else
            f = exp(x) - 1/(sqrt(x));
        printf("%lf      %lf\n", x, f);
        x += h;
    }
    return 0;
}