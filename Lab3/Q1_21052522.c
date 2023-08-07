#include <stdio.h>

int binarySearchLeftmost(int arr[], int size, int key, int *numComparisons)
{
    int low = 0, high = size - 1, mid, result = -1;
    *numComparisons = 0;

    while (low <= high)
    {
        mid = low + (high - low) / 2;
        (*numComparisons)++;

        if (arr[mid] == key)
        {
            result = mid;
            high = mid - 1; // Move left to find the leftmost appearance
        }
        else if (arr[mid] < key)
        {
            low = mid + 1;
        }
        else
        {
            high = mid - 1;
        }
    }

    return result;
}

int main()
{
    FILE *inputFile, *outputFile;
    int size, key, numComparisons;
    inputFile = fopen("input.txt", "r");
    outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(inputFile, "%d", &size);
    int arr[size];
    for (int i = 0; i < size; i++)
    {
        fscanf(inputFile, "%d", &arr[i]);
    }

    fscanf(inputFile, "%d", &key);
    fclose(inputFile);

    int leftmostPosition = binarySearchLeftmost(arr, size, key, &numComparisons);

    if (leftmostPosition != -1)
    {
        fprintf(outputFile, "%d found at index position %d\n", key, leftmostPosition);
        fprintf(outputFile, "Number of comparisons: %d\n", numComparisons);
    }
    else
    {
        fprintf(outputFile, "%d not found in the array\n", key);
    }

    fclose(outputFile);

    return 0;
}
