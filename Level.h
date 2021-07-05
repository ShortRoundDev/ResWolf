#pragma once

#include <string>
#include <stdint.h>

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
		ResWolf::LevelHeader* header;
	};
}