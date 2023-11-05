#include <stdio.h>
#include <limits.h>
// Function to print optimal parenthesization
void printOptimalParenthesis(int S[][100], int i, int j) {
    while (i == j) {
        printf("A%d ", i);
    } //else {
        /*printf("( ");
        printOptimalParenthesis(S, i, S[i][j]);
        printOptimalParenthesis(S, S[i][j] + 1, j);
        printf(") ");*/

        //printf("A%d ", i);
    }
//}

// Function to find the optimal parenthesization and number of scalar multiplications
void matrixChainOrder(int dims[], int n) {
    int M[n][n];    // M-table
    int S[n][n];    // S-table
    int i, j, k, L, q;

    // Initialize M-table with zeros
    for (i = 1; i < n; i++) {
        M[i][i] = 0;
    }
 for (i = 1; i < n; i++) {
        S[i][i] = 0;
    }

    // Calculate M and S tables
    for (L = 2; L < n; L++) {
        for (i = 1; i < n - L + 1; i++) {
            j = i + L - 1;
            M[i][j] = INT_MAX;

            for (k = i; k < j; k++) {
                q = M[i][k] + M[k + 1][j] + dims[i - 1] * dims[k] * dims[j];
                if (q < M[i][j]) {
                    M[i][j] = q;
                    S[i][j] = k;
                }
            }
        }
    }

    // Print M-table and S-table
    printf("M Table:\n");
    for (i = 1; i < n; i++) {
        for (j = 1; j < n; j++) {
            if (j >= i) {
                printf("%d ", M[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    printf("S Table:\n");
    for (i = 1; i < n; i++) {
        for (j = 1; j < n; j++) {
            if (j >= i) {
                printf("%d ", S[i][j]);
            } else {
                printf("0 ");
            }
        }
        printf("\n");
    }

    // Print optimal parenthesization
    printf("Optimal Parenthesization: ( ");
    printOptimalParenthesis(S, 1, n - 1);
    printf(")\n");

    // Print the number of scalar multiplications
    printf("The optimal ordering of the given matrices requires %d scalar multiplications.\n", M[1][n - 1]);
}

int main() {
    int n;
    printf("Enter the number of matrices: ");
    scanf("%d", &n);

    int dimensions[n + 1];
    printf("Enter row and col size for each matrix:\n");

    for (int i = 0; i < n; i++) {
        printf("Matrix A%d: ", i + 1);
        scanf("%d %d", &dimensions[i], &dimensions[i + 1]);
    }

    matrixChainOrder(dimensions, n + 1);

    return 0;
}
