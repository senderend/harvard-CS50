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

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];

    if (fread(header, sizeof(uint8_t), HEADER_SIZE, input) == 44)
    {
        if (fwrite(header, sizeof(uint8_t), HEADER_SIZE, output) == 44)
        {
            int16_t buffer;
            while (fread(&buffer, sizeof(uint16_t), 1, input))
            {
                buffer *= factor;
                fwrite(&buffer, sizeof(uint16_t), 1, output);
            }

        }
        else
        {
            printf("Header write error.\n");
            return 3;
        }
    }
    else
    {
        printf("Header read error.\n");
        return 2;
    }


    // TODO: Read samples from input file and write updated data to output file

    // Close files
    fclose(input);
    fclose(output);
}
