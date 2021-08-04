#pragma once

#include <stdint.h>

#include "Model.h"
#include "Shader.h"
#include "Texture.h"

#include "glm/glm.hpp"

namespace ResWolf
{
	class Wall
	{
	public:

		static Shader* shader;
		static Model* model;

		static void init();

		Wall(uint16_t x, uint16_t y, uint16_t floorCode, uint16_t wallCode, uint16_t ceilingCode, bool isDoor, uint8_t lockType, char* message, bool solid);
		~Wall();

		Texture* floorTexture;
		Texture* wallTexture;
		Texture* ceilingTexture;

		glm::vec3 pos;
		bool isDoor;
		uint8_t lockType;
		char* message;

		bool solid;

		float openProgress;
		bool isOpen;

		void draw();
		void update();
		bool tryOpen(uint8_t playerKeys);
		void open();
	};
}