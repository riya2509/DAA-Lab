#include <stdio.h>
#include <string.h>

// Function to find the LCS and its length
void findLCS(char X[], char Y[], int m, int n, char lcs[], int* length) {
    int L[m + 1][n + 1];

    // Build the L[m+1][n+1] table in bottom-up fashion
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0)
                L[i][j] = 0;
            else if (X[i - 1] == Y[j - 1]) {
                L[i][j] = L[i - 1][j - 1] + 1;
            } else {
                L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
            }
        }
    }

    // Reconstruct the LCS
    int i = m, j = n;
    int index = L[m][n];
    while (i > 0 && j > 0) {
        if (X[i - 1] == Y[j - 1]) {
            lcs[index - 1] = X[i - 1];
            i--;
            j--;
            index--;
        } else if (L[i - 1][j] > L[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // Calculate the length of LCS
    *length = L[m][n];
}

int main() {
    char X[100], Y[100], lcs[100];
    int length;

    // Input two strings
    printf("Enter the first string into an array: ");
    fgets(X, sizeof(X), stdin);
    X[strcspn(X, "\n")] = '\0';  // Remove newline character

    printf("Enter the second string into an array: ");
    fgets(Y, sizeof(Y), stdin);
    Y[strcspn(Y, "\n")] = '\0';  // Remove newline character

    // Find LCS and its length
    int m = strlen(X);
    int n = strlen(Y);

    findLCS(X, Y, m, n, lcs, &length);

    // Print the LCS
    printf("LCS: %s\n", lcs);

    // Print the length of LCS
    printf("LCS Length: %d\n", length);

    return 0;
}