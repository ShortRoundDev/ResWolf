#include "Level.h"

#include <iostream>

#include "FileHandling.h"
#include "Logging.h"

#define _USE_MATH_DEFINES
#include <math.h>

#include "Wall.h"

#include "GraphicsManager.h"
#include "GameManager.h"
#include "UIManager.h"

#include "EntityDef.h"

using namespace ResWolf;

#pragma region Public

Shader* Level::wallShader;
Shader* Level::entityShader;

void Level::init()
{
	Wall::init();
	wallShader = GRAPHICS->shaders["wall"];

	Entity::init();
	entityShader = GRAPHICS->shaders["entity"];
}

Level::Level(std::string path) :
	levelToken(NULL),
	width(0),
	height(0),
	totalEntities(0),
	entities(NULL),
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

	totalEntities = levelToken->totalEntities;

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
	static float progress = 0.0f;

	// TODO, change this to (visible) area around player
	if (width <= 0 || height <= 0 || walls == NULL)
		return;

	wallShader->use();

	auto lightPos = glm::vec3(3.0f + cos(progress) * 0.5f, 0.5f, 3.0f + sin(progress) * 0.5f);

	wallShader->setVec3("lightPos", lightPos);
	wallShader->setVec3("lightColor", glm::vec3(cos(progress), sin(progress), cos(progress + M_PI / 6)));
	wallShader->setMat4("view", GRAPHICS->camera->view);
	wallShader->setMat4("projection", GRAPHICS->camera->projection);
	wallShader->setVec3("playerPos", GRAPHICS->camera->cameraPos);
	wallShader->setVec3("scale", glm::vec3(1.0f));

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			wallAt(x, y)->draw();
		}
	}

	progress += 0.03f;

	entityShader->use();
	entityShader->setModel(Entity::rect);
	entityShader->setMat4("view", GRAPHICS->camera->view);
	entityShader->setMat4("projection", GRAPHICS->camera->projection);
	entityShader->setVec3("playerPos", GRAPHICS->camera->cameraPos);
	entityShader->setVec2("scale", glm::vec2(1.0f));
	entityShader->setVec3("lightPos", lightPos);
	for (uint64_t i = 0; i < totalEntities; i++)
	{
		entities[i]->draw();

	}
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	UI_MGR->drawText("CameraPos: " + vec3ToString(GRAPHICS->camera->cameraPos), 16, 64, 128, 128);
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

	// ----- Walls ----- //
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

	// ----- Entities ----- //
	if (totalEntities == 0)
		return true;

	auto entityTokenCursor = levelToken->entities;

	entities = (Entity**)calloc(totalEntities, sizeof(Entity*));
	if (entities == NULL)
	{
		status = LevelStatus::FAILED_MEM;
		return false;
	}
	Entity** cursor = entities;
	for (uint64_t i = 0; i < totalEntities; i++, cursor++, entityTokenCursor++)
	{
		*cursor = createEntity(
			entityTokenCursor->entityId,
			entityTokenCursor->x,
			entityTokenCursor->y,
			entityTokenCursor->config
		);
	}
	return true;
}

inline Wall* Level::wallAt(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return nullptr;
	return walls + ((y * width) + x);
}


#pragma endregion