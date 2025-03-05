#pragma once
#include "Figure.h"
class Canvas
{
public:
	Canvas(uint8_t height, uint8_t width);
	void repaint();
	bool moveObject(uint8_t id, uint8_t x, uint8_t y);
	bool eraseObject(uint8_t id);
	bool fillObject(uint8_t id);
	void addObject(IFigure*);
	inline std::vector<IFigure*> getObjects() const { return objects;};
private:
	std::vector<IFigure*> objects;
	uint8_t width;
	uint8_t height;
};

//237*60