#include "UIButton.h"
#include "App.h"

#define WIN32_LEAN_AND_MEAN
#include "Windows.h"

UIButton::UIButton(SDL_FPoint pos, std::string texture) :
	UINode(
		{
			pos.x, pos.y,
			128, 32
		}
	)
{
	if (!APP->tryLoadTexture(texture + ".png", texture, &image))
	{
		MessageBoxA(NULL, ("Failed to load " + texture).c_str(), NULL, MB_OK);
	}
	if (!APP->tryLoadTexture(texture + "Pressed.png", texture + "Pressed", &pressed))
	{
		MessageBoxA(NULL, ("Failed to load pressed " + texture).c_str(), NULL, MB_OK);
	}
}

UIButton::~UIButton()
{

}