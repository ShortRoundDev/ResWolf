#pragma once

#include <stdint.h>

#include "Texture.h"

typedef struct _WallToken
{
	// --- Word 1 ---
	uint16_t wallType;		// 0, 1
	uint8_t isDoor;			// 2
	uint8_t lockType;		// 3
	// --- Word 1, 2 ---
	uint8_t reserved[12];	// 4 - 15	// Reserved for future use
	// --- Word 3 ---
	char* message;			// 16 - 22
} WallToken;

class MapTile
{
public:
	MapTile(int tileNum, Texture* tileTexture);
	~MapTile();

	void draw(int x, int y);

	Texture* texture;
	WallToken token;

};

