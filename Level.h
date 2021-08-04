#pragma once

#include <string>
#include <stdint.h>

#include "Shader.h"
#include "LevelTokens.h"
#include "Wall.h"
//#include "Entity.h"

namespace ResWolf
{
	typedef struct _LevelHeader
	{
		uint8_t version;
	} _LevelHeader;

	enum class LevelStatus
	{
		OK,
		FAILED_FNF,
		FAILED_CORRUPT,
		FAILED_MEM
	};

	class Level
	{
	public:
		static void init();

		static Shader* wallShader;

		Level(std::string path);
		~Level();

		void draw();

		Wall* walls;
		//Entity** entities;

		LevelStatus status;

		inline Wall* wallAt(int x, int y);

		int width, height;

	private:
		bool fixPointers(LevelToken* levelToken);
		LevelToken* levelToken;

		bool parseLevelToken();
	};
}