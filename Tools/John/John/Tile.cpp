#include "Tile.h"

#include "App.h"

#include "Windows.h"

Tile::Tile(int t, int tileNum, Texture* image) : UINode({
		(uint16_t)((t % 3) * 72 + 8),
		(uint16_t)((t / 3) * 72 + 8),
		64, 64,
		"Resources/Tile",
		CGA_TRANSPARENT,
		StyleDirection::TOP,
		StyleDirection::LEFT
	})
{
	this->tileNum = tileNum;
	if (!APP->tryLoadTexture("Resources/TilePressed.png", "Resources/TilePressed", &pressed))
	{
		MessageBoxA(NULL, "Failed to load tile image!", NULL, MB_OK);
	}
	depressed = this->image;
	this->tileImage = image;
}

void Tile::draw(const SDL_Rect& container)
{
	UINode::draw(container);
	auto offset = getDrawOffset(container);
	SDL_Rect dim = {
		offset.x + 2, offset.y + 2,
		calcX(style.width) - 4, calcY(style.height) - 4
	};

	SDL_RenderCopy(
		APP->renderer,
		tileImage->texture,
		&tileImage->src,
		&dim
	);
}

bool Tile::onMouseDown(const SDL_Event& e)
{
	image = pressed;
	return true;
}

bool Tile::onMouseUp(const SDL_Event& e)
{
	image = depressed;

	APP->selectedTile = this->tileNum;
	APP->selectedTileTexture = this->tileImage;

	APP->selectedEntity = nullptr;
	return true;
}