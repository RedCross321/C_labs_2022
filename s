#include <stdio.h>
#include <math.h>
double integrate(int n)
{
    int i;
    const double h = 3 / n;
    const double h2 = h / 2;
    printf ("%lf\n", h);
    printf ("%lf\n", h2);
    double k = 0.0, x;
    for (i = 0; i < n; i++)
        {
            x = i * h + h2 - 1;
            if (i <= (n * (2 / 3)))
                k += exp((-2)*sin(x));
            else
                k += ((x * x) - (1 / tan(x))); 
        }
    printf ("%lf\n", k);
    printf ("%lf\n", h);
    return k*h;
}
int main()
{
    unsigned int n = 10;
    double e;
    printf ("Введите точность -> ");
    scanf("%lf", &e);
    double integrate1 = integrate(n);
    double integrate2 = integrate(n*2);
    printf("%.5lf\n%.5lf\n", integrate2, integrate1);
    while (fabs((integrate2 - integrate1)/3) >= e)  
    {
        n *= 2;
        integrate1 = integrate2;
        integrate2 = integrate(n*2);
    }              
    printf("Контрольное значение интеграла: 0,23431.\nИтоговое значение интеграла: %.5lf\n", integrate2);
}
