#include "MapTile.h"

MapTile::MapTile(int tileNum, Texture* tileTexture)
{
	token.wallType = tileNum;
	token.message = NULL;
	// to do: automatically make something a door/locked

	texture = tileTexture;
}

MapTile::~MapTile()
{

}