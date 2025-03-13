#pragma once
#include "Canvas.h"
#include <string>
#include <fstream>
#include <iostream>


static class FileManager
{
public:
    static Canvas loadFromFile(std::string fileName) 
    {
        Canvas canvas(60, 237);
        
        std::ifstream inFile(fileName, std::ios::binary);
       
        if (!inFile.is_open()) {
            std::cout << "Error: Could not open file" << std::endl;
            return canvas;
        }
        int info[7];
        while (inFile.read(reinterpret_cast<char*> (info), 28))
        {
            std::cout << info[0];
            switch (info[0])
            {
            case 0:
            {
                figures::Circle* newFigure = new figures::Circle(info[1], info[2], info[3]);
                canvas.addObject(newFigure);
                std::cout << info[5];
                if (info[5]) canvas.fillObject(canvas.getObjects().size() - 1);
                break;
            }
            case 1:
            {
                figures::Rectangle* newFigure = new figures::Rectangle(info[1], info[2], info[3], info[4]);
                canvas.addObject(newFigure);
                if (info[5]) canvas.fillObject(canvas.getObjects().size() - 1);
                break;
            }
            case 2:
            {
                figures::Triangle* newFigure = new figures::Triangle(info[1], info[2], info[3], info[4], info[5]);
                canvas.addObject(newFigure);
                if (info[5]) canvas.fillObject(canvas.getObjects().size() - 1);
                break;
            }
            default:
                break;
            }
        }
        inFile.close();
        return canvas;
    };
	static void loadToFile(std::string fileName, Canvas canvas)
    {
        std::ofstream outFile(fileName, std::ios::binary);
        if (!outFile.is_open()) {
            std::cout << "Error: Could not open file "  << std::endl;
            return;
        }

        for (IFigure* figure : canvas.getObjects()) {
            for (int v : figure->getStartValues()) {
                outFile.write(reinterpret_cast<const char*>(&v), sizeof(int));
            }
            int v = figure->getIsFilled();
            outFile.write(reinterpret_cast<const char*>(&v), sizeof(int));
        }
        outFile.close();
    }
};

