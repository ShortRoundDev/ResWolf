#include "Grid.h"

#include <iostream>
#include <Windows.h>

#include "SDL.h"

#include "App.h"
#include "LayerEditor.h"

#include "EntityButton.h"

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
			this->map[j][i] = MapTile();
		}
	}
	children.push_back(new LayerEditor(this));
}

Grid::~Grid()
{

}

void Grid::draw(const SDL_Rect& container)
{
	drawTiles(container);
	drawCursor(container);
	drawGrid(container);

	UINode::draw(container); // draw children
}

void Grid::drawTiles(const SDL_Rect& container)
{

	// draw tiles
	for (int y = position.y / 64; y < (position.y + APP->height) / 64 && y < 256; y++)
	{
		for (int x = position.x / 64; x < (position.x + APP->width) / 64 && x < 256; x++)
		{
			for (int l = 0; l <= getCurrentLayer(); l++)
			{
				auto tile = this->map[x][y];
				if (!(l == 2 && getCurrentLayer() == 3) && tile.texture[l] != nullptr && l != 3)
				{
					int l2 = l;
					if (getCurrentLayer() == 3)
						l2++;
					int opacity = (int)(((float)(4 - (getCurrentLayer() - l2))) / 4.0f * 255);
					auto tex = tile.texture[l]->texture;
					SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);
					SDL_SetTextureAlphaMod(tex, opacity);
					int _x = (x * 64) - position.x;
					int _y = (y * 64) - position.y + 34;

					SDL_Rect dst = {
						_x, _y,
						64, 64
					};

					SDL_RenderCopy(APP->renderer, tex, &tile.texture[l]->src, &dst);
					SDL_SetTextureAlphaMod(tex, 255);
				}
				else if (l == 3 && tile.token.zone > 0)
				{

					int _x = (x * 64) - position.x;
					int _y = (y * 64) - position.y + 34;

					SDL_Rect dst = {
						_x + 4, _y + 4,
						64 - 8, 64 - 8
					};
					auto col = ZONE_COLORS[tile.token.zone];
					SDL_SetRenderDrawColor(APP->renderer, col.r, col.g, col.b, col.a);
					SDL_RenderFillRect(APP->renderer, &dst);

					SDL_Rect src = {
						tile.token.zone * 14, 0,
						14, 18
					};

					dst = {
						_x + 10, _y + 10,
						14, 18
					};

					SDL_RenderCopy(APP->renderer, APP->numbers->texture, &src, &dst);

				}
			}
		}
	}
}

void Grid::drawCursor(const SDL_Rect& container)
{
	// draw cursor
	if (getCurrentLayer() != 3)
	{
		int x, y;

		SDL_GetMouseState(&x, &y);
		x = ((x + position.x) / 64 * 64) - position.x;
		y = (y - 34 + position.y) / 64 * 64 - position.y + 34;

		SDL_Rect dst = {
			x, y,
			64, 64
		};
		Texture* t = nullptr;

		if (APP->selectedTileTexture != nullptr)
		{
			t = APP->selectedTileTexture;
		}
		else if (APP->selectedEntity != nullptr)
		{
			t = APP->selectedEntity->entTexture;
		}
		if (t != nullptr)
		{
			SDL_SetTextureAlphaMod(t->texture, 128);

			SDL_RenderCopy(
				APP->renderer,
				t->texture,
				&t->src,
				&dst
			);

			SDL_SetTextureAlphaMod(t->texture, 255);
		}

	}
	else if (getCurrentLayer() == 3 && getCurrentZone() > 0)
	{
		int x, y;

		SDL_GetMouseState(&x, &y);
		x = ((x + position.x) / 64 * 64) - position.x;
		y = (y - 34 + position.y) / 64 * 64 - position.y + 34;

		SDL_Rect dst = {
			x + 4, y + 4,
			64 - 8, 64 - 8
		};

		SDL_Color col = ZONE_COLORS[getCurrentZone()];
		SDL_SetRenderDrawBlendMode(APP->renderer, SDL_BLENDMODE_BLEND);
		SDL_SetRenderDrawColor(APP->renderer, col.r, col.g, col.b, 128);
		SDL_RenderFillRect(APP->renderer, &dst);
		SDL_SetRenderDrawBlendMode(APP->renderer, SDL_BLENDMODE_NONE);
	}
}

void Grid::drawGrid(const SDL_Rect& container)
{
	SDL_Rect dimensions = {
		0, 0,
		calcX(style.width), calcY(style.height)
	};

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

	SDL_Point tilePos = tileFromMouse(e);
	//MessageBoxA(NULL, (std::to_string(mouse.x) + ", " + std::to_string(mouse.y)).c_str(), NULL, MB_OK);


	if (APP->mouseState & MOUSE_LEFT)
	{
		if (APP->keymap[SDL_SCANCODE_LSHIFT] == true)
		{
			floodFill(tilePos.x, tilePos.y);
		}
		else
		{
			placeTile(tilePos.x, tilePos.y);
		}
	}
	else if (APP->mouseState & MOUSE_MIDDLE)
	{
		removeTile(tilePos.x, tilePos.y, false);
	}
	return true;
}

