#pragma once

#include <cstdint>
#include <string>

#include "glad/glad.h"

namespace ResWolf
{
	class Texture
	{
	public:
		Texture(std::string path);
		~Texture();

		GLuint image;
		int w;
		int h;
	};
}