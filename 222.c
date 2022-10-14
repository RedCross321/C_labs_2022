//y=arccos(2sinx),z=sqrt(cos(y^2))
#include <stdio.h>
#include <math.h>
int main()
{
    double x, y, z;
    printf("RAV:\n ( -0.45, -0.35) + 2*Pi*n, n e Z;\n ( 0.25, 0.55) + 2*Pi*n, n e Z;\n ( 2.65, 2.95) + 2*Pi*n, n e Z;\n ( 3.45, 3.55) + 2*Pi*n, n e Z;\nEnter x -> ");
    scanf("%lf", &x);
    y = acos(2*sin(x));
    if ((cos(y * y) >= 0) && (sin(x) >= -0.5 && sin(x) <= 0.5))
        {z = sqrt(cos(y * y));
        printf("y(x) = %lf\nz(y) = %lf\n", y, z);}
    else
        printf("Value is incorrect!\n");
    return 0;
}
