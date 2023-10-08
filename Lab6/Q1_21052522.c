#include <stdio.h>
#include <stdlib.h>

// Defined a structure to represent an item
struct Item
{
    int item_id;                // to store  item's identifier,
    double item_profit;         // to store the item's profit
    double item_weight;         // store the item's weight
    double profit_weight_ratio; // to store the ratio of profit to weight for sorting purposes
};

// Function to perform max heapify for heap sort
void maxHeapify(struct Item arr[], int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = left;

    if (right < n && arr[right].profit_weight_ratio > arr[largest].profit_weight_ratio)
        largest = right;

    if (largest != i)
    {
        struct Item temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;
        maxHeapify(arr, n, largest);
    }
}

//  heap sort algorithm to sort the array of items based on their profit-to-weight ratios.
void heapSort(struct Item arr[], int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    for (int i = n - 1; i >= 0; i--)
    {
        struct Item temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;
        maxHeapify(arr, i, 0);
    }
}

int main()
{
    FILE *inputFile = fopen("input.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (inputFile == NULL || outputFile == NULL)
    {
        printf("File not found or cannot be opened.\n");
        return 1;
    }

    int num_items;
    printf("Enter the number of items: ");
    fscanf(inputFile, "%d", &num_items);

    struct Item items[num_items];

    // Input item details and calculate profit-to-weight ratios
    for (int i = 0; i < num_items; i++)
    {
        items[i].item_id = i + 1;
        fscanf(inputFile, "%lf %lf", &items[i].item_profit, &items[i].item_weight);
        items[i].profit_weight_ratio = items[i].item_profit / items[i].item_weight;
    }

    // reading the knapsack capacity from the input file,
    // for input and storing it in the knapsack_capacity variable
    double knapsack_capacity;
    printf("Enter the capacity of knapsack: ");
    fscanf(inputFile, "%lf", &knapsack_capacity);

    // Sort items in non-increasing order based on profit-to-weight ratio
    heapSort(items, num_items);

    double total_profit = 0.0;
    double current_weight = 0.0;

    fprintf(outputFile, "Item No profit Weight Amount to be taken\n");

    // loop iterates through the sorted items and selects items for the knapsack
    for (int i = 0; i < num_items; i++)
    {
        if (current_weight + items[i].item_weight <= knapsack_capacity)
        {
            // Take the whole item
            fprintf(outputFile, "%d %.6lf %.6lf 1.000000\n", items[i].item_id, items[i].item_profit, items[i].item_weight);
            total_profit += items[i].item_profit;
            current_weight += items[i].item_weight;
        }
        else
        {
            // Take a fraction of the item
            double fraction = (knapsack_capacity - current_weight) / items[i].item_weight;
            fprintf(outputFile, "%d %.6lf %.6lf %.6lf\n", items[i].item_id, items[i].item_profit, items[i].item_weight, fraction);
            total_profit += (fraction * items[i].item_profit);
            current_weight = knapsack_capacity;
            break;
        }
    }

    fprintf(outputFile, "Maximum profit: %.6lf\n", total_profit);

    fclose(inputFile);
    fclose(outputFile);

    printf("Output written to 'output.txt'.\n");

    return 0;
}
