#include <stdio.h>
#include <stdlib.h>

void insertionSort(int arr[], int n, long long int *comparisons)
{
    int i, j, key;
    for (i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            (*comparisons)++;
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void printArrayToFile(int arr[], int n, const char *filename)
{
    FILE *file = fopen(filename, "w");
    if (file == NULL)
    {
        printf("Error opening file %s.\n", filename);
        exit(1);
    }
    for (int i = 0; i < n; i++)
    {
        fprintf(file, "%d ", arr[i]);
    }
    fclose(file);
}

void displayFileContent(const char *filename)
{
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file %s.\n", filename);
        exit(1);
    }
    int num;
    while (fscanf(file, "%d", &num) != EOF)
    {
        printf("%d ", num);
    }
    fclose(file);
}

int main()
{
    int choice;
    long long int comparisons = 0;

    do
    {
        printf("MAIN MENU (INSERTION SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. Exit\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        if (choice >= 1 && choice <= 3)
        {
            FILE *inputFile;
            FILE *outputFile;
            const char *inputFilename, *outputFilename;

            switch (choice)
            {
            case 1:
                inputFilename = "inAsce.dat";
                outputFilename = "outInsAsce.dat";
                break;
            case 2:
                inputFilename = "inDesc.dat";
                outputFilename = "outInsDesc.dat";
                break;
            case 3:
                inputFilename = "inRand.dat";
                outputFilename = "outInsRand.dat";
                break;
            }

            inputFile = fopen(inputFilename, "r");
            if (inputFile == NULL)
            {
                printf("Error opening file %s.\n", inputFilename);
                return 1;
            }

            int n;
            fscanf(inputFile, "%d", &n);
            int arr[n];
            for (int i = 0; i < n; i++)
            {
                fscanf(inputFile, "%d", &arr[i]);
            }
            fclose(inputFile);

            comparisons = 0;
            insertionSort(arr, n, &comparisons);

            printArrayToFile(arr, n, outputFilename);

            printf("Before Sorting: ");
            displayFileContent(inputFilename);
            printf("\nAfter Sorting: ");
            displayFileContent(outputFilename);
            printf("\nNumber of Comparisons: %lld\n", comparisons);

            if (comparisons == 0)
            {
                printf("Scenario: Best-case\n");
            }
            else if (comparisons == (n * (n - 1)) / 2)
            {
                printf("Scenario: Worst-case\n");
            }
        }
        else if (choice != 4)
        {
            printf("Invalid choice. Please enter a valid option.\n");
        }

    } while (choice != 4);

    return 0;
}
