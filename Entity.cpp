#include "Entity.h"

#include "GraphicsManager.h"

using namespace ResWolf;

Model* Entity::rect = nullptr;
Shader* Entity::shader = nullptr;

void Entity::init()
{
	float entityRectVerts[] = {
		-0.5, 1, 0,		0, 0,	0, 0, 1,
		 0.5, 0, 0,		1, 1,	0, 0, 1,
		 0.5, 1, 0,		1, 0,	0, 0, 1,

		-0.5, 1, 0,		0, 0,	0, 0, 1,
		-0.5, 0, 0,		0, 1,	0, 0, 1,
		 0.5, 0, 0,		1, 1,	0, 0, 1
	};

	rect = GRAPHICS->assignNamedVertices("EntityRect", entityRectVerts, sizeof(entityRectVerts));
	shader = GRAPHICS->shaders["entity"];
}

Entity::Entity(int entityNumber, std::string texturePath, char* config, uint16_t x, uint16_t y, float w, float h) :
	Entity(entityNumber, texturePath, config, glm::vec3((float)x, 0, (float)y) + glm::vec3(0.5f, 0, 0.5f), glm::vec2(w, h))
{

}

Entity::Entity(int entityNumber, std::string texturePath, char* config, glm::vec3 pos, glm::vec2 scale) :
	texture(new Texture(texturePath)),
	pos(pos),
	direction(1, 0, 0),
	velocity(0),
	config(config),
	scale(scale)
{

}

Entity::~Entity()
{

}

void Entity::draw()
{
	// Requires Level to use the shader ahead of time
	shader->setTex(texture->image);
	shader->setVec3("offset", pos);
	shader->setVec2("scale", scale);

	glDrawArrays(GL_TRIANGLES, 0, rect->size);
}

void Entity::update()
{

}