#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

// Declaring the size of a byte
typedef uint8_t BYTE;

// Define constants
#define BLOCK_SIZE 512

// Structure for JPEG file header
typedef struct
{
    BYTE jpegHeader[3];
    BYTE additionalInfo;
} __attribute__((__packed__))
JPEGFILEHEADER;

// Check if the file header is JPEG
bool isJPEG(JPEGFILEHEADER *jpeg)
{
    // Check the first 3 bytes
    if (jpeg->jpegHeader[0] == 0xff && jpeg->jpegHeader[1] == 0xd8 && jpeg->jpegHeader[2] == 0xff)
    {
        // // Iterate from 0xe0 to 0xef
        // for (int i = 0xe0; i < 0xf0; i++)
        // {
        //     // Check the fourth byte
        //     if (jpeg->additionalInfo == i)
        //     {
        //         return true;
        //     }
        // }
        // return false;

        // Check only the first 4 bits is equals to 'e'
        if ((jpeg->additionalInfo & 0xf0) == 0xe0)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[])
{
    // Check usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image\n");
        return 1;
    }

    // Open file
    char *infile = argv[1];

    FILE *inptr = fopen(infile, "r");
    if (!inptr)
    {
        fprintf(stderr, "Could not open %s\n", infile);
        return 1;
    }

    // Declare a pointer to 512(BLOCK_SIZE) of BYTE
    BYTE *blockContent;
    blockContent = (BYTE *) malloc(BLOCK_SIZE);

    // Constructing a JPEG file header
    JPEGFILEHEADER *jpegFileHeader;
    jpegFileHeader = (JPEGFILEHEADER *) malloc(sizeof(BYTE) * 4);

    // String to store filenames
    char outfile[8];

    // Pointer to output file
    FILE *outptr = NULL;

    // Counter for JPEG encoutered
    int counter = 0;

    // Since fread() returns size, size == 0 is the EOF
    while (fread(blockContent, sizeof(BYTE), BLOCK_SIZE, inptr) > 0)
    {
        // Filling in the first three bytes of the block
        for (int i = 0; i < 3; i++)
        {
            jpegFileHeader->jpegHeader[i] = blockContent[i];
        }

        // Filling in the fourth byte of the block
        jpegFileHeader->additionalInfo = blockContent[3];

        // Check if the block has a valid JPEG file header
        if (isJPEG(jpegFileHeader))
        {
            // If file is opened, close it
            if (outptr != NULL)
            {
                fclose(outptr);
            }

            // Zero-pad the filenames
            sprintf(outfile, "%03i.jpg", counter);

            // Open the output file with write priviledges
            outptr = fopen(outfile, "w");

            // If unable to open the file
            if (outptr == NULL)
            {
                fprintf(stderr, "Unable to open %s", outfile);
                return 1;
            }

            // Increment the counter for filenames
            counter++;

            // Print success message to STDOUT
            fprintf(stdout, "%s is successfully recovered.\n", outfile);
        }

        // If the file is opened, keep writing
        if (outptr != NULL)
        {
            // Writing the block byte by byte
            for (int j = 0; j < BLOCK_SIZE; j++)
            {
                fwrite(&blockContent[j], sizeof(BYTE), 1, outptr);
            }
        }
    }

    // If file is opened, close it
    if (outptr != NULL)
    {
        fclose(outptr);
    }
    if (inptr != NULL)
    {
        fclose(inptr);
    }

    // Release memory of jpegFileHeader
    free(jpegFileHeader);

    // Release memory of blockContent
    free(blockContent);
}
