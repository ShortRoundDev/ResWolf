#include "SmallHealthPack.h"

using namespace ResWolf;

SmallHealthPack::SmallHealthPack(int id, uint16_t x, uint16_t y, char* config) :
	Entity(id, "Resources/Texture/Items/SmallHealthPack.png", config, x, y, 0.3f, 0.3f)
{

}