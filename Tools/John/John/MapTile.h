#pragma once

#include <stdint.h>

#include "Texture.h"

constexpr int LAYER_FLOOR = 0;
constexpr int LAYER_WALLS = 1;
constexpr int LAYER_CEIL  = 2;
constexpr int LAYER_GRID  = 3;

typedef struct _WallToken
{
	// --- Word 1 ---
	uint16_t wallType;		// 0, 1
	uint8_t isDoor;			// 2
	uint8_t lockType;		// 3
	uint16_t floor;			// 4, 5
	uint16_t ceiling;		// 6, 7
	// --- Word 2 ---
	uint8_t zone;
	uint8_t reserved[7];	// 4 - 15	// Reserved for future use
	// --- Word 3 ---
	char* message;			// 16 - 22
} WallToken;

typedef struct _EntityToken
{
	// --- Word 1 ---
	uint16_t entityId;		// 0, 1
	uint16_t x;				// 2, 3
	uint16_t y;				// 4, 5
	// --- Word 2 ---
	uint8_t reserved[10];	// 6, 7; 8 - 15		// Reserved for future use
	// --- Word 3 ---
	char* config;			// 16 - 23
} EntityToken;

class MapTile
{
public:
	MapTile();
	~MapTile();

	void draw(int x, int y);
	void set(int layer, int tileNum, Texture* tileTexture);
	
	Texture* texture[3];
	WallToken token;
	EntityToken* entityToken;
	
};

