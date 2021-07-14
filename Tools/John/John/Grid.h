#pragma once

#include "UINode.h"

#include <vector>
#include <tuple>

#include "MapTile.h"

constexpr SDL_Color ZONE_COLORS[10] = {
	CGA_TRANSPARENT,	// 0
	CGA_LT_RED,			// 1
	CGA_BROWN,			// 2
	CGA_GREEN,			// 3
	CGA_LT_GREEN,		// 4
	CGA_CYAN,			// 5
	CGA_LT_CYAN,		// 6
	CGA_LT_BLUE,			// 7
	CGA_LT_MAGENTA,		// 8
	CGA_MAGENTA,		// 9
};

class Grid : public UINode
{
public:
	Grid();
	~Grid();

	virtual void draw(const SDL_Rect& container);
	void drawTiles(const SDL_Rect& container);
	void drawCursor(const SDL_Rect& container);
	void drawGrid(const SDL_Rect& container);

	virtual bool onKeyDown(const SDL_Event& e);
	virtual bool onMouseDown(const SDL_Event& e);
	virtual bool onDrag(const SDL_Event& e);

	SDL_Point tileFromMouse(const SDL_Event& e);

	SDL_Point position;
	SDL_Point lastTilePlaced = { 0, 0 };

	MapTile map[512][512];

	void changeLayer(int dir);
	void changeZone(int dir);

	int getCurrentLayer();
	int getCurrentZone();

private:
	int maxX = 10;
	int maxY = 10;

	int currentLayer = 1;
	int currentZone;

	void placeTile(int x, int y);
	void floodFill(int x, int y);
	bool floodable(int x, int y, int floodType, const std::vector<std::tuple<int, int>>& history);
	void removeTile(int x, int y, bool all);
};

