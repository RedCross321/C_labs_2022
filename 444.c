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
    n = 2;
    do
    {   
        for (i = 0; i <= 3; i++)
        {
            xi = (i * (n / 2) * h);
            if (xi <= 0.25)
            {
                f += exp(sin(xi + ((n / 2) * h)/2));
                f1 += exp(sin((xi * 2) + (n * h)/2));
            }
            else
            {
                f += exp(xi + ((n / 2) * h)/2) - 1/(sqrt(xi + ((n / 2) * h)/2));
                f1 += exp((xi * 2) + (n * h)/2) - 1/(sqrt((xi * 2) + (n * h)/2));
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

      //  f *= ((n / 2) * h);
        //f1 *= (n * h);

        //f *= (i * h);
        //f1 *= (h * (i / 2));
         //   rynge = (f1 - f)/3;

























































/*
        {
            if (i <= 2)
            {
                f += exp(sin(xi));     
            }
            else
            {
                f += exp(xi) - 1/(sqrt(xi));
            }
        }










        if (i <= (n / 2))
        {
            f = exp(sin(x));
            printf("%lf      %lf\n", x, f);
            x += h;
        }
        else
        {
            f = exp(x) - 1/(sqrt(x));
            printf("%lf      %lf\n", x, f);
            x += h;
        }
*/