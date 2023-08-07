#include <stdio.h>

// Function to check endianness
int isLittleEndian()
{
    // 32 bit non negative integer unsigned
    unsigned int num = 1;
    return (*(char *)&num == 1);
}

// Function to swap endianness
unsigned int swapEndianness(unsigned int num)
{
    return ((num >> 24) & 0xFF) |
           ((num >> 8) & 0xFF00) |
           ((num << 8) & 0xFF0000) |
           ((num << 24) & 0xFF000000);
}

int main()
{
    unsigned int number;

    // Determine the endianness of the host machine
    if (isLittleEndian())
    {
        printf("Host machine is Little Endian.\n");
    }
    else
    {
        printf("Host machine is Big Endian.\n");
    }

    printf("Enter a number: ");
    scanf("%u", &number);

    // Print the content of each byte location
    unsigned char *bytePtr = (unsigned char *)&number;
    printf("Content of each byte location:\n");
    for (int i = 0; i < sizeof(unsigned int); i++)
    {
        printf("Byte %d: %02X\n", i, bytePtr[i]);
    }

    // Convert the endianness of the number
    unsigned int convertedNumber = swapEndianness(number);
    printf("Number after converting the Endianness: %u\n", convertedNumber);

    return 0;
}