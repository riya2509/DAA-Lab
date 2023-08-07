// library to use functions like fopen, fclose
#include <stdio.h>

int findRotationCount(int arr[], int size)
// the above function implements binary search
// taking input of integer array arr and its size
// returns k - no. of times array has been rotated
{
    int low = 0, high = size - 1;
    while (low <= high)
    {
        if (arr[low] <= arr[high])
        {
            return low; // Array is already sorted
        }

        int mid = (low + high) / 2;
        int next = (mid + 1) % size;
        int prev = (mid - 1 + size) % size;

        if (arr[mid] <= arr[next] && arr[mid] <= arr[prev])
        {
            return mid;
        }
        else if (arr[mid] <= arr[high])
        {
            high = mid - 1;
        }
        else if (arr[mid] >= arr[low])
        {
            low = mid + 1;
        }
    }

    return -1; // Error: Input array is not rotated
}

int main()
{
    FILE *inputFile, *outputFile;
    // 2 file pointers to handle input and output
    int size, k;

    inputFile = fopen("inputP1.txt", "r");
    outputFile = fopen("outputP1.txt", "w");

    // input file in read mode "r" and the output file in write mode "w".
    //  If any file fails to open, it displays an error message and exits the program.

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

    k = findRotationCount(arr, size);
    // calling the findRotationCount function with the array arr and its size size
    //  as arguments to calculate the value of k

    fprintf(outputFile, "k = %d\n", k);

    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
//