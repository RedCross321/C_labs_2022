#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fail()
{
    printf("Memory allocation failure!\n");
    exit(EXIT_FAILURE);
}

void fill(int n, int m, int** A)
{
    int i, k;
    for (i = 0; i < m; i++)
    {
        for (k = 0; k < n; k++)
            A[i][k] = rand () % 101 - 50;
    }
}
int** minmax(int n, int m, int** A)
{
    int i, k, x = 0, result = 51, max = -51;
    for (i = 0; i < n; i++)
    {
        for (k = 0; k < m; k++)
        {
            if (A[k][i] > max)
                max = A[k][i];
        }
//        printf("%4i ", max);
        if (result > max)
            result = max;
        max = -51;            
    }
//    printf("- Максимумы столбцов\n");
    return result;
}
int main()
{
    srand(time(NULL));
    int n, m, k, x;
    printf("Количество столбцов -> ");
    scanf("%d", &n);
    printf("Количество строк -> ");
    scanf("%d", &m);

    int **A = (int **)malloc(m * sizeof(int *));
    if (!A)
        fail();
    int i, j;
    for (i = 0; i < m; i++)
    {
        A[i] = (int *)malloc(n * sizeof(int));
        if (!A[i])
            fail();
    }
    
    fill(n, m, A);
    for (i = 0; i < m; i++)
    {
        for (k = 0; k < n; k++)
            printf("%4d ", A[i][k]); 
        printf("\n");   
    }
    int** result = minmax(n, m, A);
    printf ("Минимум среди максимумов столбцов:%4d\n", result);

    for (i = 0; i < n; i++)
        free(A[i]);
    free(A);

    return 0;
}