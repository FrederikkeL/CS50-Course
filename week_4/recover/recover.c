#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }
    // opens file specified by user
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Couldn't open %s\n", argv[1]);
        return 1;
    }

    BYTE *buffer = malloc(sizeof(BYTE) * 512);
    char *filename = malloc(sizeof(char) * 8);
    int counter = 0;
    FILE *file;
    // reads data from file into memory
    while (fread(buffer, 1, 512, input) == 512)
    {
        // if bytes is 0xff 0xd8 0xff and then one of 0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7, 0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, or 0xef
        //  start new file and store everything stop when reaching same sequence til end of file
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            ((buffer[3] & 0xf0) == 0xe0))
        {
            sprintf(filename, "%03i.jpg", counter);
            printf("%s", filename);
            if (counter == 0)
            {
                file = fopen(filename, "w");
                counter++;
            }
            else
            {
                fclose(file);
                file = fopen(filename, "w");
                counter++;
            }
        }
        if (counter > 0)
        {
            fwrite(buffer, 1, 512, file);
        }
    }
    fclose(input);
    fclose(file);
    free(buffer);
    free(filename);
}