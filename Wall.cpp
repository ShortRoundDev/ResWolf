#include "Wall.h"


#include "GraphicsManager.h"

using namespace ResWolf;

Shader* Wall::shader = nullptr;
Model* Wall::model = 0;

void Wall::init()
{
	shader = GRAPHICS->shaders["wall"];

	float box[] = {
		// Front Face
		0, 1, 0, TEX_TL,
		1, 1, 0, TEX_TR,
		0, 0, 0, TEX_BL,

		1, 1, 0, TEX_TR,
		1, 0, 0, TEX_BR,
		0, 0, 0, TEX_BL,
		// Right Face
		1, 1, 0, TEX_TL,
		1, 1, 1, TEX_TR,
		1, 0, 0, TEX_BL,

		1, 1, 1, TEX_TR,
		1, 0, 1, TEX_BR,
		1, 0, 0, TEX_BL,
		// Back Face
		1, 1, 1, TEX_TL,
		0, 1, 1, TEX_TR,
		1, 0, 1, TEX_BL,
		
		0, 1, 1, TEX_TL,
		0, 0, 1, TEX_BR,
		1, 0, 1, TEX_BL,
		// Left Face
		0, 1, 0, TEX_TR,
		0, 0, 0, TEX_BR,
		0, 0, 1, TEX_BL,

		0, 1, 0, TEX_TR,
		0, 0, 1, TEX_BL,
		0, 1, 1, TEX_TL,
		// Top Face
		1, 1, 1, TEX_TR,
		0, 1, 0, TEX_BL,
		0, 1, 1, TEX_TL,

		1, 1, 1, TEX_TR,
		1, 1, 0, TEX_BR,
		0, 1, 0, TEX_BL,

		// Bottom Face
		1, 0, 1, TEX_TR,
		0, 0, 1, TEX_TL,
		1, 0, 0, TEX_BR,

		0, 0, 1, TEX_TL,
		0, 0, 0, TEX_BL,
		1, 0, 0, TEX_BR
	};
	// TODO Upload unit cube
	model = GRAPHICS->assignNamedVertices("Box", box, sizeof(box));
}

Wall::Wall(uint16_t x, uint16_t y, uint16_t floorCode, uint16_t wallCode, uint16_t ceilingCode, bool isDoor, uint8_t lockType, char* message, bool solid) :
	pos((float)x, 0, float(y)),
	floorTexture(GRAPHICS->createTexture("Resources/Textures/Tiles/" + std::to_string(floorCode), std::to_string(floorCode))),
	wallTexture(GRAPHICS->createTexture("Resources/Textures/Tiles/" + std::to_string(wallCode), std::to_string(wallCode))),
	ceilingTexture(GRAPHICS->createTexture("Resources/Textures/Tiles/" + std::to_string(ceilingCode), std::to_string(ceilingCode))),
	isDoor(isDoor),
	lockType(lockType),
	message(message),
	solid(solid),
	isOpen(false),
	openProgress(0.0f)
{

}

void Wall::draw()
{
	// Level must call shader->use() for the wall shader before this point,
	// as well as set the view and project matrices

	shader->setModel(model);
	shader->setTex(wallTexture->image);

	shader->setVec3("offset", pos + glm::vec3(-openProgress, 0, 0));
	shader->setVec3("scale", glm::vec3(1));

	glDrawArrays(GL_TRIANGLES, 0, 6);
}

Wall::~Wall()
{

}