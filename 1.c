/*
Вывести значение наибольшего из трёх параметров x, y, z 
если оно больше суммы двух других параметров, 
и разность этой суммы и наибольшего значения иначе.

gcc 1.c -o 1
*/


#include <stdio.h>

void check(float max, float sum)
{
  if (max > sum)
  {
    printf("%f\n",max);
  }
  else
  {
    printf("%f\n", sum - max);
  }
}

int main()
{

    float x, y, z;

    printf("Enter x -> ");
    scanf("%f", &x);
    printf("Enter y -> ");
    scanf("%f", &y);
    printf("Enter z -> ");
    scanf("%f", &z);


    if ((x > y) && (x > z))
    { 
      check(x, y + z);
    }
    else if (y > z)
    { 
      check(y, x + z);
    }
    else
    { 
      check(z, x + y);
    }
    return 0;
}
