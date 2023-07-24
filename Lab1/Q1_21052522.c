//  program: Write a program to find out the second smallest and second largest
// element stored in an array of n integers.
// Input: Size of the array is „n‟ and read „n‟ number of elements from a disc file.
// Output: Second smallest, Second largest

#include <stdio.h>
#include <stdlib.h>

void findAns(int arr[], int n_22, int *secondSmallest_22, int *secondLargest_22)
{
    if (n_22 < 2)
    {
        printf("Array must contain atleast two elements. \n");
        return;
    }

    // Now initializing the variables to store the second smallest and second largest
    *secondSmallest_22 = *secondLargest_22 = arr[0];

    for (int i_22 = 1; i_22 < n_22; i_22++)
    {
        if (arr[i_22] < *secondSmallest_22)
        {
            *secondLargest_22 = *secondSmallest_22;
            *secondSmallest_22 = arr[i_22];
        }
        else if (arr[i_22] > *secondSmallest_22)
        {
            *secondLargest_22 = arr[i_22];
        }
    }
}

int main()
{
    int n_22;

    // Now reading the size of the array from the user

    printf("Enter the size of the array: ");
    scanf("%d", &n_22);

    if (n_22 <= 0)
    {
        printf("Invalid array size.\n");
        return 1;
    }

    int *arr = (int *)malloc(n_22 * sizeof(int));

    if (arr == NULL)
    {
        printf("Memory allocation failed.\n");
        return 1;
    }

    // Now Reading the array elements from the file  named "input.txt"

    FILE *file = fopen("input.txt", "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        free(arr);
        return 1;
    }

    printf("Enter %d elements:\n", n_22);
    for (int i_22 = 0; i_22 < n_22; i_22++)
    {
        if (fscanf(file, "%d", &arr[i_22]) != 1)
        {
            printf("Error reading element from the file.\n");
            fclose(file);
            free(arr);
            return 1;
        }
    }

    fclose(file);

    int secondSmallest_22, secondLargest_22;
    findAns(arr, n_22, &secondSmallest_22, &secondLargest_22);

    // Writing the results to the output file "output.txt"
    FILE *outputFile = fopen("output.txt", "w");
    if (outputFile == NULL)
    {
        printf("Error opening the output file.\n");
        free(arr);
        return 1;
    }
    fprintf(outputFile, "Second Smallest: %d\n", secondSmallest_22);
    fprintf(outputFile, "Second Largest: %d\n", secondLargest_22);

    fclose(outputFile);

    free(arr);
    return 0;
}
