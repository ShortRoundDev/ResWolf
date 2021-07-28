#include "Level.h"

#include "FileHandling.h"
#include "Logging.h"

#include <iostream>

using namespace ResWolf;

#pragma region Public

Level::Level(std::string path) :
	levelToken(NULL)
{
	char* data = NULL;
	size_t levelSize = 0;
	int err = ReadBinaryFile(path, &data, &levelSize);

	if (err)
	{
		SimpleError("Couldn't load level '" + path + "'.\nGot " + std::to_string(err));
		return;
	}

	levelToken = (LevelToken*)data;
	fixPointers(levelToken);
}

Level::~Level()
{
	if (levelToken != NULL)
	{
		free(levelToken);
		levelToken = NULL;
	}
}

#pragma endregion

#pragma region Private

bool Level::fixPointers(LevelToken* levelToken)
{
	if (levelToken->walls == NULL)
	{
		SimpleError("Malformed level header. Walls == NULL!");
		return false;
	}
	uint64_t offset = (uint64_t)levelToken;

	levelToken->walls = (WallToken*)(((uint8_t*)levelToken->walls) + offset);
	for (int y = 0; y < levelToken->height; y++)
	{
		for (int x = 0; x < levelToken->width; x++)
		{
			int idx = x + (y * levelToken->width);
			if (levelToken->walls[idx].message != NULL)
			{
				levelToken->walls[idx].message += offset;
			}
		}
	}

	if (levelToken->totalEntities == 0)
	{
		// technically a level doesn't need entities. Boring level though
		return true;
	}

	levelToken->entities = (EntityToken*)(((uint8_t*)levelToken->entities) + offset);
	for (int i = 0; i < levelToken->totalEntities; i++)
	{
		if (levelToken->entities[i].config != NULL)
		{
			levelToken->entities[i].config += offset;
		}
	}

	return true;
}

#pragma endregion