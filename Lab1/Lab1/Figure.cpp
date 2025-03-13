#include "Figure.h"
#include <math.h>

figures::Circle::Circle(int x_pos, int y_pos, int radius)
{
    startValues = {0, x_pos, y_pos, radius, 0, 0};
    refreshCoordinates();  
}

void figures::Circle::refreshCoordinates()
{   
    coordinates.clear();
    if (isFilled)
    {
        for (int j = 0; j <= startValues[3]; ++j)
        {
            for (int i = 0; i <= 360; i++)
            {
                int x = j * cos(i);
                int y = j * sin(i);

                coordinates.push_back(std::pair<int, int>(x + startValues[1], y + startValues[2]));
            }
        }
    }
    else
    {
        for (int i = 0; i <= 360; i++)
        {
            int x = startValues[3] * cos(i);
            int y = startValues[3] * sin(i);

            coordinates.push_back(std::pair<int, int>(x + startValues[1], y + startValues[2]));
        }
    }
}

void figures::Circle::transform(int x, int y)
{
    startValues[1] += x;
    startValues[2] += y;
    refreshCoordinates();
}

figures::Rectangle::Rectangle(int x_pos1, int y_pos1, int x_pos2, int y_pos2)
{
    if (x_pos1 > x_pos2) std::swap(x_pos1, x_pos2);
    if (y_pos1 > y_pos2) std::swap(y_pos1, y_pos2);
    startValues = { 1, x_pos1, y_pos1, x_pos2, y_pos2, 0};
    refreshCoordinates();
}

void figures::Rectangle::refreshCoordinates()
{
    coordinates.clear();
    if (isFilled)
    {
        for (int i = startValues[1]; i <= startValues[3]; ++i)
        {
            for (int j = startValues[2]; j <= startValues[4]; ++j)
            {
                coordinates.push_back(std::pair<int, int>(i, j));
            }
        }
    }
    else
    {
        for (int i = startValues[1]; i <= startValues[3]; ++i)
        {
            coordinates.push_back(std::pair<int, int>(i, startValues[2]));
            coordinates.push_back(std::pair<int, int>(i, startValues[4]));
        }
        for (int i = startValues[2]; i <= startValues[4]; ++i)
        {
            coordinates.push_back(std::pair<int, int>(startValues[1], i));
            coordinates.push_back(std::pair<int, int>(startValues[3], i));
        }
    }
}

void figures::Rectangle::transform(int x, int y)
{
    startValues[1] += x;
    startValues[2] += y;
    startValues[3] += x;
    startValues[4] += y;
    refreshCoordinates();
}

figures::Triangle::Triangle(int x_pos1, int y_pos1, int side1, int side2, int side3)
{
    startValues = { 2, x_pos1, y_pos1, side1, side2, side3};
    refreshCoordinates();
}

void figures::Triangle::refreshCoordinates()
{
    coordinates.clear();

    std::vector<std::pair<int, int>> vertices(3);

    int a = startValues[3];
    int b = startValues[4];
    int c = startValues[5];

    double p = (a + b + c) / 2;
    double h = 2 * sqrt(p * (p - a) * (p - b) * (p - c)) / c;

    double c1 = sqrt(a * a - h * h);
    double c2 = c - c1;


    for (int i = 0; i < round(h); ++i)
    {
        coordinates.push_back(std::pair<int, int>(startValues[1] + i, startValues[2] - round(c1 * i / h)));
        coordinates.push_back(std::pair<int, int>(startValues[1] + i, startValues[2] + round(c2 * i / h)));

        if (isFilled)
        {
            for (int j = 0; j <= round(c * i / h); ++j)
            {
                coordinates.push_back(std::pair<int, int>(startValues[1] + i, startValues[2] - c1*i/h + j ));
            }
        }
    }

    for (int i = 0; i < c; ++i)
    {
        coordinates.push_back(std::pair<int, int>(startValues[1] + round(h) - 1, startValues[2] - c1 + i));
    }
}

void figures::Triangle::transform(int x, int y)
{
    startValues[1] += x;
    startValues[2] += y;
    refreshCoordinates();
}
