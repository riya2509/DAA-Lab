#include <stdio.h>

int main()
{
    unsigned int number;
    printf("Enter a number: ");
    scanf("%u", &number);

    // Extracting each byte
    // 0xFF hexadecimal numerical system which shifts the bit to the right
    // and then performs bitwise AND operation
    unsigned char byte1 = (number >> 24) & 0xFF;
    unsigned char byte2 = (number >> 16) & 0xFF;
    unsigned char byte3 = (number >> 8) & 0xFF;
    unsigned char byte4 = number & 0xFF;

    // Printing the content of the variables
    printf("Byte 1: %u\n", byte1);
    printf("Byte 2: %u\n", byte2);
    printf("Byte 3: %u\n", byte3);
    printf("Byte 4: %u\n", byte4);

    return 0;
}