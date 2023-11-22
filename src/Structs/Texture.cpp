#include "Texture.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace Perch;
using namespace Squawk;

Vector2i Texture::GetSize() const
{
	return Size;
}

SDL_Texture* Texture::LoadTexture(SDL_Renderer* renderer, string path)
{
	SDL_Texture* texture = NULL;

	texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == NULL)
	{
		Log::Errorf("Failed to load texture, path: %s! SDL_IMAGE_ERROR: %s", path.c_str(), IMG_GetError());
		return NULL;
	}

	return texture;
}

Texture::Texture(SDL_Texture* sdlTexture)
{
	SDLTexture = unique_ptr<SDL_Texture, SDLTextureDeleter>(sdlTexture);
	SDL_SetTextureBlendMode(SDLTexture.get(), SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(SDLTexture.get(), NULL, NULL, &Size.X, &Size.Y);
}

shared_ptr<Texture> Texture::Create(Engine* engine, string path)
{
	SDL_Texture* sdlTexture = LoadTexture(engine->GetMainWindowRenderer(), path);
	if (sdlTexture == NULL)
	{
		return NULL;
	}

	shared_ptr<Texture> texture = shared_ptr<Texture>(new Texture(sdlTexture));

	return texture;
}
