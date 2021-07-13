#pragma once

#include <stdint.h>
namespace ResWolf
{
	// 3 Words
	// Size 24
	typedef struct _WallToken
	{
		// --- Word 1 ---
		uint16_t wallType;		// 0, 1
		uint8_t isDoor;			// 2
		uint8_t lockType;		// 3
		uint16_t floor;			// 4, 5
		uint16_t ceiling;		// 6, 7
		// --- Word 2 ---
		uint8_t grid;
		uint8_t reserved[7];	// 4 - 15	// Reserved for future use
		// --- Word 3 ---
		char* message;			// 16 - 22
	} WallToken;

	// 3 Words
	// Size 24
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

	// 7 Words
	// Size 56
	typedef struct _LevelToken
	{
		// --- Word 1 ---
		char waterMark[3];		// 0, 1, 2	// FUK
		uint8_t version;		// 3
		uint16_t width;			// 4, 5
		uint16_t height;		// 6, 7
		// --- Word 2 ---
		uint64_t totalEntities; // 8  - 15
		// --- Word 3 ---
		WallToken* walls;		// 16 - 23
		// --- Word 4 ---
		EntityToken* entities;  // 24 - 31
		// --- Words 5 - 7 ---
		uint8_t reserved[24];	// 32 - 55	// Reserved for future use

	} LevelToken;
}