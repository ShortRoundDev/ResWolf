#pragma once

#include <cstdint>
#include <string>

#include "glad/glad.h"

namespace ResWolf
{
	/** Utility class for OpenGL textures */
	class Texture
	{
	public:
		/** Uploads the image from the given path to the GPU, stores itself in the GraphicsManager::textures dictionary,
		  * then stores the GLuint representing the resource in itself. Stores width and height (in pixels) as well */
		Texture(std::string path);
		~Texture();

		/** The OpenGL ID of the texture resource */
		GLuint image;
		/** The width of the texture resource */
		int w;
		/** The height of the texture resource */
		int h;
	};
}