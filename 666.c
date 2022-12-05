#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fill(int n, int A[])
{
    for (int i = 0; i < n; i++)
        A[i] = rand () % 101 - 50;
}
int raskid(int n, int A[], int P[], int N[])
{
    int x = 0, y = 0;
    for (int i = 0; i < n; i++)
    {
        if (A[i] > 0)
        {
            P[x] = A[i];
            x++;
        }
        else if (A[i] < 0)
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
    int n, k = 0, d = 0;
    printf("n -> ");
    scanf("%d", &n);
    int A[n];
    fill(n, A);
    for (int i = 0; i < n; i++)
    {
        if (A[i] > 0)
            k++;
        else if (A[i] == 0)
            d++;
    }
    int P[k], N[n - k - d];
    printf("Основной массив: ");
    for (int i = 0; i < n; i++)
        printf("%d  ", A[i]);
    raskid(n, A, P, N);
    printf("\n");
    return 0;
}
