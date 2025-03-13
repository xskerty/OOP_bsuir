#include "pch.h"
#include "PaintApplication.h"

PaintApplication::PaintApplication()
{
	canvases.push_back(Canvas(60, 237));
}


void PaintApplication::AppForTest(std::vector<std::string> command)
{

	for (int c = 0; c < command.size(); ++c) {

		inputResult = InputHandler(command[c]);

		if (inputResult.isBad()) continue;
		if (inputResult.getCommand() == "undo")
		{
			if (currentIndex > 0)
			{
				currentIndex--;
			}
		}
		else if (inputResult.getCommand() == "redo")
		{
			if (canvases.size() - currentIndex > 1)
			{
				currentIndex++;
			}
		}
		else if (inputResult.getCommand() == "save")
		{
			FileManager::loadToFile(inputResult.getFilename(), canvases[currentIndex]);
		}
		else if (inputResult.getCommand() == "load")
		{
			for (int i = 0; i < canvases.size() - currentIndex - 1; ++i)
			{
				canvases.pop_back();
			}
			canvases.push_back(FileManager::loadFromFile(inputResult.getFilename()));
			currentIndex++;
		}
		else if (inputResult.getCommand() == "add")
		{
			std::vector<int> args = inputResult.getArgs();
			if (inputResult.getTypeFigure() == "circle")
			{
				if (args.size() != 3 || args[2] < 0) continue;
				for (int i = 0; i < canvases.size() - currentIndex - 1; ++i)
				{
					canvases.pop_back();
				}
				canvases.push_back(canvases[currentIndex]);
				currentIndex++;
				figures::Circle* newFigure = new figures::Circle(args[0], args[1], args[2]);
				canvases[currentIndex].addObject(newFigure);
			}
			else if (inputResult.getTypeFigure() == "rectangle")
			{
				if (args.size() != 4) continue;
				for (int i = 0; i < canvases.size() - currentIndex - 1; ++i)
				{
					canvases.pop_back();
				}
				canvases.push_back(canvases[currentIndex]);
				currentIndex++;
				figures::Rectangle* newFigure = new figures::Rectangle(args[0], args[1], args[2], args[3]);
				canvases[currentIndex].addObject(newFigure);
			}
			else if (inputResult.getTypeFigure() == "triangle")
			{
				if (args.size() != 3 || args[2] < 0) continue;
				for (int i = 0; i < canvases.size() - currentIndex - 1; ++i)
				{
					canvases.pop_back();
				}
				canvases.push_back(canvases[currentIndex]);
				currentIndex++;
				figures::Triangle* newFigure = new figures::Triangle(args[0], args[1], args[2]);
				canvases[currentIndex].addObject(newFigure);
			}
		}
		else if (inputResult.getCommand() == "move")
		{
			std::vector<int> args = inputResult.getArgs();
			if (args.size() != 3) continue;
			for (int i = 0; i < canvases.size() - currentIndex - 1; ++i)
			{
				canvases.pop_back();
			}
			Canvas canvas(60, 237);
			for (int i = 0; i < canvases[currentIndex].getObjects().size(); ++i)
			{
				std::vector<uint8_t> argsf = canvases[currentIndex].getObjects()[i]->getStartValues();
				switch (argsf[0])
				{
				case 0:
				{
					figures::Circle* newFigure = new figures::Circle(argsf[1], argsf[2], argsf[3]);
					if (canvases[currentIndex].getObjects()[i]->getIsFilled()) newFigure->fill();
					canvas.addObject(newFigure);
					break;
				}
				case 1:
				{
					figures::Rectangle* newFigure = new figures::Rectangle(argsf[1], argsf[2], argsf[3], argsf[4]);
					if (canvases[currentIndex].getObjects()[i]->getIsFilled()) newFigure->fill();
					canvas.addObject(newFigure);
					break;
				}
				case 2:
				{
					figures::Triangle* newFigure = new figures::Triangle(argsf[1], argsf[2], argsf[3]);
					if (canvases[currentIndex].getObjects()[i]->getIsFilled()) newFigure->fill();
					canvas.addObject(newFigure);
					break;
				}
				default:
					break;
				}

			}

			canvases.push_back(canvas);
			currentIndex++;
			canvases[currentIndex].moveObject(args[0], args[1], args[2]);
		}
		else if (inputResult.getCommand() == "fill")
		{
			std::vector<int> args = inputResult.getArgs();
			if (args.size() != 1) continue;
			for (int i = 0; i < canvases.size() - currentIndex - 1; ++i)
			{
				canvases.pop_back();
			}
			Canvas canvas = Canvas(60, 237);
			for (int i = 0; i < canvases[currentIndex].getObjects().size(); ++i)
			{
				std::vector<uint8_t> argsf = canvases[currentIndex].getObjects()[i]->getStartValues();
				switch (argsf[0])
				{
				case 0:
				{
					figures::Circle* newFigure = new figures::Circle(argsf[1], argsf[2], argsf[3]);
					if (canvases[currentIndex].getObjects()[i]->getIsFilled()) newFigure->fill();
					canvas.addObject(newFigure);
					break;
				}
				case 1:
				{
					figures::Rectangle* newFigure = new figures::Rectangle(argsf[1], argsf[2], argsf[3], argsf[4]);
					if (canvases[currentIndex].getObjects()[i]->getIsFilled()) newFigure->fill();
					canvas.addObject(newFigure);
					break;
				}
				case 2:
				{
					figures::Triangle* newFigure = new figures::Triangle(argsf[1], argsf[2], argsf[3]);
					if (canvases[currentIndex].getObjects()[i]->getIsFilled()) newFigure->fill();
					canvas.addObject(newFigure);
					break;
				}
				default:
					break;
				}

			}

			canvases.push_back(canvas);
			currentIndex++;
			canvases[currentIndex].fillObject(args[0]);
		}
		else if (inputResult.getCommand() == "remove")
		{
			std::vector<int> args = inputResult.getArgs();
			if (args.size() != 1) continue;
			for (int i = 0; i < canvases.size() - currentIndex - 1; ++i)
			{
				canvases.pop_back();
			}
			canvases.push_back(canvases[currentIndex]);
			currentIndex++;
			canvases[currentIndex].eraseObject(args[0]);
		}
	}
}