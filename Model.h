#pragma once

#include "glad/glad.h"

namespace ResWolf
{
	class Model
	{
	public:
		Model(GLuint vao, size_t size);
		~Model();

		GLuint vao;
		size_t size;
	};
}