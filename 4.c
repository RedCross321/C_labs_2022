/*

e^sin(x), 0 ≤ x ≤ 1/4
e^x - 1/sqrt(x), 1/4 < x ≤ 1/2

Контрольное значение: 0,23431

gcc 4.c -o 4 -lm
*/

#include <stdio.h>
#include <math.h>

double integrate(int n)
{
    const double h = 0.5/n;
    double k = 0.0;
    for (int i = 0; i < n; i++)
        {
            double xi = i*h + 0.5*h;
            if (xi <= 0.25)
                k += exp(sin(xi));
            else
                k += exp(xi) - 1/(sqrt(xi)); 
        }
    return k*h;
}

int main()
{
    unsigned int n = 1000;
    double e;

    printf ("Enter error -> ");
    scanf("%lf", &e);

    double integrate1 = integrate(n);
    double integrate2 = integrate(n*2);

    while ((integrate1 - integrate2)/3 >= e)  
    {
        n *= 2;
        integrate1 = integrate2;
        integrate2 = integrate(n*2);
    }              
    printf("Control value: 0,23431.\nTotal value: %.5lf\n", integrate2);
}
