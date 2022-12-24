#include "helpers.h"
#include <math.h>
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
            RGBTRIPLE prev_image = image[i][j + add_counter];
            image[i][j + add_counter] = image[i][j];
            image[i][j] = prev_image;
            add_counter -= 2;
            }
            else
            {
                break;
            }
        }
        add_counter = width - 1;
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0, red, green, blue, counter; j < width; j++)
        {
            red = 0, green = 0, blue = 0, counter = 0;

            // Check previous, current, next image
            for(int h = -1; h < 2; h++)
            {
                for(int w = -1; w < 2; w++)
                {
                    if((j + w == -1 || j + w == width) || (i + h == -1 || i + w == height))
                    {
                        continue;
                    }

                    red += image[i + h][j + w].rgbtRed;
                    green += image[i + h][j + w].rgbtGreen;
                    blue += image[i + h][j + w].rgbtBlue;
                    counter++;
                }
            }

            temp[i][j].rgbtRed = round(red / counter);
            temp[i][j].rgbtGreen = round(green / counter);
            temp[i][j].rgbtBlue = round(blue / counter);
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
     RGBTRIPLE temp[height][width];
     int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
     int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0, redGx, redGy, greenGx, greenGy, blueGx, blueGy; j < width; j++)
        {
            redGx = 0, redGy = 0, greenGx = 0, greenGy = 0, blueGx = 0, blueGy = 0;

            for(int h = -1; h < 2; h++)
            {
                for(int w = -1; w < 2; w++)
                {
                    if((j + w == -1 || j + w == width) || (i + h == -1 || i + w == height))
                    {
                        continue;
                    }
                    redGx += image[i + h][j + w].rgbtRed * Gx[h + 1][j + 1];
                    redGy += image[i + h][j + w].rgbtRed * Gy[h + 1][j + 1];
                    greenGx += image[i + h][j + w].rgbtGreen * Gx[h + 1][j + 1];
                    greenGy += image[i + h][j + w].rgbtGreen * Gy[h + 1][j + 1];
                    blueGx += image[i + h][j + w].rgbtBlue * Gx[h + 1][j + 1];
                    blueGy += image[i + h][j + w].rgbtBlue * Gy[h + 1][j + 1];
                }
            }

            int red = round(sqrt((redGx * redGx) + (redGy * redGy)));
            int green = round(sqrt((greenGx * greenGx) + (greenGy * greenGy)));
            int blue = round(sqrt((blueGx * blueGx) + (blueGy * blueGy)));

            if(red > 255)
            {
                red = 255;
            }
            if(green > 255)
            {
                green = 255;
            }
            if(blue > 255)
            {
                blue = 255;
            }

            temp[i][j].rgbtRed = red;
            temp[i][j].rgbtGreen = green;
            temp[i][j].rgbtBlue = blue;

        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            image[i][j] = temp[i][j];
        }
    }
    return;
}