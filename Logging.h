#pragma once

#include <string>

extern thread_local int errLine;
extern thread_local std::string errFile;

void ShowError(std::string error, std::string errorCode);
void SimpleError(std::string error);

void Warn(std::string warning);

template <typename T>
T _GameErr(T err, const char* file, int line)
{
	errLine = line;
	errFile = std::string(file);
	return err;
}
#define GameErr(x) (_GameErr((x), __FILE__, __LINE__))