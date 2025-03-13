#include "Canvas.h"
#include <iostream>

Canvas::Canvas(int height, int width)
	:height(height), width(width)
{
}

void Canvas::repaint()
{
	system("cls");
	std::vector<std::vector<char>> canvas(height, std::vector<char>(width, 0));
	for (int i = 0; i < 60; ++i)
	{
		for (int j = 0; j < 237; ++j)
		{
			canvas[i][j] = ' ';
		}
	}

	for (int i = 0; i < objects.size(); ++i)
	{
		std::vector<std::pair<int, int>> coordinates = objects[i]->getCoordinates();
		for (std::pair<int, int> pair : coordinates)
		{
			if (pair.first < 60 && pair.first >= 0 && pair.second < 237 && pair.second >= 0) canvas[pair.first][pair.second] = '@';
		}
	}

	for (int i = 0; i < 237; ++i)
	{
		canvas[0][i] = '-';
		canvas[59][i] = '-';
	}
	for (int i = 0; i < 60; ++i)
	{
		canvas[i][0] = '|';
		canvas[i][236] = '|';
	}
	for (int i = 0; i < 60; ++i)
	{
		for (int j = 0; j < 237; ++j)
		{
			std::cout << canvas[i][j];
		}
	}
}

bool Canvas::eraseObject(int id)
{
	if (id < 0 || id >= objects.size())return true;
	objects.erase(objects.begin() + id);
	return false;
}

bool Canvas::fillObject(int id)
{
	if (id < 0 || id >= objects.size())return true;
	objects[id]->fill();
	return false;
}

bool Canvas::moveObject(int id, int x, int y)
{
	if (id < 0 || id >= objects.size())return true;
	objects[id]->transform(x, y);
	return false;
}

void Canvas::addObject(IFigure* figure)
{
	objects.push_back(figure);
}