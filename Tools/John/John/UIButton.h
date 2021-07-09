#pragma once
#include "UINode.h"

#include <string>

class UIButton : public UINode
{
public:
	UIButton(SDL_FPoint pos, std::string texture);
	~UIButton();

	SDL_Texture* pressed;

};

