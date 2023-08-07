#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// Function to find the total number of duplicate elements
int countDuplicates(int arr[], int n)
{
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
            {
                count++;
                break; // Move to the next unique element
            }
        }
    }
    return count;
}

// Function to find the most repeating element in the array
int findMostRepeatingElement(int arr[], int n)
{
    int maxCount = 0;
    int mostRepeatingElement = arr[0];

    for (int i = 0; i < n; i++)
    {
        int count = 1;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[i] == arr[j])
                count++;
        }
        if (count > maxCount)
        {
            maxCount = count;
            mostRepeatingElement = arr[i];
        }
    }
    return mostRepeatingElement;
}

int main()
{
    char filename[100];
    int n, arr[MAX_SIZE];

    printf("Enter the file name (e.g., data.txt): ");
    scanf("%s", filename);

    // Open the file in read mode
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    // Read the integers from the file and store them in the array
    int i = 0;
    while (fscanf(file, "%d", &arr[i]) == 1 && i < MAX_SIZE)
    {
        i++;
    }
    n = i; // Save the number of elements in the array

    // Close the file
    fclose(file);

    // Task a) Find the total number of duplicate elements
    int totalDuplicates = countDuplicates(arr, n);
    printf("Total number of duplicate elements: %d\n", totalDuplicates);

    // Task b) Find the most repeating element in the array
    int mostRepeatingElement = findMostRepeatingElement(arr, n);
    printf("Most repeating element: %d\n", mostRepeatingElement);

    return 0;
}
