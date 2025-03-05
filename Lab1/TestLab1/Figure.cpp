#include "pch.h"
#include "Figure.h"

figures::Circle::Circle(uint8_t x_pos, uint8_t y_pos, uint8_t radius)
{
    startValues = {0, x_pos, y_pos, radius, 0};
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
                uint8_t x = j * cos(i);
                uint8_t y = j * sin(i);

                coordinates.push_back(std::pair<uint8_t, uint8_t>(x + startValues[1], y + startValues[2]));
            }
        }
    }
    else
    {
        for (int i = 0; i <= 360; i++)
        {
            uint8_t x = startValues[3] * cos(i);
            uint8_t y = startValues[3] * sin(i);

            coordinates.push_back(std::pair<uint8_t, uint8_t>(x + startValues[1], y + startValues[2]));
        }
    }
}

void figures::Circle::transform(uint8_t x, uint8_t y)
{
    startValues[1] += x;
    startValues[2] += y;
    refreshCoordinates();
}

figures::Rectangle::Rectangle(uint8_t x_pos1, uint8_t y_pos1, uint8_t x_pos2, uint8_t y_pos2)
{
    if (x_pos1 > x_pos2) std::swap(x_pos1, x_pos2);
    if (y_pos1 > y_pos2) std::swap(y_pos1, y_pos2);
    startValues = { 1, x_pos1, y_pos1, x_pos2, y_pos2};
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
                coordinates.push_back(std::pair<uint8_t, uint8_t>(i, j));
            }
        }
    }
    else
    {
        for (int i = startValues[1]; i <= startValues[3]; ++i)
        {
            coordinates.push_back(std::pair<uint8_t, uint8_t>(i, startValues[2]));
            coordinates.push_back(std::pair<uint8_t, uint8_t>(i, startValues[4]));
        }
        for (int i = startValues[2]; i <= startValues[4]; ++i)
        {
            coordinates.push_back(std::pair<uint8_t, uint8_t>(startValues[1], i));
            coordinates.push_back(std::pair<uint8_t, uint8_t>(startValues[3], i));
        }
    }
}

void figures::Rectangle::transform(uint8_t x, uint8_t y)
{
    startValues[1] += x;
    startValues[2] += y;
    startValues[3] += x;
    startValues[4] += y;
    refreshCoordinates();
}

figures::Triangle::Triangle(uint8_t x_pos1, uint8_t y_pos1, uint8_t height)
{
    startValues = { 2, x_pos1, y_pos1, height, 0};
    refreshCoordinates();
}

void figures::Triangle::refreshCoordinates()
{
    coordinates.clear();
    if (isFilled)
    {
        for (int i = startValues[1]; i < startValues[1] + startValues[3]; ++i)
        {
            for (int j = startValues[2] - i + startValues[1]; j <= startValues[2] + i - startValues[1]; ++j)
            {
                coordinates.push_back(std::pair<uint8_t, uint8_t>(i, j));
            }
        }
    }
    else
    {
        for (int i = startValues[1]; i < startValues[1]+startValues[3]; ++i)
        {
            coordinates.push_back(std::pair<uint8_t, uint8_t>(i, startValues[2] + i - startValues[1]));
            coordinates.push_back(std::pair<uint8_t, uint8_t>(i, startValues[2] - i + startValues[1]));
        }
        for (int i = startValues[2] - startValues[3]; i <= startValues[2] + startValues[3]; ++i)
        {
            coordinates.push_back(std::pair<uint8_t, uint8_t>(startValues[1]+startValues[3], i));
        }
    }
}

void figures::Triangle::transform(uint8_t x, uint8_t y)
{
    startValues[1] += x;
    startValues[2] += y;
    refreshCoordinates();
}
