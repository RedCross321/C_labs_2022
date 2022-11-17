#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill(int n, int A[])
{
    int i, k;
    for (i = 0; i < n; i++)
        A[i] = rand () % 101 - 50;
}
void raskid(int n, int P[], int N[], int A[])
{
    int i, x = 0, y = 0;
    for (i = 0; i < n; i++)
    {
        if (A[i] >= 0)
        {
            P[x] = A[i];
            x++;
        }
        else
        {
            N[y] = A[i];
            y++;
        }
    }
    printf("\nПоложительный массив: ");
    for (i = 0; i < x; i++)
        printf("%d  ", P[i]);
    printf("\nОтрицательный массив: ");
    for (i = 0; i < y; i++)
        printf("%d  ", N[i]); 
}
int main()
{
    srand(time(NULL));
    int n;
    printf("n -> ");
    scanf("%d", &n);
    int A[n], i, N[n], P[n];
    fill(n, A);
    printf("Основной массив: ");
    for (i = 0; i < n; i++)
        printf("%d  ", A[i]);
    raskid(n, P, N, A);
    printf("\n");
    return 0;
}
