#include "helpers.h"
#include<math.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            BYTE red = image[i][j].rgbtRed;
            BYTE green = image[i][j].rgbtGreen;
            BYTE blue = image[i][j].rgbtBlue;
            BYTE avg = round((red + green + blue) / 3);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int add_counter = width - 1;

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            if(add_counter > 0)
            {
            BYTE previmagered = image[i][j + add_counter].rgbtRed;
            BYTE previmagegreen = image[i][j + add_counter].rgbtGreen;
            BYTE previmageblue = image[i][j + add_counter].rgbtBlue;

            image[i][j + add_counter].rgbtRed = image[i][j].rgbtRed;
            image[i][j + add_counter].rgbtGreen = image[i][j].rgbtGreen;
            image[i][j + add_counter].rgbtBlue = image[i][j].rgbtBlue;

            image[i][j].rgbtRed = previmagered;
            image[i][j].rgbtGreen = previmagegreen;
            image[i][j].rgbtBlue = previmageblue;

            add_counter -= 2;
            }
            else
            {
                return;
            }
        }

        add_counter = width -1;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}