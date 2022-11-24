#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fill(int n, int A[], int k)
{
    for (int i = 0; i < n; i++)
    {
        A[i] = rand () % 101 - 50;
        if (A[i] >= 0)
            k++;
    }
    return k;    
}
int raskid(int n, int A[], int k)
{
    int x = 0, y = 0;
    int P[k], N[n - k];
    for (int i = 0; i < n; i++)
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
    for (int i = 0; i < x; i++)
        printf("%d  ", P[i]);
    printf("\nОтрицательный массив: ");
    for (int i = 0; i < y; i++)
        printf("%d  ", N[i]); 
}
int main()
{
    srand(time(NULL));
    int n, k = 0;
    printf("n -> ");
    scanf("%d", &n);
    int A[n];
    k = fill(n, A, k);
    printf("Основной массив: ");
    for (int i = 0; i < n; i++)
        printf("%d  ", A[i]);
    raskid(n, A, k);
    printf("\n");
    return 0;
}