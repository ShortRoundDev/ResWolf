#pragma once

#include <stdint.h>
namespace ResWolf
{
	// 3 Words
	// Size 24
	/** A token representing a wall. These variables are used to construct the wall. */
	typedef struct _WallToken
	{
		// --- Word 1 ---
		/** The Tile/Texture # of the wall */
		uint16_t wallType;		// 0, 1
		/** Is the wall an openable door? */
		uint8_t isDoor;			// 2
		/** If this is a door, what type of lock? 0 = unlocked door */
		uint8_t lockType;		// 3
		/** The Tile/Texture # of the floor */
		uint16_t floor;			// 4, 5
		/** The Tile/Texture # of the ceiling */
		uint16_t ceiling;		// 6, 7
		// --- Word 2 ---
		/** The Grid # of the tile. Used for some AI stuff. */
		uint8_t grid;
		uint8_t reserved[7];	// 4 - 15	// Reserved for future use
		// --- Word 3 ---
		/** Messages use is defined by the specific tile. Can be any text.
		  * Usually just used for showing a message in the HUD */
		char* message;			// 16 - 22
	} WallToken;

	// 3 Words
	// Size 24
	/** A token representing an entity. These variables are used to construct a new entity.
	  * the entity ID is used by a generated function in EntityDef.cpp to choose the correct entity's constructor. */
	typedef struct _EntityToken
	{
		// --- Word 1 ---
		uint16_t entityId;		// 0, 1
		uint16_t x;				// 2, 3
		uint16_t y;				// 4, 5
		// --- Word 2 ---
		uint8_t reserved[10];	// 6, 7; 8 - 15		// Reserved for future use
		// --- Word 3 ---
		/** config's use is defined by the specific entity. Can be any text */
		char* config;		// 16 - 23	
	} EntityToken;

	// 7 Words
	// Size 56
	/** A token in a map file representing the header of the map. Manually aligned.
	  * Pointers are relative to the file and must be changed to absolute upon loading */
	typedef struct _LevelToken
	{
		// --- Word 1 ---
		/** Watermark to make sure this is the right filetype */
		char waterMark[3];		// 0, 1, 2	// Always "FUK"
		/** Version #, for backward compatibility */
		uint8_t version;		// 3
		/** Width of the map, in # of tiles */
		uint16_t width;			// 4, 5
		/** Height of the map, in # of tiles */
		uint16_t height;		// 6, 7
		
		// --- Word 2 ---
		/** Total # of entities in the map */
		uint64_t totalEntities; // 8  - 15
		
		// --- Word 3 ---
		/** 2D (width x height) map of tiles */
		WallToken* walls;		// 16 - 23
		
		// --- Word 4 ---
		/** Linear array of entities, `totalEntities` long */
		EntityToken* entities;  // 24 - 31
		// --- Words 5 - 7 ---
		uint8_t reserved[24];	// 32 - 55	// Reserved for future use // TODO: Put player position here. Only need 3 bytes (x, y, look)

	} LevelToken;
}