//y=arccos(2sinx),z=sqrt(cos(y^2))
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
        printf("Value is incorrect!\n");
    return 0;
}
