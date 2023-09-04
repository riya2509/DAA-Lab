#include <stdio.h>

// Function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform partitioning for Quick Sort
int partition(int arr[], int low, int high, long long int *comparisons)
{
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++)
    {
        (*comparisons)++;
        if (arr[j] < pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return i + 1;
}

// Function to perform Quick Sort
void quickSort(int arr[], int low, int high, long long int *comparisons)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high, comparisons);

        quickSort(arr, low, pivotIndex - 1, comparisons);
        quickSort(arr, pivotIndex + 1, high, comparisons);
    }
}

// Function to read data from a file and return the number of elements read
int readDataFromFile(const char *filename, int arr[])
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s\n", filename);
        return 0;
    }

    int numElements = 0;
    while (fscanf(file, "%d", &arr[numElements]) != EOF)
    {
        numElements++;
    }

    fclose(file);
    return numElements;
}

// Function to write sorted data to a file
void writeSortedDataToFile(const char *filename, int arr[], int numElements)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s for writing\n", filename);
        return;
    }

    for (int i = 0; i < numElements; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}

int main()
{
    int choice;
    printf("MAIN MENU (QUICK SORT)\n");
    printf("1. Ascending Data\n");
    printf("2. Descending Data\n");
    printf("3. Random Data\n");
    printf("4. Exit\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    int arr[500]; // Maximum size based on our requirement
    int numElements;
    const char *inputFilename;
    const char *outputFilename;

    switch (choice)
    {
    case 1:
        inputFilename = "inAsce.dat";
        outputFilename = "outQuickAsce.dat";
        break;
    case 2:
        inputFilename = "inDesc.dat";
        outputFilename = "outQuickDesc.dat";
        break;
    case 3:
        inputFilename = "inRand.dat";
        outputFilename = "outQuickRand.dat";
        break;
    case 4:
        printf("Exiting...\n");
        return 0;
    default:
        printf("Invalid choice\n");
        return 1;
    }

    numElements = readDataFromFile(inputFilename, arr);
    if (numElements == 0)
    {
        printf("No data read from file %s\n", inputFilename);
        return 1;
    }

    long long int comparisons = 0;
    quickSort(arr, 0, numElements - 1, &comparisons);
    writeSortedDataToFile(outputFilename, arr, numElements);

    printf("Sorted data written to %s\n", outputFilename);
    printf("Number of comparisons: %lld\n", comparisons);

    // Determining whether it's best-case or worst-case partitioning
    if (comparisons == ((numElements * (numElements - 1)) / 2))
    {
        printf("Partitioning is worst-case\n");
    }
    else if (comparisons == (numElements - 1))
    {
        printf("Partitioning is best-case\n");
    }

    return 0;
}
