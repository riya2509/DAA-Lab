
//  starts by reading the size of the array n from the user, which represents the number of elements in the array.

//  dynamically allocating memory for two arrays, arr and prefixSum, both of size n. The arr array  stores the input integers, and the prefixSum array  stores the prefix sum values.

// It then proceeds to read the elements of the array from a file named "input.txt". Each element is stored in the arr array.

// After reading the elements, the program calls the calculatePrefixSum function. This function takes the arr array, its size n, and the prefixSum array as input arguments. It calculates the prefix sum for each element of the array and stores the values in the prefixSum array.

// The calculatePrefixSum function iterates through the arr array and calculates the prefix sum at each index. For index i, the prefix sum is the sum of elements from arr[0] to arr[i]. It uses the previously calculated prefix sum to compute the current prefix sum efficiently.

// After prefixSum array  calculated,  program opens  output file  to write the results.

//  writes the prefix sum array to the output file. Each element of the prefixSum array is written to a new line in the file.

// Finally frees the dynamically allocated memory for both arr and prefixSum and returns 0 to indicate successful execution.

#include <stdio.h>
#include <stdlib.h>

void calculatePrefixSum(int arr_22[], int n_22, int prefixSum_22[])
{
    prefixSum_22[0] = arr_22[0];

    for (int i_22 = 1; i_22 < n_22; i_22++)
    {
        prefixSum_22[i_22] = prefixSum_22[i_22 - 1] + arr_22[i_22];
    }
}

int main()
{
    int n_22;

    // Read the size of the array from the user
    printf("Enter the size of the array: ");
    scanf("%d", &n_22);

    if (n_22 <= 0)
    {
        printf("Invalid array size.\n");
        return 1;
    }

    int *arr = (int *)malloc(n_22 * sizeof(int));
    int *prefixSum = (int *)malloc(n_22 * sizeof(int));

    if (arr == NULL || prefixSum == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Read the array elements from the file (assuming the file is named "input.txt")
    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        free(arr);
        free(prefixSum);
        return 1;
    }

    printf("Enter %d elements:\n", n_22);
    for (int i = 0; i < n_22; i++)
    {
        if (fscanf(file, "%d", &arr[i]) != 1)
        {
            printf("Error reading element from the file.\n");
            fclose(file);
            free(arr);
            free(prefixSum);
            return 1;
        }
    }

    fclose(file);

    calculatePrefixSum(arr, n_22, prefixSum);

    // Write the prefix sum array to the output file "output.txt"
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Error opening the output file.\n");
        free(arr);
        free(prefixSum);
        return 1;
    }

    fprintf(outputFile, "Prefix Sum Array:\n");
    for (int i = 0; i < n_22; i++)
    {
        fprintf(outputFile, "%d ", prefixSum[i]);
    }
    fprintf(outputFile, "\n");

    fclose(outputFile);

    free(arr);
    free(prefixSum);
    return 0;
}
