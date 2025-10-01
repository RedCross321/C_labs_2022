/*
y = arccos(2sinx) 
z = cos(y^2)^0.5

ключ -lm для компиляции math.h

gcc 2.c -o 2 -lm
*/

#include <stdio.h>
#include <math.h>

int main()
{
    double x, y, z;

    printf("Enter x {0.25 <= x <= 0.52} -> ");
    scanf("%lf", &x);

    if (x >= 0.25 && x <= 0.52)
    {
        y = acos(2*sin(x));
        z = sqrt(cos(y * y));
        printf("y(x) = %lf\nz(y) = %lf\n", y, z);
    }
    else
    {
        printf("Value is incorrect!\n");
    }
    return 0;
}
