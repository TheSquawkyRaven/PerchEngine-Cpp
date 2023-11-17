#include "Texture.h"

#include "../Log.h"

#include "Loaders/TextureLoader.h"

#include <iostream>
#include <string>

using namespace Perch;
using namespace Squawk;

Vector2 Perch::Texture::GetSize() const
{
	if (SDLSurface == NULL)
	{
		return NULL;
	}
	return Vector2(SDLSurface->w, SDLSurface->h);
}

Perch::Texture::Texture(SDL_Surface* surface)
{
	SDLSurface = std::unique_ptr<SDL_Surface>(surface);

}

Perch::Texture* Perch::Texture::Create(SDL_Surface* mainWindowSurface, std::string path, TextureFileFormat fileFormat)
{

	SDL_Surface* surface = NULL;

	switch (fileFormat)
	{
	case FORMAT_BMP:
		surface = TextureLoader::LoadBMPSurface(mainWindowSurface, path);
		break;
	case FORMAT_PNG:
		surface = TextureLoader::LoadSurface(mainWindowSurface, path);
		break;
	default:
		Log::Error(std::to_string((int)fileFormat).c_str());
		Log::Errorf("Texture file format not supported! Format: %d", fileFormat);
		return NULL;
	}

	Texture* texture = new Texture(surface);

	return texture;
}
