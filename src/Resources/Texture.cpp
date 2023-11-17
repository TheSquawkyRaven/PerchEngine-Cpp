#include "Texture.h"

#include "Loaders/TextureLoader.h"

#include <iostream>
#include <string>

using namespace Perch;
using namespace Squawk;

Vector2i Texture::GetSize() const
{
	return Size;
}

Texture::Texture(SDL_Texture* sdlTexture)
{
	SDLTexture = std::unique_ptr<SDL_Texture, SDLTextureDeleter>(sdlTexture);
	SDL_QueryTexture(SDLTexture.get(), NULL, NULL, &Size.X, &Size.Y);
}

std::shared_ptr<Texture> Texture::Create(Engine* engine, std::string path)
{
	SDL_Texture* sdlTexture = TextureLoader::LoadTexture(engine->GetMainWindowRenderer(), path);
	if (sdlTexture == NULL)
	{
		return NULL;
	}

	std::shared_ptr<Texture> texture = std::shared_ptr<Texture>(new Texture(sdlTexture));

	return texture;
}
