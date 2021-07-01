#pragma once

#include <string>

extern int errLine;
extern std::string errFile;

void ShowError(std::string error, std::string errorCode);
void SimpleError(std::string error);

template <typename T>
T _GameErr(T err, const char* file, int line)
{
	errLine = line;
	errFile = std::string(file);
	return err;
}
#define GameErr(x) (_GameErr((x), __FILE__, __LINE__))