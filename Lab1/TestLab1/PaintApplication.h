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
	void AppForTest(std::vector<std::string> command);
private:
	std::vector<Canvas> canvases;
	uint8_t currentIndex = 0;
	std::string input;
	InputHandler inputResult = InputHandler("");
};

