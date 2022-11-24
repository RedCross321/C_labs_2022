#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill(int n, int m, int A[n][m])
{
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < m; k++)
            A[i][k] = rand () % 101 - 50;
    }
}
int minmax(int n, int m, int A[n][m])
{
    int i, k, x = 0, result = 51, max = -51;
    for (i = 0; i < m; i++)
    {
        for (k = 0; k < n; k++)
        {
            if (A[k][i] > max)
                max = A[k][i];
        }
        printf("%4i ", max);
        if (result > max)
            result = max;
        max = -51;            
    }
    printf("- Максимумы столбцов\n");
    return result;
}

int main()
{
    srand(time(NULL));
    int n, m, result;
    printf("Количество строк -> ");
    scanf("%d", &m);
    printf("Количество столбцов -> ");
    scanf("%d", &n);
    int A[n][m];
    fill(n, m, A);
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < m; k++)
            printf("%4d ", A[i][k]); 
        printf("\n");   
    }
    result = minmax(n, m, A);
    printf ("Минимум среди максимумов столбцов:%4i\n", result);
    return 0;
}
