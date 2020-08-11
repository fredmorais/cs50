#include "helpers.h"
#include <math.h>

int higher(int number);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //Iterate each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Get the average of the R, G and B values
            int newColor = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / (3 * 1.0));

            //Apply the average value to R, G and B
            image[i][j].rgbtRed = newColor;
            image[i][j].rgbtGreen = newColor;
            image[i][j].rgbtBlue = newColor;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    //Temporary array for the left half of the pixels
    RGBTRIPLE tempPixels[height][width];

    //Save a copy of the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tempPixels[i][j].rgbtRed = image[i][j].rgbtRed;
            tempPixels[i][j].rgbtGreen = image[i][j].rgbtGreen;
            tempPixels[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //Reflect the image
    for (int i = 0; i < height; i++)
    {
        for (int j = (width-1); j >= 0; j--)
        {
            image[i][width - j - 1].rgbtRed = tempPixels[i][j].rgbtRed;
            image[i][width - j - 1].rgbtGreen = tempPixels[i][j].rgbtGreen;
            image[i][width - j - 1].rgbtBlue = tempPixels[i][j].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy the image
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j].rgbtRed = image[i][j].rgbtRed;
            imageCopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageCopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //Iterate each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Arrays for pixels around the current pixel
            int tempR[3][3];
            int tempG[3][3];
            int tempB[3][3];

            //Get the RGB values for the pixels around the current pixel
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    if ((i + y >= 0 && i + y < height) && (j + x >= 0 && j + x < width))
                    {
                        tempR[y+1][x+1] = imageCopy[i+y][j+x].rgbtRed;
                        tempG[y+1][x+1] = imageCopy[i+y][j+x].rgbtGreen;
                        tempB[y+1][x+1] = imageCopy[i+y][j+x].rgbtBlue;
                    }
                    else
                    {
                        tempR[y+1][x+1] = -1;
                        tempG[y+1][x+1] = -1;
                        tempB[y+1][x+1] = -1;
                    }
                }
            }

            int averageR = 0;
            int averageG = 0;
            int averageB = 0;
            int numPixels = 0;

            //Get the average of the RGB values
            for (int n = 0; n < 3; n++)
            {
                for (int m = 0; m < 3; m++)
                {
                    if (!(tempR[n][m] == -1))
                    {
                        averageR += tempR[n][m];
                        averageG += tempG[n][m];
                        averageB += tempB[n][m];
                        numPixels++;
                    }
                }
            }

            //Update the current pixel
            image[i][j].rgbtRed = round(averageR / (numPixels * 1.0));
            image[i][j].rgbtGreen = round(averageG / (numPixels * 1.0));
            image[i][j].rgbtBlue = round(averageB / (numPixels * 1.0));
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy the image
    RGBTRIPLE imageCopy[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imageCopy[i][j].rgbtRed = image[i][j].rgbtRed;
            imageCopy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imageCopy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //Iterate each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Arrays for pixels around the current pixel
            int tempR[3][3];
            int tempG[3][3];
            int tempB[3][3];

            //Get the RGB values for the pixels around the current pixel
            for (int y = -1; y < 2; y++)
            {
                for (int x = -1; x < 2; x++)
                {
                    if ((i + y >= 0 && i + y <= height - 1) && (j + x >= 0 && j + x <= width - 1))
                    {
                        tempR[y+1][x+1] = imageCopy[i+y][j+x].rgbtRed;
                        tempG[y+1][x+1] = imageCopy[i+y][j+x].rgbtGreen;
                        tempB[y+1][x+1] = imageCopy[i+y][j+x].rgbtBlue;
                    }
                    else
                    {
                        tempR[y+1][x+1] = 0;
                        tempG[y+1][x+1] = 0;
                        tempB[y+1][x+1] = 0;
                    }
                }
            }

            //Calculate the Gx and Gy using the kernels
            int GxR = (-1)*tempR[0][0] + tempR[0][2] + (-2)*tempR[1][0] + 2*tempR[1][2] + (-1)*tempR[2][0] + tempR[2][2];
            int GxG = (-1)*tempG[0][0] + tempG[0][2] + (-2)*tempG[1][0] + 2*tempG[1][2] + (-1)*tempG[2][0] + tempG[2][2];
            int GxB = (-1)*tempB[0][0] + tempB[0][2] + (-2)*tempB[1][0] + 2*tempB[1][2] + (-1)*tempB[2][0] + tempB[2][2];

            int GyR = (-1)*tempR[0][0] + (-2)*tempR[0][1] + (-1)*tempR[0][2] + tempR[2][0] + 2*tempR[2][1] + tempR[2][2];
            int GyG = (-1)*tempG[0][0] + (-2)*tempG[0][1] + (-1)*tempG[0][2] + tempG[2][0] + 2*tempG[2][1] + tempG[2][2];
            int GyB = (-1)*tempB[0][0] + (-2)*tempB[0][1] + (-1)*tempB[0][2] + tempB[2][0] + 2*tempB[2][1] + tempB[2][2];

            //Update the current pixel
            image[i][j].rgbtRed = higher(round(sqrt(pow(GxR,2) + pow(GyR,2))));
            image[i][j].rgbtGreen = higher(round(sqrt(pow(GxG,2) + pow(GyG,2))));
            image[i][j].rgbtBlue = higher(round(sqrt(pow(GxB,2) + pow(GyB,2))));
        }
    }
    return;
}

int higher(int number)
{
    if (number > 255)
    {
        return 255;
    }
    return number;
}