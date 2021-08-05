#pragma once

#include <string>
#include <stdint.h>

#include "Shader.h"
#include "LevelTokens.h"
#include "Wall.h"
//#include "Entity.h"

namespace ResWolf
{

	/** The status of the level. Used for loading errors */
	enum class LevelStatus
	{
		OK,
		FAILED_FNF,
		FAILED_CORRUPT,
		FAILED_MEM
	};

	/** A level of the game. Contains walls and entities */
	class Level
	{
	public:
		/** Initializes some statically cached things for the level*/
		static void init();

		/** Cached shader for rendering walls */
		static Shader* wallShader;

		/** Loads a level from the given path. If the level fails to load (doesn't exist or malformed or some bug)
		  * then the status field will be set to a status code other than LevelStatus::OK */
		Level(std::string path);
		/** Destroys all data associated with the level (walls, entities, text), but not their underlying assets (textures, models) */
		~Level();

		/** Draws the level, its walls, its characters */
		void draw();

		/** A single array of walls. Loaded from a 2D specification but put into a single array */
		Wall* walls;
		//Entity** entities;

		/** The current load status of the level */
		LevelStatus status;

		/** Returns the wall at the given x y location, doing the math inline to access it from a single array */
		inline Wall* wallAt(int x, int y);

		/** Width and height of the level, in # of tiles*/
		int width, height;

	private:
		/** Fixes the pointer offsets in the level token. Pointers are relative in the file and must be made absolute upon loading. */
		bool fixPointers(LevelToken* levelToken);
		/** The raw level file. Used to build the actual walls. Kept around in memory because it's
		  * easier than deleting it and moving all the data elsewhere */
		LevelToken* levelToken;

		/** Reads player pos, walls, and entities */ // TODO: Handle player position and entities
		bool parseLevelToken();
	};
}