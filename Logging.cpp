#define LOGGIN_IMP
#include "Logging.h"

int errLine;
std::string errFile;

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