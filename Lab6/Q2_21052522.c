#include <stdio.h>
#include <stdlib.h>

// Define a structure SYMBOL to represent characters and frequencies
struct SYMBOL
{
    char alphabet;
    int frequency;
};

// Define a structure NODE for Huffman tree nodes
struct NODE
{
    struct SYMBOL symbol;
    struct NODE *left;
    struct NODE *right;
};

// Define a structure for the Min-Priority Queue
struct MinPriorityQueue
{
    int size;
    struct NODE **array;
};

// Function to create a new node
struct NODE *newNode(struct SYMBOL symbol)
{
    struct NODE *node = (struct NODE *)malloc(sizeof(struct NODE));
    node->symbol = symbol;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to create a new Min-Priority Queue
struct MinPriorityQueue *createMinPriorityQueue(int capacity)
{
    struct MinPriorityQueue *queue = (struct MinPriorityQueue *)malloc(sizeof(struct MinPriorityQueue));
    queue->size = 0;
    queue->array = (struct NODE **)malloc(capacity * sizeof(struct NODE *));
    return queue;
}

// Function to swap two nodes
void swapNodes(struct NODE **a, struct NODE **b)
{
    struct NODE *temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify function for Min-Priority Queue
void minHeapify(struct MinPriorityQueue *queue, int index)
{
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < queue->size && queue->array[left]->symbol.frequency < queue->array[smallest]->symbol.frequency)
        smallest = left;

    if (right < queue->size && queue->array[right]->symbol.frequency < queue->array[smallest]->symbol.frequency)
        smallest = right;

    if (smallest != index)
    {
        swapNodes(&queue->array[index], &queue->array[smallest]);
        minHeapify(queue, smallest);
    }
}

// Function to build a Min-Priority Queue
struct MinPriorityQueue *buildMinPriorityQueue(struct SYMBOL symbols[], int n)
{
    struct MinPriorityQueue *queue = createMinPriorityQueue(n);

    for (int i = 0; i < n; i++)
        queue->array[i] = newNode(symbols[i]);

    queue->size = n;

    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(queue, i);

    return queue;
}

// Function to extract the minimum node from Min-Priority Queue
struct NODE *extractMin(struct MinPriorityQueue *queue)
{
    struct NODE *minNode = queue->array[0];
    queue->array[0] = queue->array[queue->size - 1];
    queue->size--;
    minHeapify(queue, 0);
    return minNode;
}

// Function to insert a node into Min-Priority Queue
void insert(struct MinPriorityQueue *queue, struct NODE *node)
{
    queue->size++;
    int i = queue->size - 1;
    while (i > 0 && node->symbol.frequency < queue->array[(i - 1) / 2]->symbol.frequency)
    {
        queue->array[i] = queue->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    queue->array[i] = node;
}

// Function to build the Huffman tree
struct NODE *buildHuffmanTree(struct SYMBOL symbols[], int n)
{
    struct NODE *left, *right, *top;
    struct MinPriorityQueue *queue = buildMinPriorityQueue(symbols, n);

    while (queue->size > 1)
    {
        left = extractMin(queue);
        right = extractMin(queue);

        // Create a new node with a frequency equal to the sum of the two nodes' frequencies
        top = newNode((struct SYMBOL){'\0', left->symbol.frequency + right->symbol.frequency});
        top->left = left;
        top->right = right;

        insert(queue, top);
    }

    return extractMin(queue);
}

// Function to perform an in-order traversal of the Huffman tree
void inorderTraversal(struct NODE *root, FILE *outputFile)
{
    if (root)
    {
        inorderTraversal(root->left, outputFile);

        // Print only non-empty symbols
        if (root->symbol.alphabet != '\0')
            fprintf(outputFile, "%c", root->symbol.alphabet);

        inorderTraversal(root->right, outputFile);
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

    int num_alphabets;
    printf("Enter the number of distinct alphabets: ");
    fscanf(inputFile, "%d", &num_alphabets);

    struct SYMBOL symbols[num_alphabets];

    printf("Enter the alphabets: ");
    for (int i = 0; i < num_alphabets; i++)
    {
        fscanf(inputFile, " %c", &symbols[i].alphabet);
    }

    printf("Enter its frequencies: ");
    for (int i = 0; i < num_alphabets; i++)
    {
        fscanf(inputFile, "%d", &symbols[i].frequency);
    }

    struct NODE *root = buildHuffmanTree(symbols, num_alphabets);

    fprintf(outputFile, "In-order traversal of the tree (Huffman): ");
    inorderTraversal(root, outputFile);

    fprintf(outputFile, "\n");

    fclose(inputFile);
    fclose(outputFile);

    printf("Output written to 'output.txt'.\n");

    return 0;
}
