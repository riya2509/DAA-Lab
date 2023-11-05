#include <stdio.h>
#include <limits.h>

void matrixChainOrder(int p[], int n, int m[n][n], int s[n][n])
{
    for (int i = 1; i < n; i++)
    {
        m[i][i] = 0;
    }

    for (int len = 2; len < n; len++)
    {
        for (int i = 1; i < n - len + 1; i++)
        {
            int j = i + len - 1;
            m[i][j] = INT_MAX;

            for (int k = i; k < j; k++)
            {
                int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                if (q < m[i][j])
                {
                    m[i][j] = q;
                    s[i][j] = k;
                }
            }
        }
    }
}

void printOptimalParenthesization(int i, int j, int s[i][j], char matrix_name, int *counter)
{
    if (i == j)
    {
        printf(" %c%d ", matrix_name, (*counter)++);
    }
    else
    {
        printf("(");
        printOptimalParenthesization(i, s[i][j], s, matrix_name, counter);
        printOptimalParenthesization(s[i][j] + 1, j, s, matrix_name, counter);
        printf(")");
    }
}

int main()
{
    int n;
    FILE *inputFile = fopen("matrix.txt", "r");
    if (!inputFile)
    {
        perror("Error opening the input file");
        return 1;
    }

    fscanf(inputFile, "%d", &n);
    int p[n + 1];
    char matrix_names[n];
    int i, j;

    for (i = 1; i <= n; i++)
    {
        int row, col;
        fscanf(inputFile, "%d %d %c", &row, &col, &matrix_names[i - 1]);
        p[i - 1] = row;
        if (i == n)
        {
            p[i] = col;
        }
    }

    fclose(inputFile);

    int m[n][n], s[n][n];
    matrixChainOrder(p, n, m, s);

    printf("M Table:\n");
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

    printf("S Table:\n");
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            printf("%d ", s[i][j]);
        }
        printf("\n");
    }

    printf("Optimal parenthesization:");
    int counter = 1;
    printOptimalParenthesization(1, n - 1, s, matrix_names[0], &counter);
    printf("\n");

    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n - 1]);

    FILE *outputFile = fopen("output.txt", "w");
    if (!outputFile)
    {
        perror("Error opening the output file");
        return 1;
    }

    fprintf(outputFile, "M Table:\n");
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            fprintf(outputFile, "%d ", m[i][j]);
        }
        fprintf(outputFile, "\n");
    }

    fprintf(outputFile, "S Table:\n");
    for (i = 1; i < n; i++)
    {
        for (j = 1; j < n; j++)
        {
            fprintf(outputFile, "%d ", s[i][j]);
        }
        fprintf(outputFile, "\n");
    }

    fprintf(outputFile, "Optimal parenthesization:");
    counter = 1;
    printOptimalParenthesization(1, n - 1, s, matrix_names[0], &counter);
    fprintf(outputFile, "\n");

    fprintf(outputFile, "The optimal ordering of the given matrices requires %d scalar multiplications.\n", m[1][n - 1]);

    fclose(outputFile);

    return 0;
}
