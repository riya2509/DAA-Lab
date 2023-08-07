#include <stdio.h>

int gcd(int a, int b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

void processPairs(FILE *inputFile, FILE *outputFile)
{
    int num1, num2;
    while (fscanf(inputFile, "%d %d", &num1, &num2) == 2)
    {
        int result = gcd(num1, num2);
        fprintf(outputFile, "The GCD of %d and %d is %d\n", num1, num2, result);
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    char *inputFileName = argv[1];
    char *outputFileName = argv[2];

    FILE *inputFile = fopen(inputFileName, "r");
    FILE *outputFile = fopen(outputFileName, "w");

    if (!inputFile || !outputFile)
    {
        printf("Error opening files.\n");
        return 1;
    }

    processPairs(inputFile, outputFile);

    fclose(inputFile);
    fclose(outputFile);

    // Display the contents of the output file
    printf("Contents of the output disc file \"%s\":\n", outputFileName);
    outputFile = fopen(outputFileName, "r");
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
