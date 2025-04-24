#pragma once
#include "Figure.h"
class Canvas
{
public:
	Canvas(int height, int width);
	void repaint();
	bool moveObject(int id, int x, int y);
	bool eraseObject(int id);
	bool fillObject(int id);
	void addObject(IFigure*);
	inline std::vector<IFigure*> getObjects() const { return objects;};
private:
	std::vector<IFigure*> objects;
	int width;
	int height;
};

//237*60