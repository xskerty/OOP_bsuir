#pragma once
#include "Canvas.h"
#include "Figure.h"
#include "iostream"
#include "FileManager.h"
#include "InputHandler.h"

class PaintApplication
{
public:
	PaintApplication();
	void App();
private:
	std::vector<Canvas> canvases;
	int currentIndex = 0;
	std::string input;
	InputHandler inputResult = InputHandler("");
};

