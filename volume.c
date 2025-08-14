// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file

    // Create buffer for header
    uint8_t header[HEADER_SIZE];

    // Read header into buffer
    fread(header, sizeof(uint8_t), HEADER_SIZE, input);

    // Write header into the output file
    fwrite(header, sizeof(uint8_t), HEADER_SIZE, output);

    // Read samples from input file and write updated data to output file

    // Create buffer for each sample
    int16_t buffer;

    // Read samples into buffer until the end of the file
    while (fread(&buffer, sizeof(int16_t), 1, input) != 0)
    {
        // Multiply the volume of each sample by factor
        buffer = buffer * factor;

        // Write samples to output file
        fwrite(&buffer, sizeof(int16_t), 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
