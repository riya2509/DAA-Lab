#include <stdio.h>
#include <stdlib.h>
#include <time.h> // time related function

// merge function for merging two sorted sub-arrays into a single sorted array.
void merge(int arr[], int l, int m, int r, long long *comparisons)
// arr[]- Array to be sorted
// l - left index of the sub-array to be merged
// m - middle index of the sub-array to be merged
// r - right index of the sub-array to be merged.
// *comparisons- pointer to a variable keeping track of no. of comparisons during sorting
{
    int n1 = m - l + 1;
    int n2 = r - m;
    // calculating the sizes of the two sub-arrays to be merged

    int L[n1], R[n2]; // two temporary arrays L and R to hold elements of the two sub-arrays

    for (int i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
    // loops copying the elements from the main array arr into the temporary arrays L and R

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        (*comparisons)++;
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    // compares the elements in the temporary arrays L and R and then places the smaller
    // element into the main array arr

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }
    // handles any remaining elements in the L
    // copies the remaining elements into the main array arr

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
    // handles any remaining elements in the R
    // copies them into the main array arr.
}

// Function performing Merge sort algorithm recursively on the input array.
void mergeSort(int arr[], int l, int r, long long *comparisons)
{
    if (l < r)
    {
        int m = l + (r - l) / 2; // dividing the array into smaller sub-arrays
        mergeSort(arr, l, m, comparisons);
        mergeSort(arr, m + 1, r, comparisons); // sorting the array

        merge(arr, l, m, r, comparisons); // merging them back together
    }
}

int main()
{
    FILE *inputFile, *outputFile;
    int choice, n;

    printf("MAIN MENU (MERGE SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. Exit\n");
    printf("Enter option: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
        inputFile = fopen("inAsce.dat", "r");
        outputFile = fopen("outMergeAsce.dat", "w");
        break;
    case 2:
        inputFile = fopen("inDesc.dat", "r");
        outputFile = fopen("outMergeDesc.dat", "w");
        break;
    case 3:
        inputFile = fopen("inRand.dat", "r");
        outputFile = fopen("outMergeRand.dat", "w");
        break;
    case 4:
        return 0;
    }
    fscanf(inputFile, "%d", &n); // reading no. of elements from the input file
    int arr[n];
    for (int i = 0; i < n; i++)
        fscanf(inputFile, "%d", &arr[i]);
    fclose(inputFile); // input File closed

    long long comparisons = 0; // initializing a variable 'comparisons' for keeping track
    // of the no. of comparisons made during sorting

    clock_t start, end;
    // To store clock ticks before and after the sorting process starts
    start = clock();
    // clock() - returns the processor time consumed by the clock ticks

    mergeSort(arr, 0, n - 1, &comparisons);
    // Initiates the merge sort process on the array. Starts from index 0 to n-1

    end = clock(); // end time using clock()
    double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC * 1000000000.0;
    // elapsed time- is calculated by taking the difference between end and start and then
    //  converting it to nanoseconds.

    // CLOCKS_PER_SEC- defines the number of clock ticks per second.

    fprintf(outputFile, "Sorted Array:\n");
    for (int i = 0; i < n; i++)
        fprintf(outputFile, "%d ", arr[i]);
    fprintf(outputFile, "\nNumber of Comparisons: %lld\n", comparisons);
    fprintf(outputFile, "Execution Time: %.2lf nanoseconds\n", elapsedTime);
    fclose(outputFile);

    printf("Sorting completed. Results written to output file.\n");

    return 0;
}
