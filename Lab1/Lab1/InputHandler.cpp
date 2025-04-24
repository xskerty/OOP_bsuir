#include "InputHandler.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>

InputHandler::InputHandler(std::string input)
{
	std::transform(input.begin(), input.end(), input.begin(),
		[](unsigned char c) { return std::tolower(c); });

	std::vector<std::string> elems;
	std::stringstream a = std::stringstream(input);
	std::string item;
	
	while (std::getline(a, item, ' ')) {
		if (!item.empty()) {
			elems.push_back(item);
		}
	}
	if (elems.size() == 1  && (elems[0] == "undo" || elems[0] == "redo"))
	{
		command = elems[0];
	}
	else if (elems.size() == 2 && (elems[0] == "load" || elems[0] == "save"))
	{
		command = elems[0];
		filename = elems[1];
	}
	else if (elems.size() > 4 && elems.size() <= 7 && elems[0] == "add")
	{
		command = elems[0];
		typeFigure = elems[1];
		int a = 0;
		for (int i = 2; i < elems.size(); ++i)
		{
			try { a = std::stoi(elems[i]); }
			catch (std::out_of_range) { std::cout << "Out of range\n"; bad = true; }
			catch (std::invalid_argument) { std::cout << "Invalid argument\n"; bad = true; }
			if (a < -256 || a >= 256) { std::cout << "Out of range\n"; bad = true; }
			else args.push_back(a);
		}
	}
	else if (elems.size()>1 && elems.size()<6)
	{
		command = elems[0];
		int a = 0;
		for (int i = 1; i < elems.size(); ++i)
		{
			try { a = std::stoi(elems[i]); }
			catch (std::out_of_range) { std::cout << "Out of range\n"; bad = true; }
			catch (std::invalid_argument) { std::cout << "Invalid argument\n"; bad = true; }
			if (a < -256 || a >= 256) { std::cout << "Out of range\n"; bad = true; }
			else args.push_back(a);
		}
	}
	else
	{
		bad = true;
	}
}

