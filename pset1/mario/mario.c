#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height <= 0 || height > 8);

    // Looping through each row
    for (int i = 1; i <= height; i++)
    {
        // Print the spaces padded in front
        for (int j = 0; j < height - i; j++)
        {
            printf(" ");
        }

        // Print the hashtags
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Print the 2 spaces in between hashtags
        printf("  ");

        // Print the hashtags
        for (int j = 0; j < i; j++)
        {
            printf("#");
        }

        // Print the newline
        printf("\n");
    }
}