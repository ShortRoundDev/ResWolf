#pragma once
#include <string>

#include "Texture.h"
#include "Model.h"
#include "Shader.h"

namespace ResWolf
{
	class Entity
	{
	public:
		static Model* rect;
		static Shader* shader;
		static void init();
		Entity(int entityNumber, std::string texturePath, char* config, uint16_t x, uint16_t y, float w, float h);
		Entity(int entityNumber, std::string texturePath, char* config, glm::vec3 pos, glm::vec2 scale);
		~Entity();

		glm::vec3 pos;
		glm::vec3 direction;
		glm::vec3 velocity;
		glm::vec2 scale;

		virtual void draw();
		virtual void update();

		Texture* texture;
		char* config;
	};
};