#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            double grey = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue);
            double grey2 = grey / 3;
            int new_value = round(grey2);
            image[i][j].rgbtRed = new_value;
            image[i][j].rgbtGreen = new_value;
            image[i][j].rgbtBlue = new_value;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int rgbtRed;
        int rgbtGreen;
        int rgbtBlue;

    } copy;

    copy copys[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copys[i][j].rgbtRed = image[i][j].rgbtRed;
            copys[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copys[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = copys[i][(width - 1) - j].rgbtRed;
            image[i][j].rgbtGreen = copys[i][(width - 1) - j].rgbtGreen;
            image[i][j].rgbtBlue = copys[i][(width - 1) - j].rgbtBlue;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int rgbtRed;
        int rgbtGreen;
        int rgbtBlue;

    } copy;

    copy copys[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copys[i][j].rgbtRed = image[i][j].rgbtRed;
            copys[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copys[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                if (i == 0 && j == 0) // top left courner
                {
                    double rgbtRed = copys[i][j].rgbtRed +
                                     copys[i + 1][j].rgbtRed +
                                     copys[i][j + 1].rgbtRed +
                                     copys[i + 1][j + 1].rgbtRed;
                    double rgbtGreen = copys[i][j].rgbtGreen +
                                       copys[i + 1][j].rgbtGreen +
                                       copys[i][j + 1].rgbtGreen +
                                       copys[i + 1][j + 1].rgbtGreen;
                    double rgbtBlue = copys[i][j].rgbtBlue +
                                      copys[i + 1][j].rgbtBlue +
                                      copys[i][j + 1].rgbtBlue +
                                      copys[i + 1][j + 1].rgbtBlue;
                    double rgbtRed2 = rgbtRed / 4;
                    image[i][j].rgbtRed = round(rgbtRed2);
                    double rgbtGreen2 = rgbtGreen / 4;
                    image[i][j].rgbtGreen = round(rgbtGreen2);
                    double rgbtBlue2 = rgbtBlue / 4;
                    image[i][j].rgbtBlue = round(rgbtBlue2);
                }
                else if (i == height - 1 && j == width - 1) // bottom right courner
                {
                    double rgbtRed = copys[i][j].rgbtRed +
                                     copys[i - 1][j].rgbtRed +
                                     copys[i][j - 1].rgbtRed +
                                     copys[i - 1][j - 1].rgbtRed;
                    double rgbtGreen = copys[i][j].rgbtGreen +
                                       copys[i - 1][j].rgbtGreen +
                                       copys[i][j - 1].rgbtGreen +
                                       copys[i - 1][j - 1].rgbtGreen;
                    double rgbtBlue = copys[i][j].rgbtBlue +
                                      copys[i - 1][j].rgbtBlue +
                                      copys[i][j - 1].rgbtBlue +
                                      copys[i - 1][j - 1].rgbtBlue;
                    double rgbtRed2 = rgbtRed / 4;
                    image[i][j].rgbtRed = round(rgbtRed2);
                    double rgbtGreen2 = rgbtGreen / 4;
                    image[i][j].rgbtGreen = round(rgbtGreen2);
                    double rgbtBlue2 = rgbtBlue / 4;
                    image[i][j].rgbtBlue = round(rgbtBlue2);
                }
                else if (i == 0 && j == width - 1) // top right courner
                {
                    double rgbtRed = copys[i][j].rgbtRed +
                                     copys[i + 1][j].rgbtRed +
                                     copys[i][j - 1].rgbtRed +
                                     copys[i + 1][j - 1].rgbtRed;
                    double rgbtGreen = copys[i][j].rgbtGreen +
                                       copys[i + 1][j].rgbtGreen +
                                       copys[i][j - 1].rgbtGreen +
                                       copys[i + 1][j - 1].rgbtGreen;
                    double rgbtBlue = copys[i][j].rgbtBlue +
                                      copys[i + 1][j].rgbtBlue +
                                      copys[i][j - 1].rgbtBlue +
                                      copys[i + 1][j - 1].rgbtBlue;
                    double rgbtRed2 = rgbtRed / 4;
                    image[i][j].rgbtRed = round(rgbtRed2);
                    double rgbtGreen2 = rgbtGreen / 4;
                    image[i][j].rgbtGreen = round(rgbtGreen2);
                    double rgbtBlue2 = rgbtBlue / 4;
                    image[i][j].rgbtBlue = round(rgbtBlue2);
                }
                else if (i == height - 1 && j == 0) // bottom left courner
                {
                    double rgbtRed = copys[i][j].rgbtRed +
                                     copys[i - 1][j].rgbtRed +
                                     copys[i][j + 1].rgbtRed +
                                     copys[i - 1][j + 1].rgbtRed;
                    double rgbtGreen = copys[i][j].rgbtGreen +
                                       copys[i - 1][j].rgbtGreen +
                                       copys[i][j + 1].rgbtGreen +
                                       copys[i - 1][j + 1].rgbtGreen;
                    double rgbtBlue = copys[i][j].rgbtBlue +
                                      copys[i - 1][j].rgbtBlue +
                                      copys[i][j + 1].rgbtBlue +
                                      copys[i - 1][j + 1].rgbtBlue;
                    double rgbtRed2 = rgbtRed / 4;
                    image[i][j].rgbtRed = round(rgbtRed2);
                    double rgbtGreen2 = rgbtGreen / 4;
                    image[i][j].rgbtGreen = round(rgbtGreen2);
                    double rgbtBlue2 = rgbtBlue / 4;
                    image[i][j].rgbtBlue = round(rgbtBlue2);
                }
                else if (i == 0 && 0 < j < width - 1) // top edge
                {
                    double rgbtRed = copys[i][j].rgbtRed +
                                     copys[i][j - 1].rgbtRed +
                                     copys[i][j + 1].rgbtRed +
                                     copys[i + 1][j].rgbtRed +
                                     copys[i + 1][j + 1].rgbtRed +
                                     copys[i + 1][j - 1].rgbtRed;
                    double rgbtGreen = copys[i][j].rgbtGreen +
                                       copys[i][j - 1].rgbtGreen +
                                       copys[i][j + 1].rgbtGreen +
                                       copys[i + 1][j].rgbtGreen +
                                       copys[i + 1][j + 1].rgbtGreen +
                                       copys[i + 1][j - 1].rgbtGreen;
                    double rgbtBlue = copys[i][j].rgbtBlue +
                                      copys[i][j - 1].rgbtBlue +
                                      copys[i][j + 1].rgbtBlue +
                                      copys[i + 1][j].rgbtBlue +
                                      copys[i + 1][j + 1].rgbtBlue +
                                      copys[i + 1][j - 1].rgbtBlue;
                    double rgbtRed2 = rgbtRed / 6;
                    image[i][j].rgbtRed = round(rgbtRed2);
                    double rgbtGreen2 = rgbtGreen / 6;
                    image[i][j].rgbtGreen = round(rgbtGreen2);
                    double rgbtBlue2 = rgbtBlue / 6;
                    image[i][j].rgbtBlue = round(rgbtBlue2);
                }
                else if (j == 0 && 0 < i < height - 1) // left edge
                {
                    double rgbtRed = copys[i][j].rgbtRed +
                                     copys[i - 1][j].rgbtRed +
                                     copys[i - 1][j + 1].rgbtRed +
                                     copys[i][j + 1].rgbtRed +
                                     copys[i + 1][j].rgbtRed +
                                     copys[i + 1][j + 1].rgbtRed;
                    double rgbtGreen = copys[i][j].rgbtGreen +
                                       copys[i - 1][j].rgbtGreen +
                                       copys[i - 1][j + 1].rgbtGreen +
                                       copys[i][j + 1].rgbtGreen +
                                       copys[i + 1][j].rgbtGreen +
                                       copys[i + 1][j + 1].rgbtGreen;
                    double rgbtBlue = copys[i][j].rgbtBlue +
                                      copys[i - 1][j].rgbtBlue +
                                      copys[i - 1][j + 1].rgbtBlue +
                                      copys[i][j + 1].rgbtBlue +
                                      copys[i + 1][j].rgbtBlue +
                                      copys[i + 1][j + 1].rgbtBlue;
                    double rgbtRed2 = rgbtRed / 6;
                    image[i][j].rgbtRed = round(rgbtRed2);
                    double rgbtGreen2 = rgbtGreen / 6;
                    image[i][j].rgbtGreen = round(rgbtGreen2);
                    double rgbtBlue2 = rgbtBlue / 6;
                    image[i][j].rgbtBlue = round(rgbtBlue2);
                }
                else if (i == height - 1 && 0 < j < width - 1) // bottom edge
                {
                    double rgbtRed = copys[i][j].rgbtRed +
                                     copys[i][j - 1].rgbtRed +
                                     copys[i - 1][j - 1].rgbtRed +
                                     copys[i - 1][j].rgbtRed +
                                     copys[i - 1][j + 1].rgbtRed +
                                     copys[i][j + 1].rgbtRed;
                    double rgbtGreen = copys[i][j].rgbtGreen +
                                       copys[i][j - 1].rgbtGreen +
                                       copys[i - 1][j - 1].rgbtGreen +
                                       copys[i - 1][j].rgbtGreen +
                                       copys[i - 1][j + 1].rgbtGreen +
                                       copys[i][j + 1].rgbtGreen;
                    double rgbtBlue = copys[i][j].rgbtBlue +
                                      copys[i][j - 1].rgbtBlue +
                                      copys[i - 1][j - 1].rgbtBlue +
                                      copys[i - 1][j].rgbtBlue +
                                      copys[i - 1][j + 1].rgbtBlue +
                                      copys[i][j + 1].rgbtBlue;
                    double rgbtRed2 = rgbtRed / 6;
                    image[i][j].rgbtRed = round(rgbtRed2);
                    double rgbtGreen2 = rgbtGreen / 6;
                    image[i][j].rgbtGreen = round(rgbtGreen2);
                    double rgbtBlue2 = rgbtBlue / 6;
                    image[i][j].rgbtBlue = round(rgbtBlue2);
                }
                else if (j == width - 1 && 0 < i < height - 1) // right edge
                {
                    double rgbtRed = copys[i][j].rgbtRed +
                                     copys[i - 1][j].rgbtRed +
                                     copys[i - 1][j - 1].rgbtRed +
                                     copys[i][j - 1].rgbtRed +
                                     copys[i + 1][j - 1].rgbtRed +
                                     copys[i + 1][j].rgbtRed;
                    double rgbtGreen = copys[i][j].rgbtGreen +
                                       copys[i - 1][j].rgbtGreen +
                                       copys[i - 1][j - 1].rgbtGreen +
                                       copys[i][j - 1].rgbtGreen +
                                       copys[i + 1][j - 1].rgbtGreen +
                                       copys[i + 1][j].rgbtGreen;
                    double rgbtBlue = copys[i][j].rgbtBlue +
                                      copys[i - 1][j].rgbtBlue +
                                      copys[i - 1][j - 1].rgbtBlue +
                                      copys[i][j - 1].rgbtBlue +
                                      copys[i + 1][j - 1].rgbtBlue +
                                      copys[i + 1][j].rgbtBlue;

                    double rgbtRed2 = rgbtRed / 6;
                    image[i][j].rgbtRed = round(rgbtRed2);
                    double rgbtGreen2 = rgbtGreen / 6;
                    image[i][j].rgbtGreen = round(rgbtGreen2);
                    double rgbtBlue2 = rgbtBlue / 6;
                    image[i][j].rgbtBlue = round(rgbtBlue2);
                }
            }
            else
            {
                double rgbtRed = (copys[i][j].rgbtRed +
                                  copys[i][j - 1].rgbtRed +
                                  copys[i][j + 1].rgbtRed +
                                  copys[i + 1][j].rgbtRed +
                                  copys[i + 1][j - 1].rgbtRed +
                                  copys[i + 1][j + 1].rgbtRed +
                                  copys[i - 1][j].rgbtRed +
                                  copys[i - 1][j - 1].rgbtRed +
                                  copys[i - 1][j + 1].rgbtRed);
                double rgbtRed2 = rgbtRed / 9;
                image[i][j].rgbtRed = round(rgbtRed2);

                double rgbtGreen = (copys[i][j].rgbtGreen +
                                    copys[i][j - 1].rgbtGreen +
                                    copys[i][j + 1].rgbtGreen +
                                    copys[i + 1][j].rgbtGreen +
                                    copys[i + 1][j - 1].rgbtGreen +
                                    copys[i + 1][j + 1].rgbtGreen +
                                    copys[i - 1][j].rgbtGreen +
                                    copys[i - 1][j - 1].rgbtGreen +
                                    copys[i - 1][j + 1].rgbtGreen);
                double rgbtGreen2 = rgbtGreen / 9;
                image[i][j].rgbtGreen = round(rgbtGreen2);

                double rgbtBlue = (copys[i][j].rgbtBlue +
                                   copys[i][j - 1].rgbtBlue +
                                   copys[i][j + 1].rgbtBlue +
                                   copys[i + 1][j].rgbtBlue +
                                   copys[i + 1][j - 1].rgbtBlue +
                                   copys[i + 1][j + 1].rgbtBlue +
                                   copys[i - 1][j].rgbtBlue +
                                   copys[i - 1][j - 1].rgbtBlue +
                                   copys[i - 1][j + 1].rgbtBlue);

                double rgbtBlue2 = rgbtBlue / 9;
                image[i][j].rgbtBlue = round(rgbtBlue2);
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int rgbtRed;
        int rgbtGreen;
        int rgbtBlue;

    } copy;

    copy copys[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copys[i][j].rgbtRed = image[i][j].rgbtRed;
            copys[i][j].rgbtGreen = image[i][j].rgbtGreen;
            copys[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {

            if (i == 0 || i == height - 1 || j == 0 || j == width - 1)
            {
                double GxRed = 0;
                double GxGreen = 0;
                double GxBlue = 0;
                double GyRed = 0;
                double GyGreen = 0;
                double GyBlue = 0;
                if (i == 0 && j == 0) // top left courner
                {
                    GxRed = (0 * copys[i][j].rgbtRed) +
                            (0 * copys[i + 1][j].rgbtRed) +
                            (2 * copys[i][j + 1].rgbtRed) +
                            (1 * copys[i + 1][j + 1].rgbtRed);
                    GxGreen = (0 * copys[i][j].rgbtGreen) +
                              (0 * copys[i + 1][j].rgbtGreen) +
                              (2 * copys[i][j + 1].rgbtGreen) +
                              (1 * copys[i + 1][j + 1].rgbtGreen);
                    GxBlue = (0 * copys[i][j].rgbtBlue) +
                             (0 * copys[i + 1][j].rgbtBlue) +
                             (2 * copys[i][j + 1].rgbtBlue) +
                             (1 * copys[i + 1][j + 1].rgbtBlue);

                    GyRed = (0 * copys[i][j].rgbtRed) +
                            (2 * copys[i + 1][j].rgbtRed) +
                            (0 * copys[i][j + 1].rgbtRed) +
                            (1 * copys[i + 1][j + 1].rgbtRed);
                    GyGreen = (0 * copys[i][j].rgbtGreen) +
                              (2 * copys[i + 1][j].rgbtGreen) +
                              (0 * copys[i][j + 1].rgbtGreen) +
                              (1 * copys[i + 1][j + 1].rgbtGreen);
                    GyBlue = (0 * copys[i][j].rgbtBlue) +
                             (2 * copys[i + 1][j].rgbtBlue) +
                             (0 * copys[i][j + 1].rgbtBlue) +
                             (1 * copys[i + 1][j + 1].rgbtBlue);
                }
                else if (i == height - 1 && j == width - 1) // bottom right courner
                {
                    GxRed = (0 * copys[i][j].rgbtRed) +
                            (0 * copys[i - 1][j].rgbtRed) +
                            (-2 * copys[i][j - 1].rgbtRed) +
                            (-1 * copys[i - 1][j - 1].rgbtRed);
                    GxGreen = (0 * copys[i][j].rgbtGreen) +
                              (0 * copys[i - 1][j].rgbtGreen) +
                              (-2 * copys[i][j - 1].rgbtGreen) +
                              (-1 * copys[i - 1][j - 1].rgbtGreen);
                    GxBlue = (0 * copys[i][j].rgbtBlue) +
                             (0 * copys[i - 1][j].rgbtBlue) +
                             (-2 * copys[i][j - 1].rgbtBlue) +
                             (-1 * copys[i - 1][j - 1].rgbtBlue);

                    GyRed = (0 * copys[i][j].rgbtRed) +
                            (-2 * copys[i - 1][j].rgbtRed) +
                            (0 * copys[i][j - 1].rgbtRed) +
                            (-1 * copys[i - 1][j - 1].rgbtRed);
                    GyGreen = (0 * copys[i][j].rgbtGreen) +
                              (-2 * copys[i - 1][j].rgbtGreen) +
                              (0 * copys[i][j - 1].rgbtGreen) +
                              (-1 * copys[i - 1][j - 1].rgbtGreen);
                    GyBlue = (0 * copys[i][j].rgbtBlue) +
                             (-2 * copys[i - 1][j].rgbtBlue) +
                             (0 * copys[i][j - 1].rgbtBlue) +
                             (-1 * copys[i - 1][j - 1].rgbtBlue);
                }

                else if (i == 0 && j == width - 1) // top right courner
                {
                    GxRed = (0 * copys[i][j].rgbtRed) +
                            (0 * copys[i + 1][j].rgbtRed) +
                            (-2 * copys[i][j - 1].rgbtRed) +
                            (-1 * copys[i + 1][j - 1].rgbtRed);
                    GxGreen = (0 * copys[i][j].rgbtGreen) +
                              (0 * copys[i + 1][j].rgbtGreen) +
                              (-2 * copys[i][j - 1].rgbtGreen) +
                              (-1 * copys[i + 1][j - 1].rgbtGreen);
                    GxBlue = (0 * copys[i][j].rgbtBlue) +
                             (0 * copys[i + 1][j].rgbtBlue) +
                             (-2 * copys[i][j - 1].rgbtBlue) +
                             (-1 * copys[i + 1][j - 1].rgbtBlue);

                    GyRed = (0 * copys[i][j].rgbtRed) +
                            (2 * copys[i + 1][j].rgbtRed) +
                            (0 * copys[i][j - 1].rgbtRed) +
                            (1 * copys[i + 1][j - 1].rgbtRed);
                    GyGreen = (0 * copys[i][j].rgbtGreen) +
                              (2 * copys[i + 1][j].rgbtGreen) +
                              (0 * copys[i][j - 1].rgbtGreen) +
                              (1 * copys[i + 1][j - 1].rgbtGreen);
                    GyBlue = (0 * copys[i][j].rgbtBlue) +
                             (2 * copys[i + 1][j].rgbtBlue) +
                             (0 * copys[i][j - 1].rgbtBlue) +
                             (1 * copys[i + 1][j - 1].rgbtBlue);
                }

                else if (i == height - 1 && j == 0) // bottom left courner
                {
                    GxRed = (0 * copys[i][j].rgbtRed) +
                            (0 * copys[i - 1][j].rgbtRed) +
                            (2 * copys[i][j + 1].rgbtRed) +
                            (1 * copys[i - 1][j + 1].rgbtRed);
                    GxGreen = (0 * copys[i][j].rgbtGreen) +
                              (0 * copys[i - 1][j].rgbtGreen) +
                              (2 * copys[i][j + 1].rgbtGreen) +
                              (1 * copys[i - 1][j + 1].rgbtGreen);
                    GxBlue = (0 * copys[i][j].rgbtBlue) +
                             (0 * copys[i - 1][j].rgbtBlue) +
                             (2 * copys[i][j + 1].rgbtBlue) +
                             (1 * copys[i - 1][j + 1].rgbtBlue);

                    GyRed = (0 * copys[i][j].rgbtRed) +
                            (-2 * copys[i - 1][j].rgbtRed) +
                            (0 * copys[i][j + 1].rgbtRed) +
                            (-1 * copys[i - 1][j + 1].rgbtRed);
                    GyGreen = (0 * copys[i][j].rgbtGreen) +
                              (-2 * copys[i - 1][j].rgbtGreen) +
                              (0 * copys[i][j + 1].rgbtGreen) +
                              (-1 * copys[i - 1][j + 1].rgbtGreen);
                    GyBlue = (0 * copys[i][j].rgbtBlue) +
                             (-2 * copys[i - 1][j].rgbtBlue) +
                             (0 * copys[i][j + 1].rgbtBlue) +
                             (-1 * copys[i - 1][j + 1].rgbtBlue);
                }

                else if (i == 0 && 0 < j < width - 1) // top edge
                {
                    GxRed = (0 * copys[i][j].rgbtRed) +
                            (0 * copys[i + 1][j].rgbtRed) +
                            (2 * copys[i][j + 1].rgbtRed) +
                            (1 * copys[i + 1][j + 1].rgbtRed) +
                            (-2 * copys[i][j - 1].rgbtRed) +
                            (-1 * copys[i + 1][j - 1].rgbtRed);
                    GxGreen = (0 * copys[i][j].rgbtGreen) +
                              (0 * copys[i + 1][j].rgbtGreen) +
                              (2 * copys[i][j + 1].rgbtGreen) +
                              (1 * copys[i + 1][j + 1].rgbtGreen) +
                              (-2 * copys[i][j - 1].rgbtGreen) +
                              (-1 * copys[i + 1][j - 1].rgbtGreen);
                    GxBlue = (0 * copys[i][j].rgbtBlue) +
                             (0 * copys[i + 1][j].rgbtBlue) +
                             (2 * copys[i][j + 1].rgbtBlue) +
                             (1 * copys[i + 1][j + 1].rgbtBlue) +
                             (-2 * copys[i][j - 1].rgbtBlue) +
                             (-1 * copys[i + 1][j - 1].rgbtBlue);

                    GyRed = (0 * copys[i][j].rgbtRed) +
                            (2 * copys[i + 1][j].rgbtRed) +
                            (0 * copys[i][j + 1].rgbtRed) +
                            (1 * copys[i + 1][j + 1].rgbtRed) +
                            (0 * copys[i][j - 1].rgbtRed) +
                            (1 * copys[i + 1][j - 1].rgbtRed);
                    GyGreen = (0 * copys[i][j].rgbtGreen) +
                              (2 * copys[i + 1][j].rgbtGreen) +
                              (0 * copys[i][j + 1].rgbtGreen) +
                              (1 * copys[i + 1][j + 1].rgbtGreen) +
                              (0 * copys[i][j - 1].rgbtGreen) +
                              (1 * copys[i + 1][j - 1].rgbtGreen);
                    GyBlue = (0 * copys[i][j].rgbtBlue) +
                             (2 * copys[i + 1][j].rgbtBlue) +
                             (0 * copys[i][j + 1].rgbtBlue) +
                             (1 * copys[i + 1][j + 1].rgbtBlue) +
                             (0 * copys[i][j - 1].rgbtBlue) +
                             (1 * copys[i + 1][j - 1].rgbtBlue);
                }

                else if (j == 0 && 0 < i < height - 1) // left edge
                {
                    GxRed = (0 * copys[i][j].rgbtRed) +
                            (0 * copys[i - 1][j].rgbtRed) +
                            (2 * copys[i][j + 1].rgbtRed) +
                            (1 * copys[i + 1][j + 1].rgbtRed) +
                            (1 * copys[i - 1][j + 1].rgbtRed) +
                            (0 * copys[i + 1][j].rgbtRed);
                    GxGreen = (0 * copys[i][j].rgbtGreen) +
                              (0 * copys[i - 1][j].rgbtGreen) +
                              (2 * copys[i][j + 1].rgbtGreen) +
                              (1 * copys[i + 1][j + 1].rgbtGreen) +
                              (1 * copys[i - 1][j + 1].rgbtGreen) +
                              (0 * copys[i + 1][j].rgbtGreen);
                    GxBlue = (0 * copys[i][j].rgbtBlue) +
                             (0 * copys[i - 1][j].rgbtBlue) +
                             (2 * copys[i][j + 1].rgbtBlue) +
                             (1 * copys[i + 1][j + 1].rgbtBlue) +
                             (1 * copys[i - 1][j + 1].rgbtBlue) +
                             (0 * copys[i + 1][j].rgbtBlue);

                    GyRed = (0 * copys[i][j].rgbtRed) +
                            (-2 * copys[i - 1][j].rgbtRed) +
                            (0 * copys[i][j + 1].rgbtRed) +
                            (1 * copys[i + 1][j + 1].rgbtRed) +
                            (-1 * copys[i - 1][j + 1].rgbtRed) +
                            (2 * copys[i + 1][j].rgbtRed);
                    GyGreen = (0 * copys[i][j].rgbtGreen) +
                              (-2 * copys[i - 1][j].rgbtGreen) +
                              (0 * copys[i][j + 1].rgbtGreen) +
                              (1 * copys[i + 1][j + 1].rgbtGreen) +
                              (-1 * copys[i - 1][j + 1].rgbtGreen) +
                              (2 * copys[i + 1][j].rgbtGreen);
                    GyBlue = (0 * copys[i][j].rgbtBlue) +
                             (-2 * copys[i - 1][j].rgbtBlue) +
                             (0 * copys[i][j + 1].rgbtBlue) +
                             (1 * copys[i + 1][j + 1].rgbtBlue) +
                             (-1 * copys[i - 1][j + 1].rgbtBlue) +
                             (2 * copys[i + 1][j].rgbtBlue);
                }
                else if (i == height - 1 && 0 < j < width - 1) // bottom edge
                {
                    GxRed = (0 * copys[i][j].rgbtRed) +
                            (0 * copys[i - 1][j].rgbtRed) +
                            (2 * copys[i][j + 1].rgbtRed) +
                            (1 * copys[i - 1][j + 1].rgbtRed) +
                            (-2 * copys[i][j - 1].rgbtRed) +
                            (-1 * copys[i - 1][j - 1].rgbtRed);
                    GxGreen = (0 * copys[i][j].rgbtGreen) +
                              (0 * copys[i - 1][j].rgbtGreen) +
                              (2 * copys[i][j + 1].rgbtGreen) +
                              (1 * copys[i - 1][j + 1].rgbtGreen) +
                              (-2 * copys[i][j - 1].rgbtGreen) +
                              (-1 * copys[i - 1][j - 1].rgbtGreen);
                    GxBlue = (0 * copys[i][j].rgbtBlue) +
                             (0 * copys[i - 1][j].rgbtBlue) +
                             (2 * copys[i][j + 1].rgbtBlue) +
                             (1 * copys[i - 1][j + 1].rgbtBlue) +
                             (-2 * copys[i][j - 1].rgbtBlue) +
                             (-1 * copys[i - 1][j - 1].rgbtBlue);

                    GyRed = (0 * copys[i][j].rgbtRed) +
                            (-2 * copys[i - 1][j].rgbtRed) +
                            (0 * copys[i][j + 1].rgbtRed) +
                            (-1 * copys[i - 1][j + 1].rgbtRed) +
                            (0 * copys[i][j - 1].rgbtRed) +
                            (-1 * copys[i - 1][j - 1].rgbtRed);
                    GyGreen = (0 * copys[i][j].rgbtGreen) +
                              (-2 * copys[i - 1][j].rgbtGreen) +
                              (0 * copys[i][j + 1].rgbtGreen) +
                              (-1 * copys[i - 1][j + 1].rgbtGreen) +
                              (0 * copys[i][j - 1].rgbtGreen) +
                              (-1 * copys[i - 1][j - 1].rgbtGreen);
                    GyBlue = (0 * copys[i][j].rgbtBlue) +
                             (-2 * copys[i - 1][j].rgbtBlue) +
                             (0 * copys[i][j + 1].rgbtBlue) +
                             (-1 * copys[i - 1][j + 1].rgbtBlue) +
                             (0 * copys[i][j - 1].rgbtBlue) +
                             (-1 * copys[i - 1][j - 1].rgbtBlue);
                }
                else if (j == width - 1 && 0 < i < height - 1) // right edge
                {
                    GxRed = (0 * copys[i][j].rgbtRed) +
                            (0 * copys[i - 1][j].rgbtRed) +
                            (-2 * copys[i][j - 1].rgbtRed) +
                            (-1 * copys[i - 1][j - 1].rgbtRed) +
                            (-1 * copys[i + 1][j - 1].rgbtRed) +
                            (0 * copys[i + 1][j].rgbtRed);

                    GxGreen = (0 * copys[i][j].rgbtGreen) +
                              (0 * copys[i - 1][j].rgbtGreen) +
                              (-2 * copys[i][j - 1].rgbtGreen) +
                              (-1 * copys[i - 1][j - 1].rgbtGreen) +
                              (-1 * copys[i + 1][j - 1].rgbtGreen) +
                              (0 * copys[i + 1][j].rgbtGreen);

                    GxBlue = (0 * copys[i][j].rgbtBlue) +
                             (0 * copys[i - 1][j].rgbtBlue) +
                             (-2 * copys[i][j - 1].rgbtBlue) +
                             (-1 * copys[i - 1][j - 1].rgbtBlue) +
                             (-1 * copys[i + 1][j - 1].rgbtBlue) +
                             (0 * copys[i + 1][j].rgbtBlue);

                    GyRed = (0 * copys[i][j].rgbtRed) +
                            (-2 * copys[i - 1][j].rgbtRed) +
                            (0 * copys[i][j - 1].rgbtRed) +
                            (-1 * copys[i - 1][j - 1].rgbtRed) +
                            (1 * copys[i + 1][j - 1].rgbtRed) +
                            (2 * copys[i + 1][j].rgbtRed);
                    GyGreen = (0 * copys[i][j].rgbtGreen) +
                              (-2 * copys[i - 1][j].rgbtGreen) +
                              (0 * copys[i][j - 1].rgbtGreen) +
                              (-1 * copys[i - 1][j - 1].rgbtGreen) +
                              (1 * copys[i + 1][j - 1].rgbtGreen) +
                              (2 * copys[i + 1][j].rgbtGreen);
                    GyBlue = (0 * copys[i][j].rgbtBlue) +
                             (-2 * copys[i - 1][j].rgbtBlue) +
                             (0 * copys[i][j - 1].rgbtBlue) +
                             (-1 * copys[i - 1][j - 1].rgbtBlue) +
                             (1 * copys[i + 1][j - 1].rgbtBlue) +
                             (2 * copys[i + 1][j].rgbtBlue);
                }
                double RedD = sqrt(GxRed * GxRed + GyRed * GyRed);
                int Red = round(RedD);
                double GreenD = sqrt(GxGreen * GxGreen + GyGreen * GyGreen);
                int Green = round(GreenD);
                double BlueD = sqrt(GxBlue * GxBlue + GyBlue * GyBlue);
                int Blue = round(BlueD);

                if (Red > 255)
                {
                    Red = 255;
                }

                if (Green > 255)
                {
                    Green = 255;
                }
                if (Blue > 255)
                {
                    Blue = 255;
                }

                image[i][j].rgbtRed = Red;
                image[i][j].rgbtGreen = Green;
                image[i][j].rgbtBlue = Blue;
            }
            else
            {
                double GxRed = (0 * copys[i][j].rgbtRed) +          // 6
                               (-2 * copys[i][j - 1].rgbtRed) +     // 5
                               (2 * copys[i][j + 1].rgbtRed) +      // 7
                               (0 * copys[i + 1][j].rgbtRed) +      // 10
                               (-1 * copys[i + 1][j - 1].rgbtRed) + // 9
                               (1 * copys[i + 1][j + 1].rgbtRed) +  // 11
                               (0 * copys[i - 1][j].rgbtRed) +      // 2
                               (-1 * copys[i - 1][j - 1].rgbtRed) + // 1
                               (1 * copys[i - 1][j + 1].rgbtRed);   // 3

                double GxGreen = (0 * copys[i][j].rgbtGreen) +
                                 (-2 * copys[i][j - 1].rgbtGreen) +
                                 (2 * copys[i][j + 1].rgbtGreen) +
                                 (0 * copys[i + 1][j].rgbtGreen) +
                                 (-1 * copys[i + 1][j - 1].rgbtGreen) +
                                 (1 * copys[i + 1][j + 1].rgbtGreen) +
                                 (0 * copys[i - 1][j].rgbtGreen) +
                                 (-1 * copys[i - 1][j - 1].rgbtGreen) +
                                 (1 * copys[i - 1][j + 1].rgbtGreen);

                double GxBlue = (0 * copys[i][j].rgbtBlue) +
                                (-2 * copys[i][j - 1].rgbtBlue) +
                                (2 * copys[i][j + 1].rgbtBlue) +
                                (0 * copys[i + 1][j].rgbtBlue) +
                                (-1 * copys[i + 1][j - 1].rgbtBlue) +
                                (1 * copys[i + 1][j + 1].rgbtBlue) +
                                (0 * copys[i - 1][j].rgbtBlue) +
                                (-1 * copys[i - 1][j - 1].rgbtBlue) +
                                (1 * copys[i - 1][j + 1].rgbtBlue);

                double GyRed = (0 * copys[i][j].rgbtRed) +
                               (0 * copys[i][j - 1].rgbtRed) +
                               (0 * copys[i][j + 1].rgbtRed) +
                               (2 * copys[i + 1][j].rgbtRed) +
                               (1 * copys[i + 1][j - 1].rgbtRed) +
                               (1 * copys[i + 1][j + 1].rgbtRed) +
                               (-2 * copys[i - 1][j].rgbtRed) +
                               (-1 * copys[i - 1][j - 1].rgbtRed) +
                               (-1 * copys[i - 1][j + 1].rgbtRed);

                double GyGreen = (0 * copys[i][j].rgbtGreen) +
                                 (0 * copys[i][j - 1].rgbtGreen) +
                                 (0 * copys[i][j + 1].rgbtGreen) +
                                 (2 * copys[i + 1][j].rgbtGreen) +
                                 (1 * copys[i + 1][j - 1].rgbtGreen) +
                                 (1 * copys[i + 1][j + 1].rgbtGreen) +
                                 (-2 * copys[i - 1][j].rgbtGreen) +
                                 (-1 * copys[i - 1][j - 1].rgbtGreen) +
                                 (-1 * copys[i - 1][j + 1].rgbtGreen);

                double GyBlue = (0 * copys[i][j].rgbtBlue) +
                                (0 * copys[i][j - 1].rgbtBlue) +
                                (0 * copys[i][j + 1].rgbtBlue) +
                                (2 * copys[i + 1][j].rgbtBlue) +
                                (1 * copys[i + 1][j - 1].rgbtBlue) +
                                (1 * copys[i + 1][j + 1].rgbtBlue) +
                                (-2 * copys[i - 1][j].rgbtBlue) +
                                (-1 * copys[i - 1][j - 1].rgbtBlue) +
                                (-1 * copys[i - 1][j + 1].rgbtBlue);

                double RedD = sqrt(GxRed * GxRed + GyRed * GyRed);
                int Red = round(RedD);
                double GreenD = sqrt(GxGreen * GxGreen + GyGreen * GyGreen);
                int Green = round(GreenD);
                double BlueD = sqrt(GxBlue * GxBlue + GyBlue * GyBlue);
                int Blue = round(BlueD);

                if (Red > 255)
                {
                    Red = 255;
                }

                if (Green > 255)
                {
                    Green = 255;
                }
                if (Blue > 255)
                {
                    Blue = 255;
                }

                image[i][j].rgbtRed = Red;
                image[i][j].rgbtGreen = Green;
                image[i][j].rgbtBlue = Blue;
            }
        }
    }
    return;
}
