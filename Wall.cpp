#include "Wall.h"


#include "GraphicsManager.h"

using namespace ResWolf;

Shader* Wall::shader = nullptr;
Model* Wall::model = nullptr;
Model* Wall::ceilingPlane = nullptr;
Model* Wall::floorPlane = nullptr;

void Wall::init()
{
	shader = GRAPHICS->shaders["wall"];

	float box[] = {
		// Front Face		0
		0, 1, 0, TEX_TR, 0, 0, -1,
		1, 1, 0, TEX_TL, 0, 0, -1,
		0, 0, 0, TEX_BR, 0, 0, -1,

		1, 1, 0, TEX_TL, 0, 0, -1,
		1, 0, 0, TEX_BL, 0, 0, -1,
		0, 0, 0, TEX_BR, 0, 0, -1,
		// Right Face		6
		1, 1, 0, TEX_TR, 1, 0, 0,
		1, 1, 1, TEX_TL, 1, 0, 0,
		1, 0, 0, TEX_BR, 1, 0, 0,

		1, 1, 1, TEX_TL, 1, 0, 0,
		1, 0, 1, TEX_BL, 1, 0, 0,
		1, 0, 0, TEX_BR, 1, 0, 0,
		// Back Face		12
		1, 1, 1, TEX_TR, 0, 0, 1,
		0, 1, 1, TEX_TL, 0, 0, 1,
		1, 0, 1, TEX_BR, 0, 0, 1,
		
		0, 1, 1, TEX_TL, 0, 0, 1,
		0, 0, 1, TEX_BL, 0, 0, 1,
		1, 0, 1, TEX_BR, 0, 0, 1,
		// Left Face		18
		0, 1, 0, TEX_TL, -1, 0, 0,
		0, 0, 0, TEX_BL, -1, 0, 0,
		0, 0, 1, TEX_BR, -1, 0, 0,

		0, 1, 0, TEX_TL, -1, 0, 0,
		0, 0, 1, TEX_BR, -1, 0, 0,
		0, 1, 1, TEX_TR, -1, 0, 0,
		// Top Face			24
		1, 1, 1, TEX_TL, 0, 1, 0,
		0, 1, 0, TEX_BR, 0, 1, 0,
		0, 1, 1, TEX_TR, 0, 1, 0,

		1, 1, 1, TEX_TL, 0, 1, 0,
		1, 1, 0, TEX_BL, 0, 1, 0,
		0, 1, 0, TEX_BR, 0, 1, 0,

		// Bottom Face		30
		1, 0, 1, TEX_TR, 0, -1, 0,
		0, 0, 1, TEX_TL, 0, -1, 0,
		1, 0, 0, TEX_BR, 0, -1, 0,

		0, 0, 1, TEX_TL, 0, -1, 0,
		0, 0, 0, TEX_BL, 0, -1, 0,
		1, 0, 0, TEX_BR, 0, -1, 0
	};
	model = GRAPHICS->assignNamedVertices("Box", box, sizeof(box));

	float ceilingPlaneMdl[] = {
		0, 1, 0,	1, 0, 0, -1, 0,
		1, 1, 0,	0, 0, 0, -1, 0,
		1, 1, 1,	0, 1, 0, -1, 0,

		0, 1, 0,	1, 0, 0, -1, 0,
		1, 1, 1,	0, 1, 0, -1, 0,
		0, 1, 1,	1, 1, 0, -1, 0
	};

	ceilingPlane = GRAPHICS->assignNamedVertices("CeilingPlane", ceilingPlaneMdl, sizeof(ceilingPlaneMdl));

	float floorPlaneMdl[] = {
		0, 0, 0,	1, 0, 0, 1, 0,
		1, 0, 1,	0, 1, 0, 1, 0,
		1, 0, 0,	0, 0, 0, 1, 0,

		0, 0, 0,	1, 0, 0, 1, 0,
		0, 0, 1,	1, 1, 0, 1, 0,
		1, 0, 1,	0, 1, 0, 1, 0
	};

	floorPlane = GRAPHICS->assignNamedVertices("FloorPlane", floorPlaneMdl, sizeof(floorPlaneMdl));
}

Wall::Wall(uint16_t x, uint16_t y, uint16_t floorCode, uint16_t wallCode, uint16_t ceilingCode, bool isDoor, uint8_t lockType, char* message, bool solid) :
	pos((float)x, 0, float(y)),
	floorTexture(GRAPHICS->createTexture("Resources/Texture/Tiles/" + std::to_string(floorCode) + ".png", std::to_string(floorCode))),
	floorCode(floorCode),
	wallTexture(GRAPHICS->createTexture("Resources/Texture/Tiles/" + std::to_string(wallCode) + ".png", std::to_string(wallCode))),
	wallCode(wallCode),
	ceilingTexture(GRAPHICS->createTexture("Resources/Texture/Tiles/" + std::to_string(ceilingCode) + ".png", std::to_string(ceilingCode))),
	ceilingCode(ceilingCode),
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
	
	// Draw wall
	shader->setVec3("offset", pos + glm::vec3(-openProgress, 0, 0));
	shader->setVec3("scale", glm::vec3(1));

	if (wallCode != 0)
	{
		shader->setModel(model);
		shader->setTex(wallTexture->image);

		glDrawArrays(GL_TRIANGLES, 0, (GLsizei)model->size);
	}

	// Draw ceiling
	shader->setModel(ceilingPlane);
	shader->setTex(ceilingTexture->image);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)ceilingPlane->size);

	shader->setModel(floorPlane);
	shader->setTex(floorTexture->image);
	glDrawArrays(GL_TRIANGLES, 0, (GLsizei)floorPlane->size);
}

Wall::~Wall()
{

}