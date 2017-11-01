#include "tool.h"
#include <string>

std::string Tool::toLower(std::string line) {
	transform(line.begin(), line.end(), line.begin(),(int (*)(int))tolower);
	return line;
}

bool Tool::tryParseInt(std::string input, int* out) {
	try {
		*out = stoi(input);
		return true;
	}
	catch (const std::exception&) {
		return false;
	}
}

bool Tool::tryReadInt(int* out) {
	return tryParseInt(readLine(), out);
}

std::string Tool::readLine() {
	std::string line = "";
	getline(std::cin, line);
	return line;
}

void Tool::pressToContinue() {
	std::cout << "\nPress enter to continue\n";
	Tool::readLine();
}

void Tool::errorMessageInvalidInput() {
	std::cout << "Invalid input, please try again\n";
}

void Tool::printSeparator() {
	std::cout << "\n\n---------------------------------------------------------\n\n\n";
}
