#include <stdio.h>
#include <stdlib.h>

// Function to swap the values of two variables using pointers
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <value1> <value2>\n", argv[0]);
        return 1;
    }

    // atoi----converts a character string to an integer value
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);

    printf("Before swapping: num1 = %d, num2 = %d\n", num1, num2);

    // Calling the swap function with the addresses of num1 and num2
    swap(&num1, &num2);

    printf("After swapping: num1 = %d, num2 = %d\n", num1, num2);

    return 0;
}