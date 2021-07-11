#include "SaveButton.h"

#include "Windows.h"

SaveButton::SaveButton() : UIButton(
	{
		0, 0,
		128, 32,
		"Resources/Save"
	}
)
{

}

bool SaveButton::onMouseUp(const SDL_Event& e)
{
	UIButton::onMouseUp(e);

	// Save

	return true;
}