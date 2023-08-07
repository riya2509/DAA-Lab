#include <stdio.h>

// Function to swap/exchange two numbers
void EXCHANGE(int *p, int *q)
{
    int temp = *p;
    *p = *q;
    *q = temp;
}

// Function to rotate right the first p2 elements of an array by 1 position
void ROTATE_RIGHT(int *p1, int p2)
{
    int last_element = *(p1 + p2 - 1); // Save the last element to shift later

    // Shift the elements to the right
    for (int i = p2 - 1; i > 0; i--)
    {
        *(p1 + i) = *(p1 + i - 1);
    }

    // Place the last element in the first position
    *p1 = last_element;
}

int main()
{
    FILE *file;
    char filename[100];
    int N, p2;

    printf("Enter the file name (e.g., input.txt): ");
    scanf("%s", filename);

    // Open the file in read mode
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read the size of the array (N)
    fscanf(file, "%d", &N);

    // Read the array elements from the file
    int A[N];
    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%d", &A[i]);
    }

    // Read the number of elements to rotate (p2)
    fscanf(file, "%d", &p2);

    // Close the input file
    fclose(file);

    printf("Before ROTATE:");
    for (int i = 0; i < N; i++)
    {
        printf(" %d", A[i]);
    }
    printf("\n");

    ROTATE_RIGHT(A, p2);

    printf("After ROTATE:");
    for (int i = 0; i < N; i++)
    {
        printf(" %d", A[i]);
    }
    printf("\n");

    // Open the output file in write mode
    file = fopen("output.txt", "w");
    if (file == NULL)
    {
        printf("Error creating the output file.\n");
        return 1;
    }

    // Write the rotated array to the output file
    fprintf(file, "After ROTATE:");
    for (int i = 0; i < N; i++)
    {
        fprintf(file, " %d", A[i]);
    }
    fprintf(file, "\n");

    // Close the output file
    fclose(file);

    return 0;
}
