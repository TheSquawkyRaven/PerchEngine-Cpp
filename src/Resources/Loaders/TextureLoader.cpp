#include "TextureLoader.h"

#include "../../Log.h"

using namespace Squawk;

SDL_Surface* Perch::TextureLoader::LoadBMPSurface(SDL_Surface* mainWindowSurface, std::string path)
{
	SDL_Surface* rawSurface = SDL_LoadBMP(path.c_str());
	if (rawSurface == NULL)
	{
		Log::Errorf("Failed to load bmp texture! SDL_ERROR: %s", SDL_GetError());
		return NULL;
	}

	// Optimize
	// Bmp textures are generally 24 bit. This pre-converts the texture to 32 bit (or monitor's bits, in this case the MainWindow's Surface)
	// so SDL won't have to convert 24 bit -> 32 bit every time it is blitted
	SDL_Surface* optimizedSurface = SDL_ConvertSurface(rawSurface, mainWindowSurface->format, 0);
	if (optimizedSurface == NULL)
	{
		Log::Errorf("Failed to optimize bmp texture! SDL_ERROR: %s", SDL_GetError());
		return NULL;
	}

	// Since Converting it creates a new copy, free the raw bmp texture
	SDL_FreeSurface(rawSurface);

	return optimizedSurface;
}


SDL_Surface* Perch::TextureLoader::LoadSurface(SDL_Surface* mainWindowSurface, std::string path)
{
	SDL_Surface* rawSurface = IMG_Load(path.c_str());
	if (rawSurface == NULL)
	{
		Log::Errorf("Failed to load texture! SDL_IMAGE_ERROR: %s", IMG_GetError());
		return NULL;
	}

	// Optimize to 32 bit
	SDL_Surface* optimizedSurface = SDL_ConvertSurface(rawSurface, mainWindowSurface->format, 0);
	if (optimizedSurface == NULL)
	{
		Log::Errorf("Failed to optimize texture! SDL_ERROR: %s", SDL_GetError());
		return NULL;
	}

	// Since Converting it creates a new copy, free the raw bmp texture
	SDL_FreeSurface(rawSurface);

	return optimizedSurface;
}
