#pragma once

#include "UINode.h"

#include "MapTile.h"

class Grid : public UINode
{
public:
	Grid();
	~Grid();

	virtual void draw(const SDL_Rect& container);
	virtual bool onKeyDown(const SDL_Event& e);
	virtual bool onMouseDown(const SDL_Event& e);

	SDL_Point position;

	MapTile* map[512][512];
	int maxX = 10;
	int maxY = 10;
};

