#ifndef TOOL_H
#define TOOL_H

#include <algorithm>
#include <iostream>

class Tool {
public:
	static std::string readLine();
	static bool tryParseInt(std::string input, int* out);
	static bool tryReadInt(int* out);
	static void errorMessageInvalidInput();
	static void printSeparator();
};

#endif // TOOL_H
