#include "LoadButton.h"

#include "Windows.h"

LoadButton::LoadButton() : UIButton(
	{
		128, 0,
		128, 32,
		"Resources/UI/Load"
	}
)
{

}

bool LoadButton::onMouseUp(const SDL_Event& e)
{
	UIButton::onMouseUp(e);
	MessageBoxA(NULL, "Load", NULL, MB_OK);
	return true;
}