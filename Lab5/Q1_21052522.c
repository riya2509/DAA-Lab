#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    int id;
    char *name;
    int age;
    int height;
    int weight;
};

// Function to swap two person structs
void swap(struct person *a, struct person *b)
{
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

// Function to create a min-heap based on age
void minHeapify(struct person *arr, int n, int i)
{
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].age < arr[smallest].age)
        smallest = left;

    if (right < n && arr[right].age < arr[smallest].age)
        smallest = right;

    if (smallest != i)
    {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Function to create a max-heap based on weight
void maxHeapify(struct person *arr, int n, int i)
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].weight > arr[largest].weight)
        largest = left;

    if (right < n && arr[right].weight > arr[largest].weight)
        largest = right;

    if (largest != i)
    {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

// Function to build a min-heap or max-heap based on user choice
void buildHeap(struct person *arr, int n, int choice)
{
    for (int i = n / 2 - 1; i >= 0; i--)
    {
        if (choice == 2)
            maxHeapify(arr, n, i); // Build max-heap
        else
            minHeapify(arr, n, i); // Build min-heap
    }
}

// Function to display the weight of the youngest person
void displayYoungestWeight(struct person *arr, int n)
{
    if (n > 0)
    {
        printf("Weight of the youngest person: %d\n", arr[0].weight);
    }
    else
    {
        printf("Heap is empty.\n");
    }
}

// Function to insert a new person into the min-heap
struct person *insertPerson(struct person *arr, int *n, struct person newPerson)
{
    (*n)++;
    arr = (struct person *)realloc(arr, (*n) * sizeof(struct person));
    arr[(*n) - 1] = newPerson;
    int i = (*n) - 1;

    while (i > 0 && arr[(i - 1) / 2].age > arr[i].age)
    {
        swap(&arr[i], &arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }

    return arr;
}

// Function to delete the oldest person from the min-heap
struct person *deleteOldestPerson(struct person *arr, int *n)
{
    if (*n <= 0)
    {
        printf("Heap is empty.\n");
        return arr;
    }

    if (*n == 1)
    {
        (*n)--;
        free(arr);
        arr = NULL;
        printf("Oldest person deleted.\n");
        return arr;
    }

    swap(&arr[0], &arr[(*n) - 1]);
    (*n)--;
    arr = (struct person *)realloc(arr, (*n) * sizeof(struct person));
    minHeapify(arr, *n, 0);
    printf("Oldest person deleted.\n");

    return arr;
}

int main()
{
    int choice, n = 0;
    struct person *people = NULL;

    while (1)
    {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
        {
            // Read data from a file
            FILE *file = fopen("data.txt", "r");
            if (file == NULL)
            {
                printf("Error opening the file.\n");
                break;
            }

            int id, age, height, weight;
            char name[100];
            while (fscanf(file, "%d %s %d %d %d", &id, name, &age, &height, &weight) != EOF)
            {
                struct person newPerson;
                newPerson.id = id;
                newPerson.name = strdup(name);
                newPerson.age = age;
                newPerson.height = height;
                newPerson.weight = weight;

                people = insertPerson(people, &n, newPerson);
            }

            fclose(file);
            printf("Data read and stored.\n");
            break;
        }

        case 2:
            // Create a Min-heap based on age
            buildHeap(people, n, 1);
            printf("Min-heap based on age created.\n");
            break;

        case 3:
            // Create a Max-heap based on weight
            buildHeap(people, n, 2);
            printf("Max-heap based on weight created.\n");
            break;

        case 4:
            // Display weight of the youngest person
            displayYoungestWeight(people, n);
            break;

        case 5:
        {
            // Insert a new person into the Min-heap
            struct person newPerson;
            printf("Enter the new person's id: ");
            scanf("%d", &newPerson.id);
            printf("Enter the new person's name: ");
            scanf("%s", newPerson.name);
            printf("Enter the new person's age: ");
            scanf("%d", &newPerson.age);
            printf("Enter the new person's height: ");
            scanf("%d", &newPerson.height);
            printf("Enter the new person's weight: ");
            scanf("%d", &newPerson.weight);

            people = insertPerson(people, &n, newPerson);
            printf("New person inserted into the Min-heap.\n");
            break;
        }

        case 6:
            // Delete the oldest person from the Min-heap
            people = deleteOldestPerson(people, &n);
            break;

        case 7:
            // Exit
            if (people != NULL)
            {
                for (int i = 0; i < n; i++)
                {
                    free(people[i].name);
                }
                free(people);
            }
            exit(0);

        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
