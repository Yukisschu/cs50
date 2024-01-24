#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avr = 0;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            avr = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = avr;
            image[i][j].rgbtGreen = avr;
            image[i][j].rgbtBlue = avr;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int tmp = 0;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (width / 2); j++)
        {
            tmp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][width - j - 1].rgbtRed = tmp;

            tmp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;
            image[i][width - j - 1].rgbtGreen = tmp;

            tmp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][width - j - 1].rgbtBlue = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum_rgbtRed = 0;
            int sum_rgbtGreen = 0;
            int sum_rgbtBlue = 0;
            float count = 0.0;

            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (m < height && n < width && m >= 0 && n >= 0)
                    {
                        sum_rgbtRed += copy[m][n].rgbtRed;
                        sum_rgbtGreen += copy[m][n].rgbtGreen;
                        sum_rgbtBlue += copy[m][n].rgbtBlue;
                        count++;
                    }
                }
            }
            int avg_rgbtRed = round(sum_rgbtRed / count);
            int avg_rgbtGreen = round(sum_rgbtGreen / count);
            int avg_rgbtBlue = round(sum_rgbtBlue / count);

            image[i][j].rgbtRed = avg_rgbtRed;
            image[i][j].rgbtGreen = avg_rgbtGreen;
            image[i][j].rgbtBlue = avg_rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    int Gx[9] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[9] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int Gxsum_rgbtRed = 0;
            int Gxsum_rgbtGreen = 0;
            int Gxsum_rgbtBlue = 0;
            int Gysum_rgbtRed = 0;
            int Gysum_rgbtGreen = 0;
            int Gysum_rgbtBlue = 0;
            int g = 0;

            for (int m = i - 1; m < i + 2; m++)
            {
                for (int n = j - 1; n < j + 2; n++)
                {
                    if (m < height && n < width && m >= 0 && n >= 0)
                    {

                        Gxsum_rgbtRed += copy[m][n].rgbtRed * Gx[g];
                        Gxsum_rgbtGreen += copy[m][n].rgbtGreen * Gx[g];
                        Gxsum_rgbtBlue += copy[m][n].rgbtBlue * Gx[g];

                        Gysum_rgbtRed += copy[m][n].rgbtRed * Gy[g];
                        Gysum_rgbtGreen += copy[m][n].rgbtGreen * Gy[g];
                        Gysum_rgbtBlue += copy[m][n].rgbtBlue * Gy[g];
                    }
                    g++;
                }
            }
            int avg_rgbtRed = round(fmin(sqrt(pow(Gxsum_rgbtRed, 2) + pow(Gysum_rgbtRed, 2)), 255));
            int avg_rgbtGreen = round(fmin(sqrt(pow(Gxsum_rgbtGreen, 2) + pow(Gysum_rgbtGreen, 2)), 255));
            int avg_rgbtBlue = round(fmin(sqrt(pow(Gxsum_rgbtBlue, 2) + pow(Gysum_rgbtBlue, 2)), 255));

            image[i][j].rgbtRed = avg_rgbtRed;
            image[i][j].rgbtGreen = avg_rgbtGreen;
            image[i][j].rgbtBlue = avg_rgbtBlue;
        }
    }
    return;
}
