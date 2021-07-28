#include "Texture.h"

#include "GraphicsManager.h"

using namespace ResWolf;

Texture::Texture(std::string path):
	image(0),
	w(0),
	h(0)
{
	image = GRAPHICS->uploadTexture(path, &w, &h);
}

Texture::~Texture()
{

}
