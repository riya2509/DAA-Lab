#include <stdio.h>

struct pkt
{
    char ch1;
    char ch2[2];
    char ch3;
};

int main()
{
    int number;
    printf("Enter a number: ");
    scanf("%d", &number);

    // Create the structure variable
    struct pkt packet;

    // Break the number into its individual bytes and store them in the structure
    packet.ch1 = (number >> 16) & 0xFF;
    packet.ch2[0] = (number >> 8) & 0xFF;
    packet.ch2[1] = number & 0xFF;
    packet.ch3 = (number >> 24) & 0xFF;

    // Print the content of each member of the structure
    printf("Content of the structure:\n");
    printf("ch1: %d\n", packet.ch1);
    printf("ch2: %d %d\n", packet.ch2[0], packet.ch2[1]);
    printf("ch3: %d\n", packet.ch3);

    // Aggregating each member of the structure to form the original number
    int original_number = 0;
    original_number |= (packet.ch1 << 16);
    original_number |= (packet.ch2[0] << 8);
    original_number |= packet.ch2[1];
    original_number |= (packet.ch3 << 24);

    // Print the original number
    printf("Original Number: %d\n", original_number);

    return 0;
}