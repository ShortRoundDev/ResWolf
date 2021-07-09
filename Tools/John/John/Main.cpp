#include <Windows.h>
#include "App.h"

int WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR     lpCmdLine,
	int       nShowCmd
)
{
	App::init("John");
	while (!APP->shouldQuit)
	{
		APP->events();
		APP->update();
		APP->draw();
	}
	return 1;
}