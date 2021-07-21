#include "Checkbox.h"

#include "App.h"
#include "Windows.h"

Checkbox::Checkbox(bool* toCheck) : UINode(
	{
		24, 0,
		22, 22,
		"",
		CGA_TRANSPARENT,
		StyleDirection::TOP,
		StyleDirection::RIGHT
	}
)
{
	this->toCheck = toCheck;
	if (
		!APP->tryLoadTexture("Resources/CheckBoxUnchecked.png", "CheckboxUnchecked", &uncheckDepressed) ||
		!APP->tryLoadTexture("Resources/CheckBoxUncheckedPressed.png", "CheckboxUncheckedPressed", &uncheckPressed) ||
		!APP->tryLoadTexture("Resources/CheckBoxChecked.png", "CheckboxChecked", &checkDepressed) ||
		!APP->tryLoadTexture("Resources/CheckBoxCheckedPressed.png", "CheckboxCheckedPressed", &checkPressed)
	)
	{
		MessageBoxA(NULL, "Failed to initialize checkbox images", NULL, MB_OK);
		return;
	}

	image = *toCheck
		? checkDepressed
		: uncheckDepressed;
}

bool Checkbox::onMouseDown(const SDL_Event& e)
{
	image = *toCheck
		? checkPressed
		: uncheckPressed;
	return true;
}

bool Checkbox::onMouseUp(const SDL_Event& e)
{
	*toCheck ^= true;

	image = *toCheck
		? checkDepressed
		: uncheckDepressed;
	return true;
}