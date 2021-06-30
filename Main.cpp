#define WIN32_LEAN_AND_MEAN
#include "windows.h"

#include "Win32Application.h"
#include "Logging.h"

#include "GraphicsManager.h"

using namespace ResWolf;

int main(int argc, char** argv)
{
	SetHandlers();
	GraphicsError status;
	if ((status = GraphicsManager::init()) == GraphicsError::OK)
	{
		ShowError("Couldn't Initialize Graphics!", GraphicsErrorMessage(status));
		return -1;
	}
}