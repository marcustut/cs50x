#include <stdlib.h>
#include <math.h>
#include "helpers.h"

// Return the minimum value
int min(int x, int y)
{
    return (x < y) ? x : y;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Iterating through rows from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Iterating through cols from left to right
        for (int j = 0; j < width; j++)
        {
            // Taking the average of BGR values
            int avg = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            // Updating the current pixel to the average of old BGR values
            image[i][j] = (RGBTRIPLE)
            {
                .rgbtBlue = avg,
                .rgbtGreen = avg,
                .rgbtRed = avg
            };
        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a new blank array to store reflected pixels temporarily
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Iterating through rows from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Iterating through cols from right to left
        for (int j = width - 1; j >= 0; j--)
        {
            // Store the pixels in a temporary image
            temp[i][width - 1 - j] = image[i][j];
        }
    }

    // Iterating through rows from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Iterating through cols from left to right
        for (int j = 0; j < width; j++)
        {
            // Copy over the pixels stored
            image[i][j] = temp[i][j];
        }
    }

    // Free the memory of temporary image array
    free(temp);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a new blank array to store blurred pixels temporarily
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Iterate through rows from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Iterate through cols from left to right
        for (int j = 0; j < width; j++)
        {
            int red;
            int green;
            int blue;
            int counter;
            red = green = blue = counter = 0;

            // If center pixel exists
            if (i >= 0 && j >= 0)
            {
                red += image[i][j].rgbtRed;
                green += image[i][j].rgbtGreen;
                blue += image[i][j].rgbtBlue;
                counter++;
            }
            // If left pixel exists
            if (i >= 0 && j - 1 >= 0)
            {
                red += image[i][j - 1].rgbtRed;
                green += image[i][j - 1].rgbtGreen;
                blue += image[i][j - 1].rgbtBlue;
                counter++;
            }
            // If right pixel exists
            if (i >= 0 && j + 1 >= 0 && j + 1 < width)
            {
                red += image[i][j + 1].rgbtRed;
                green += image[i][j + 1].rgbtGreen;
                blue += image[i][j + 1].rgbtBlue;
                counter++;
            }
            // If top center pixel exists
            if (i - 1 >= 0 && j >= 0)
            {
                red += image[i - 1][j].rgbtRed;
                green += image[i - 1][j].rgbtGreen;
                blue += image[i - 1][j].rgbtBlue;
                counter++;
            }
            // If top left pixel exists
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                red += image[i - 1][j - 1].rgbtRed;
                green += image[i - 1][j - 1].rgbtGreen;
                blue += image[i - 1][j - 1].rgbtBlue;
                counter++;
            }
            // If top right pixel exists
            if (i - 1 >= 0 && j + 1 >= 0 && j + 1 < width)
            {
                red += image[i - 1][j + 1].rgbtRed;
                green += image[i - 1][j + 1].rgbtGreen;
                blue += image[i - 1][j + 1].rgbtBlue;
                counter++;
            }
            // If bottom center pixel exists
            if (i + 1 >= 0 && i + 1 < height && j >= 0)
            {
                red += image[i + 1][j].rgbtRed;
                green += image[i + 1][j].rgbtGreen;
                blue += image[i + 1][j].rgbtBlue;
                counter++;
            }
            // If bottom left pixel exists
            if (i + 1 >= 0 && i + 1 < height && j - 1 >= 0)
            {
                red += image[i + 1][j - 1].rgbtRed;
                green += image[i + 1][j - 1].rgbtGreen;
                blue += image[i + 1][j - 1].rgbtBlue;
                counter++;
            }
            // If bottom right pixel exists
            if (i + 1 >= 0 && i + 1 < height && j + 1 >= 0 && j + 1 < width)
            {
                red += image[i + 1][j + 1].rgbtRed;
                green += image[i + 1][j + 1].rgbtGreen;
                blue += image[i + 1][j + 1].rgbtBlue;
                counter++;
            }

            // Store the blurred pixels into temp array
            temp[i][j] = (RGBTRIPLE)
            {
                .rgbtRed = round(red / (counter * 1.0)),
                .rgbtGreen = round(green / (counter * 1.0)),
                .rgbtBlue = round(blue / (counter * 1.0))
            };
        }
    }

    // Iterate through rows from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Iterate through cols from left to right
        for (int j = 0; j < width; j++)
        {
            // Replace original pixels with blurred pixels
            image[i][j] = temp[i][j];
        }
    }

    // Free the memory of temporary image array
    free(temp);
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create a new blank array to store processed pixels temporarily
    RGBTRIPLE(*temp)[width] = calloc(height, width * sizeof(RGBTRIPLE));

    // Iterate through rows from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Iterate through cols from left to right
        for (int j = 0; j < width; j++)
        {
            float redx, redy, greenx, greeny, bluex, bluey;
            redx = redy = greenx = greeny = bluex = bluey = 0;

            // If left pixel exists
            if (i >= 0 && j - 1 >= 0)
            {
                redx += image[i][j - 1].rgbtRed * -2;
                greenx += image[i][j - 1].rgbtGreen * -2;
                bluex += image[i][j - 1].rgbtBlue * -2;
            }
            // If right pixel exists
            if (i >= 0 && j + 1 >= 0 && j + 1 < width)
            {
                redx += image[i][j + 1].rgbtRed * 2;
                greenx += image[i][j + 1].rgbtGreen * 2;
                bluex += image[i][j + 1].rgbtBlue * 2;
            }
            // If top center pixel exists
            if (i - 1 >= 0 && j >= 0)
            {
                redy += image[i - 1][j].rgbtRed * -2;
                greeny += image[i - 1][j].rgbtGreen * -2;
                bluey += image[i - 1][j].rgbtBlue * -2;
            }
            // If top left pixel exists
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                redx += image[i - 1][j - 1].rgbtRed * -1;
                greenx += image[i - 1][j - 1].rgbtGreen * -1;
                bluex += image[i - 1][j - 1].rgbtBlue * -1;
                redy += image[i - 1][j - 1].rgbtRed * -1;
                greeny += image[i - 1][j - 1].rgbtGreen * -1;
                bluey += image[i - 1][j - 1].rgbtBlue * -1;
            }
            // If top right pixel exists
            if (i - 1 >= 0 && j + 1 >= 0 && j + 1 < width)
            {
                redx += image[i - 1][j + 1].rgbtRed;
                greenx += image[i - 1][j + 1].rgbtGreen;
                bluex += image[i - 1][j + 1].rgbtBlue;
                redy += image[i - 1][j + 1].rgbtRed * -1;
                greeny += image[i - 1][j + 1].rgbtGreen * -1;
                bluey += image[i - 1][j + 1].rgbtBlue * -1;
            }
            // If bottom center pixel exists
            if (i + 1 >= 0 && i + 1 < height && j >= 0)
            {
                redy += image[i + 1][j].rgbtRed * 2;
                greeny += image[i + 1][j].rgbtGreen * 2;
                bluey += image[i + 1][j].rgbtBlue * 2;
            }
            // If bottom left pixel exists
            if (i + 1 >= 0 && i + 1 < height && j - 1 >= 0)
            {
                redx += image[i + 1][j - 1].rgbtRed * -1;
                greenx += image[i + 1][j - 1].rgbtGreen * -1;
                bluex += image[i + 1][j - 1].rgbtBlue * -1;
                redy += image[i + 1][j - 1].rgbtRed;
                greeny += image[i + 1][j - 1].rgbtGreen;
                bluey += image[i + 1][j - 1].rgbtBlue;
            }
            // If bottom right pixel exists
            if (i + 1 >= 0 && i + 1 < height && j + 1 >= 0 && j + 1 < width)
            {
                redx += image[i + 1][j + 1].rgbtRed;
                greenx += image[i + 1][j + 1].rgbtGreen;
                bluex += image[i + 1][j + 1].rgbtBlue;
                redy += image[i + 1][j + 1].rgbtRed;
                greeny += image[i + 1][j + 1].rgbtGreen;
                bluey += image[i + 1][j + 1].rgbtBlue;
            }

            // Store the processed pixels into temp array
            temp[i][j] = (RGBTRIPLE)
            {
                .rgbtRed = min(round(sqrt(pow(redx, 2) + pow(redy, 2))), 255),
                .rgbtGreen = min(round(sqrt(pow(greenx, 2) + pow(greeny, 2))), 255),
                .rgbtBlue = min(round(sqrt(pow(bluex, 2) + pow(bluey, 2))), 255)
            };
        }
    }

    // Iterate through rows from top to bottom
    for (int i = 0; i < height; i++)
    {
        // Iterate through cols from left to right
        for (int j = 0; j < width; j++)
        {
            // Replace original pixels with blurred pixels
            image[i][j] = temp[i][j];
        }
    }

    // Free the memory of temporary image array
    free(temp);
}
