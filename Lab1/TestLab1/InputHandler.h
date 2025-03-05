#pragma once
#include <string>
#include <vector>

class InputHandler
{
public:
	InputHandler(std::string);
	inline bool isBad() const { return bad; };
	inline std::string getCommand() const { return command; };
	inline std::string getFilename() const { return filename; };
    inline std::vector<int> getArgs() const { return args; };
	inline std::string getTypeFigure() const { return typeFigure; };
private:
	std::string command = "";
	std::string filename = "";
	std::string typeFigure = "";
	bool bad = false;
	std::vector<int> args;
};

