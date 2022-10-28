#include <stdio.h>
#include <math.h>
int main ()
{
    double h = 0.125, xi, f, n, f1, e, rynge, k, s, d;
    int i;
    printf("Enter e -> ");
    scanf("%lf", &e);   
    n = 2;
    do
    { 
        s = (0.5 / (h / (n / 2))) - 1;  
        d = (0.5 / (h / n)) - 1;
        f =0;
        f1 =0;
        for (i = 0; i <= s; i++)
        {
            xi += (i * (h / (n/2)));
            if (xi <= 0.25)
            {
                f += exp(sin(xi + ((h / (n / 2))/2)));
            }
            else
            {
                f += exp(xi + (h / (n / 2))/2) - 1/(sqrt(xi + (h / (n / 2))/2));
            }
        }
        for (k = 0; k <= d; k++)
        {
            xi += (k * (h / n));
            if (xi <= 0.25)
            {
                f1 += exp(sin((xi * 2) + (h / n)/2));
            }
            else
            {
                f1 += exp((xi * 2) + (h / n)/2) - 1/(sqrt((xi * 2) + (h / n)/2));
            }
        }
        f *= (h / (n / 2));
        f1 *= (h / n);
        rynge = (f1 - f)/3;        
        n *= 2;
    } while (rynge < e);
    printf("%lf\n%lf\n%lf\n", rynge, f, f1);
    return 0;
}