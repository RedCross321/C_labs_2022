//e^sin(x), 0 ≤ x ≤ 1/4
//e^x - 1/sqrt(x), 1/4 < x ≤ 1/2
//Контрольное значение интеграла: 0,23431.
#include <stdio.h>
#include <math.h>
int main ()
{
    double h = 0.125, xi, f, n, f1, e, rynge;
    int i;
    printf("Enter e -> ");
    scanf("%lf", &e);   
    f = 0;
    f1 = 0;
    n = 2;
    do
    {   
        xi = 0;
        for (i = 0; i <= 3; i++)
        {
            xi += (i * h);
            if (xi <= 0.125)
            {
                f += exp(sin((xi + h/2)/(n/2)));
                f1 += exp(sin((xi + h/2)/n));
            }
            else
            {
                f += exp((xi + h/2)/(n/2)) - 1/(sqrt((xi + h/2)/(n/2)));
                f1 += exp(((xi + h/2)/n)) - 1/(sqrt(((xi + h/2)*n)));
            }
        }
        f *= ((n / 2) * h);
        f1 *= (n * h);
        rynge = (f1 - f)/3;        
        n *= 2;
    } while (rynge < e);
    printf("%lf\n%lf\n%lf\n", rynge, f, f1);
    return 0;
}