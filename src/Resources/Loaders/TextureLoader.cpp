#include "TextureLoader.h"

#include "../../Log.h"

using namespace Squawk;

SDL_Texture* Perch::TextureLoader::LoadTexture(SDL_Renderer* renderer, std::string path)
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
