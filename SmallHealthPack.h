#pragma once

#include "Entity.h"

namespace ResWolf
{
	class SmallHealthPack : public Entity
	{
	public:
		SmallHealthPack(int id, uint16_t x, uint16_t y, char* config);
	};
}