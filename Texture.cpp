#include "Texture.h"

#include "GraphicsManager.h"

using namespace ResWolf;

Texture::Texture(std::string path):
	image(0),
	w(0),
	h(0)
{
	int _image = GRAPHICS->uploadTexture(path, &w, &h);
	if (_image == 0)
	{
		image = GRAPHICS->notFound->image;
		w = GRAPHICS->notFound->w;
		h = GRAPHICS->notFound->h;
	}
	else
	{
		image = _image;
	}
}

Texture::~Texture()
{

}
