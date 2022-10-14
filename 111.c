//наибольшее если оно больше суммы двух других
//сумма минус наибольшее иначе
#include <stdio.h>
#include <math.h>
int main()
{
    float x, y, z, sum;


    printf("Enter x -> "); //ввод своих значений
    scanf("%f", &x);
    printf("Enter y -> ");
    scanf("%f", &y);
    printf("Enter z -> ");
    scanf("%f", &z);


    if ((x > y) && (x > z))
    { 
      if (x > (y + z))
        printf("%f\n",x);
      else 
        sum = ((y + z) - x);
        printf("%f\n", sum);
    }
    else if ((y > x) && (y > z))
    { 
      if (y > (x + z))
        printf("%f\n",y);
      else 
        sum = ((x + z) - y);
        printf("%f\n", sum); 
    }
    else
    { 
      if (z > (y + x))
        printf("%f\n",z);
      else 
        sum = ((y + x) - z);
        printf("%f\n", sum);  
    }
    return 0;
}