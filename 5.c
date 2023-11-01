#include <stdio.h>
#include <math.h>
unsigned int fr(unsigned int n)
{
    if (n > 0)
    {
        unsigned int k = n % 10;
        fr(n/10);
        printf("%u ", k);
        return 0;
    }
}
unsigned int fl(unsigned int n)
{
    unsigned int y = n, k = 0, i, d, x; 
    while (y > 0)
    {
        y /= 10;
        k++;
    }
    for(i = 0; i < k; i++)
    {
        d = pow(10, k - i - 1);
        x = (n - (n % d)) / d;
        n %= d;
        printf("%u ", x);
    }
    return 0;
}
int main ()
{
    unsigned int n;
    printf("Десятичное число n одноразрядными числами\nn -> ");
    scanf("%u", &n);
    fr(n);
    printf("- RECURSION\n");
    fl(n);
    printf("- CYCLE\n");
    return 0;
}
