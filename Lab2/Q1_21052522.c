// The program includes the necessary standard C library headers, <stdio.h> for file
// input/output operations and <stdlib.h> for the atoi function. It also declares the
//  decimalToBinary function, which is responsible for converting decimal numbers to binary
// using recursion
#include <stdio.h>
#include <stdlib.h>

void decimalToBinary(FILE *inputFile, FILE *outputFile, int n)
{
    // parameter *inputFile - A pointer to the input file where the decimal numbers are stored.
    // parameter *outputFile - A pointer to the output file binary numbers stored
    // n - no. of decimal numbers to convert to binary

    if (n > 0) // The function first checks if n is greater than 0.
    // If n is zero or negative, the recursion will stop.
    {
        int num;
        // reading the next decimal number using fscanf
        if (fscanf(inputFile, "%d", &num) != EOF)
        {
            // binary representation is obtained by iterating over each
            // bit (from the most significant bit to the least significant bit) of
            // the decimal number and extracting the corresponding bit using bitwise operations.
            fprintf(outputFile, "The binary equivalent of %d is ", num);
            for (int i = 31; i >= 0; i--)
            {
                int bit = (num >> i) & 1;
                fprintf(outputFile, "%d", bit);
            }
            fprintf(outputFile, "\n");

            // recursively with n - 1 to process the next decimal number from the input file.
            decimalToBinary(inputFile, outputFile, n - 1);
        }
    }
}

// It handles command-line arguments, opens the input and output files,
// and calls the decimalToBinary function to perform the conversion.
int main(int argc, char *argv[])
{

    // first checks if the correct number of command-line arguments
    //  is provided (4 arguments, including the program name)
    if (argc != 4)
    {
        printf("Usage: %s <n> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    //  converts the first argument argv[1]
    // (representing "n") to an integer using the atoi function.
    int n = atoi(argv[1]);
    // extracting the input file name from argv[2] and the output file name from argv[3]
    char *inputFileName = argv[2];
    char *outputFileName = argv[3];

    // input file in read mode "r" and the output file in write mode "w".
    //  If any file fails to open, it displays an error message and exits the program.

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (!inputFile || !outputFile)
    {
        printf("Error opening files.\n");
        return 1;
    }

    decimalToBinary(inputFile, outputFile, n);

    // closing input and output files
    fclose(inputFile);
    fclose(outputFile);

    // Display the contents of the output file
    printf("Contents of the output disc file \"%s\":\n", outputFileName);
    outputFile = fopen(outputFileName, "r"); // reopening output file in read mode
    if (!outputFile)
    {
        printf("Error opening the output file for reading.\n");
        return 1;
    }

    char line[100];
    while (fgets(line, sizeof(line), outputFile))
    {
        printf("%s", line);
    }

    fclose(outputFile);
    return 0;
}
