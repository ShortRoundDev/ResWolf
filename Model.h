#pragma once

#include "glad/glad.h"

namespace ResWolf
{
	/** Represents a vertex mesh */
	class Model
	{
	public:
		/** creates the model simply from a provided VAO.
		  * Sets the Model::size variable to the provided `size` in the constructor divided by 5,
		  * since there are 5 floats per vertex, 5 floats = 1 vertex. This may change if bones are added later */
		Model(GLuint vao, size_t size);
		~Model();

		/** Vertex array object */
		GLuint vao;
		/** size of the vao, in # of vertices */
		size_t size;
	};
}