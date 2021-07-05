#pragma once

#include <string>
#include <stdint.h>

#include "LevelTokens.h"

namespace ResWolf
{
	typedef struct _LevelHeader
	{
		uint8_t version;
	} _LevelHeader;

	class Level
	{
	public:
		Level(std::string path);
		~Level();
	private:
		bool fixPointers(LevelToken* levelToken);
		LevelToken* levelToken;
	};
}