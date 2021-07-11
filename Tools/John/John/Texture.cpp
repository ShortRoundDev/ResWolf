#include "Texture.h"
#include "App.h"

#include "SDL_image.h"

_Success_(return);
bool Texture::tryLoad(_In_ std::string path, _Out_ Texture** texture)
{
	*texture = NULL;
	SDL_Texture* sdlTexture = IMG_LoadTexture(APP->renderer, path.c_str());
	if(sdlTexture == NULL)
		return false;

	*texture = new Texture(sdlTexture);
	return true;
}

Texture::Texture(SDL_Texture* texture)
{
	this->texture = texture;
	int w = 0;
	int h = 0;
	SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	this->src = { 0, 0, w, h };
}

Texture::~Texture()
{
	#pragma message("WARNING! Textures are not being cleaned up right now")
}