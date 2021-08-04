#include "Logging.h"

thread_local int errLine;
thread_local std::string errFile;

#ifdef CONSOLE_LOG
#include <iostream>
#endif

#ifdef WIN_LOG
#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#endif

void ShowError(std::string error, std::string errorCode)
{
	#ifdef CONSOLE_LOG
	std::cerr << "ERROR: " << error << std::endl;
	if (!errorCode.empty())
	{
		std::cerr << errorCode << std::endl;
	}
	#endif
	#ifdef WIN_LOG
	MessageBoxA(NULL, (error + "\n" + errorCode + "\nAt " + std::string(errFile) + "#" + std::to_string(errLine)).c_str(), NULL, MB_OK);
	#endif
}

void SimpleError(std::string error)
{
	#ifdef CONSOLE_LOG
	std::cerr << "ERROR: " << error << std::endl;
	#endif
	#ifdef WIN_LOG
	MessageBoxA(NULL, error.c_str(), NULL, MB_OK);
	#endif
}

void Warn(std::string warning)
{
	#ifndef _DEBUG
	return;
	#endif
	#ifdef CONSOLE_LOG
	std::cerr << "WARNING: " << warning << std::endl;
	#endif
	#ifdef WIN_LOG
	MessageBoxA(NULL, warning.c_str(), "Warning", MB_OK);
	#endif
}

std::string vec3ToString(_In_ glm::vec3 in)
{
	return std::to_string(in.x) + ", " + std::to_string(in.y) + ", " + std::to_string(in.z);
}