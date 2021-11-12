#pragma once

#include "glm/glm.hpp"

namespace ResWolf
{
	typedef struct _RWVertex
	{
		glm::vec3 vertex;
		glm::vec2 texel;
		glm::vec3 normal;
	} RWVertex;
}