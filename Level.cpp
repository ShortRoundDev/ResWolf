#include "Level.h"

#include <iostream>

#include "FileHandling.h"
#include "Logging.h"

#include "Wall.h"

#include "GraphicsManager.h"
#include "GameManager.h"

using namespace ResWolf;

#pragma region Public

Shader* Level::wallShader;

void Level::init()
{
	Wall::init();
	wallShader = GRAPHICS->shaders["wall"];
}

Level::Level(std::string path) :
	levelToken(NULL),
	width(0),
	height(0),
	walls(NULL)
{
	char* data = NULL;
	size_t levelSize = 0;
	int err = ReadBinaryFile(path, &data, &levelSize);

	if (err)
	{
		status = LevelStatus::FAILED_FNF;
		SimpleError("Couldn't load level '" + path + "'.\nGot " + std::to_string(err));
		return;
	}

	levelToken = (LevelToken*)data;
	if (!fixPointers(levelToken))
	{
		return;
	}

	width = levelToken->width;
	height = levelToken->height;

	parseLevelToken();

	status = LevelStatus::OK;
}

Level::~Level()
{
	if (levelToken != NULL)
	{
		free(levelToken);
		levelToken = NULL;
	}
	if (walls != NULL)
	{
		free(walls);
		walls = NULL;
	}
}

void Level::draw()
{
	// TODO, change this to (visible) area around player
	if (width <= 0 || height <= 0 || walls == NULL)
		return;

	wallShader->use();

	wallShader->setMat4("view", GRAPHICS->camera->view);
	wallShader->setMat4("projection", GRAPHICS->camera->projection);
	wallShader->setVec3("playerPos", GRAPHICS->camera->cameraPos);
	wallShader->setVec3("scale", glm::vec3(1.0f));

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			wallAt(x, y)->draw();
			return;
		}
	}
}

#pragma endregion

#pragma region Private

bool Level::fixPointers(LevelToken* levelToken)
{
	if (levelToken->walls == NULL)
	{
		SimpleError("Malformed level header. Walls == NULL!");
		status = LevelStatus::FAILED_CORRUPT;
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

bool Level::parseLevelToken()
{
	walls = (Wall*)calloc(height * width, sizeof(Wall));
	if (walls == NULL)
	{
		status = LevelStatus::FAILED_MEM;
		return false;
	}

	WallToken* wallToken = levelToken->walls;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++, wallToken++)
		{
			*wallAt(x, y) = Wall(
				x, y,
				wallToken->floor, wallToken->wallType, wallToken->ceiling,
				wallToken->isDoor,
				wallToken->lockType,
				wallToken->message,
				true // todo: solid tile lookup table
			);
		}
	}
}

inline Wall* Level::wallAt(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return nullptr;
	return walls + ((y * width) + x);
}


#pragma endregion