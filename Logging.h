#pragma once

#include <string>

#ifdef LOGGING_IMP
int errLine = 0;
std::string errFile = "!Main.cpp";
#undef LOGGIN_IMP
#else
extern int errLine;
extern std::string errFile;
#endif

void ShowError(std::string error, std::string errorCode);

template <typename T>
T _GameErr(T err, const char* file, int line)
{
	errLine = line;
	errFile = std::string(file);
	return err;
}
#define GameErr(x) (_GameErr((x), __FILE__, __LINE__))