bool Grid::onDrag(const SDL_Event& e)
{
	static int dragged = 0;
	SDL_Point tilePos = tileFromMouse(e);
	if ((lastTilePlaced.x == tilePos.x) && (lastTilePlaced.y == tilePos.y))
	{
		return true;
	}

	if (APP->mouseState & MOUSE_LEFT)
		placeTile(tilePos.x, tilePos.y);
	else if (APP->mouseState & MOUSE_MIDDLE)
		removeTile(tilePos.x, tilePos.y, false);
}

SDL_Point Grid::tileFromMouse(const SDL_Event& e)
{
	SDL_Point mouse = {
		e.button.x,
		e.button.y
	};

	mouse.x = ((mouse.x + position.x) / 64);
	mouse.y = (mouse.y - 34 + position.y) / 64;

	return mouse;
}

void Grid::changeLayer(int dir)
{
	this->currentLayer += dir;
	if (this->currentLayer < 0)
		this->currentLayer = 0;
	else if (this->currentLayer > 3)
		this->currentLayer = 3;
}

void Grid::changeZone(int dir)
{
	this->currentZone += dir;
	if (this->currentZone < 0)
		this->currentZone = 0;
	else if (this->currentZone > 9)
		this->currentZone = 9;
}

int Grid::getCurrentLayer()
{
	return currentLayer;
}

int Grid::getCurrentZone()
{
	return currentZone;
}

void Grid::placeTile(int x, int y)
{
	if (x < 0 || x >= 512)
		return;
	if (y < 0 || y >= 512)
		return;
	if (getCurrentLayer() != LAYER_GRID)
	{
		map[x][y].set(getCurrentLayer(), APP->selectedTile, APP->selectedTileTexture);
	}
	else
	{
		map[x][y].set(getCurrentLayer(), getCurrentZone(), nullptr);
	}
	lastTilePlaced = { x, y };
}

void Grid::floodFill(int x, int y)
{
	if (x < 0 || x > 255 || y < 0 || y > 255)
		return;
	int floodType = -1;
	switch (getCurrentLayer())
	{
	case LAYER_FLOOR:
		floodType = map[x][y].token.floor;
		break;
	case LAYER_WALLS:
		floodType = map[x][y].token.wallType;
		break;
	case LAYER_CEIL:
		floodType = map[x][y].token.ceiling;
		break;
	case LAYER_GRID:
		floodType = map[x][y].token.zone;
		break;
	}

	std::vector<std::tuple<int, int>> history = std::vector<std::tuple<int, int>>();
	std::vector<std::tuple<int, int>> permanentHistory = std::vector<std::tuple<int, int>>();
	history.push_back(std::tuple<int, int>(x, y));
	while (!history.empty())
	{
		std::tuple<int, int> top = history.back();
		history.pop_back();
		int x = std::get<0>(top),
			y = std::get<1>(top);
		if (floodable(x, y, floodType, history))
		{
			placeTile(x, y);
			permanentHistory.push_back(top);
			if (floodable(x - 1, y, floodType, permanentHistory))
				history.push_back(std::tuple<int, int>(x - 1, y));
			if (floodable(x + 1, y, floodType, permanentHistory))
				history.push_back(std::tuple<int, int>(x + 1, y));
			if (floodable(x, y - 1, floodType, permanentHistory))
				history.push_back(std::tuple<int, int>(x, y - 1));
			if (floodable(x, y + 1, floodType, permanentHistory))
				history.push_back(std::tuple<int, int>(x, y + 1));
		}
	}
}

bool Grid::floodable(int x, int y, int floodType, const std::vector<std::tuple<int, int>>& history)
{
	if (x < 0 || x > 255 || y < 0 || y > 255)
		return false;

	if (std::find(history.begin(), history.end(), std::tuple<int, int>(x, y)) != history.end())
	{
		return false;
	}

	switch (getCurrentLayer())
	{
	case LAYER_FLOOR:
		return map[x][y].token.floor == floodType;
	case LAYER_WALLS:
		return map[x][y].token.wallType == floodType;
	case LAYER_CEIL:
		return map[x][y].token.ceiling == floodType;
	case LAYER_GRID:
		return map[x][y].token.zone == floodType;
	}
	return false;
}

void Grid::removeTile(int x, int y, bool all)
{
	if (x < 0 || x >= 512)
		return;
	if (y < 0 || y >= 512)
		return;
	if (all)
	{
		for (int i = 0; i < 0; i++)
		{
			map[x][y].set(i, 0, nullptr);
		}
	}
	else
	{
		map[x][y].set(getCurrentLayer(), 0, nullptr);
	}
	lastTilePlaced = { x, y };

}