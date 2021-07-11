#include "Grid.h"

#include <iostream>
#include <Windows.h>

#include "SDL.h"

#include "App.h"

Grid::Grid() : UINode(
	{
		0, 34,
		UINode::PCT(100), UINode::PCT(100)
	}
)
{
	position = { 0, 0 };
	for (int i = 0; i < 512; i++)
	{
		for (int j = 0; j < 512; j++)
		{
			this->map[j][i] = nullptr;
		}
	}
}

Grid::~Grid()
{

}

void Grid::draw(const SDL_Rect& container)
{
	SDL_Rect dimensions = {
		0, 0,
		calcX(style.width), calcY(style.height)
	};

	// draw tiles
	for (int y = position.y / 64; y < (position.y + APP->height) / 64 && y < 256; y++)
	{
		for (int x = position.x / 64; x < (position.x + APP->width) / 64 && x < 256; x++)
		{
			auto tile = this->map[x][y];
			if (tile != nullptr)
			{
				int _x = (x * 64) - position.x;
				int _y = (y * 64) - position.y + 34;

				SDL_Rect dst = {
					_x, _y,
					64, 64
				};

				SDL_RenderCopy(APP->renderer, tile->texture->texture, &tile->texture->src, &dst);
			}
		}
	}

	// draw cursor
	if (APP->selectedTile != 0 && APP->selectedTileTexture != nullptr)
	{
		int x, y;

		SDL_GetMouseState(&x, &y);
		x = ((x + position.x) / 64 * 64) - position.x;
		y = (y - 34 + position.y) / 64 * 64 - position.y + 34;

		SDL_Rect dst = {
			x, y,
			64, 64
		};

		SDL_RenderCopy(APP->renderer, APP->selectedTileTexture->texture, &APP->selectedTileTexture->src, &dst);
	}

	// draw grid
	SDL_SetRenderDrawColor(APP->renderer, CGA_LT_GRAY.r, CGA_LT_GRAY.g, CGA_LT_GRAY.b, CGA_LT_GRAY.a);
	for (int x = (-position.x % 64); x < dimensions.w + 64; x += 64)
	{
		for (int y = style.y + (-position.y % 64); y < dimensions.h; y += 64)
		{
			SDL_Rect dot = {
				x - 2, y - 2, 4, 4
			};
			SDL_RenderFillRect(APP->renderer, &dot);
		}
	}

	SDL_SetRenderDrawColor(APP->renderer, CGA_YELLOW.r, CGA_YELLOW.g, CGA_YELLOW.b, CGA_YELLOW.a);
	//draw boundaries
	if (position.x < maxX * 64 && position.y < maxY * 64)
	{
		for (int y = 0; y < maxY * 4 + 1; y++) // * 4 for 16px grid
		{
			SDL_Rect dot = {
				maxX * 64 - position.x - 2, y * 16 - position.y - 2 + 34,
				4, 4
			};
			SDL_RenderFillRect(APP->renderer, &dot);
		}

		for (int x = 0; x < maxX * 4; x++) // * 4 for 16px grid
		{
			SDL_Rect dot = {
				x * 16 - position.x - 2, maxY * 64 - position.y - 2 + 34,
				4, 4
			};
			SDL_RenderFillRect(APP->renderer, &dot);
		}
	}
}

bool Grid::onKeyDown(const SDL_Event& e)
{
	int diff = 20;
	if (e.key.keysym.mod & KMOD_LSHIFT)
	{
		diff = 64;
	}
	switch (e.key.keysym.scancode)
	{
	case SDL_SCANCODE_LEFT:
	{
		position.x -= diff;
		if (position.x < 0)
			position.x = 0;
		break;
	}
	case SDL_SCANCODE_RIGHT:
	{
		position.x += diff;
		break;
	}
	case SDL_SCANCODE_UP:
	{
		position.y -= diff;
		if (position.y < 0)
			position.y = 0;
		break;
	}
	case SDL_SCANCODE_DOWN:
	{
		position.y += diff;
	}
	}
	return true;
}

bool Grid::onMouseDown(const SDL_Event& e)
{
	SDL_Point mouse = {
		e.button.x,
		e.button.y
	};
	SDL_Rect actualSize = {
		0, 34,
		calcX(PCT(100)) - 256, calcY(PCT(100)) - 34
	};
	if (!SDL_PointInRect(&mouse, &actualSize))
	{
		return true;
	}

	mouse.x = ((mouse.x + position.x) / 64);
	mouse.y = (mouse.y - 34 + position.y) / 64;

	//MessageBoxA(NULL, (std::to_string(mouse.x) + ", " + std::to_string(mouse.y)).c_str(), NULL, MB_OK);

	if (this->map[mouse.x][mouse.y] != nullptr)
	{
		delete this->map[mouse.x][mouse.y];
	}
	this->map[mouse.x][mouse.y] = new MapTile(APP->selectedTile, APP->selectedTileTexture);

	return true;
}