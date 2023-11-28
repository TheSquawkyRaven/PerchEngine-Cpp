#include "pch.h"

#include "Texture.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace Perch;
using namespace Squawk;

Vector2i Texture::GetSize() const
{
	return size;
}

SDL_Texture* Texture::LoadTexture(SDL_Renderer* renderer, string path)
{
	SDL_Texture* texture = nullptr;

	texture = IMG_LoadTexture(renderer, path.c_str());
	if (texture == nullptr)
	{
		Log::Errorf("Failed to load texture, path: %s! SDL_IMAGE_ERROR: %s", path.c_str(), IMG_GetError());
		return nullptr;
	}

	return texture;
}

Texture::Texture(SDL_Texture* sdlTexture)
{
	this->sdlTexture = unique_ptr<SDL_Texture, SDLTextureDeleter>(sdlTexture);
	SDL_SetTextureBlendMode(sdlTexture, SDL_BLENDMODE_BLEND);
	SDL_QueryTexture(sdlTexture, nullptr, nullptr, &size.x, &size.y);
}

shared_ptr<Texture> Texture::Create(Engine* engine, string path)
{
	shared_ptr<Texture> texture = engine->GetResource()->TryGetLoadedTexture(path);
	if (texture)
	{
		return texture;
	}

	SDL_Texture* sdlTexture = LoadTexture(engine->GetMainWindowRenderer(), path);
	if (sdlTexture == nullptr)
	{
		return nullptr;
	}

	texture = shared_ptr<Texture>(new Texture(sdlTexture));
	engine->GetResource()->AddLoadedTexture(path, weak_ptr<Texture>(texture));

	return texture;
}

shared_ptr<Texture> Texture::Create(Engine* engine, std::shared_ptr<Font> font, std::string text, int fontSize, Color color)
{
	if (text.length() == 0)
	{
		return nullptr;
	}

	font->SetFontSize(fontSize);
	SDL_Surface* sdlSurface = TTF_RenderText_Solid(font->GetSDLFont(), text.c_str(), color);
	if (sdlSurface == nullptr)
	{
		Log::Errorf("Failed to create surface from font! SDL_TTF_ERROR: %s", TTF_GetError());
		return nullptr;
	}

	SDL_Texture* sdlTexture = SDL_CreateTextureFromSurface(engine->GetMainWindowRenderer(), sdlSurface);
	SDL_FreeSurface(sdlSurface);
	if (sdlTexture == nullptr)
	{
		Log::Errorf("Failed to convert surface to texture! SDL_IMAGE_ERROR: %s", IMG_GetError());
		return nullptr;
	}

	shared_ptr<Texture> texture = shared_ptr<Texture>(new Texture(sdlTexture));

	return texture;
}
