

#include "Texture.h"

#include "../Engine.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace Perch;
using namespace Squawk;


Texture::Texture(SDL_Texture* sdlTexture)
{
	this->sdlTexture = unique_ptr<SDL_Texture, SDLTextureDeleter>(sdlTexture);
}

Vector2i Texture::GetSize() const
{
	return size;
}

shared_ptr<Texture> Texture::Create(Engine* engine, string path)
{
	shared_ptr<Texture> texture = engine->GetResource()->TryGetLoadedTexture(path);
	if (texture)
	{
		return texture;
	}

	SDLRenderer* sdlRenderer = dynamic_cast<SDLRenderer*>(engine->GetMainWindowRenderer());
	if (sdlRenderer == nullptr)
	{
		Log::Error("Texture loading does not support non SDL_Renderer rendering yet!");
		return nullptr;
	}

	Texture* text = sdlRenderer->LoadTexture(path.c_str());
	if (text == nullptr)
	{
		return nullptr;
	}

	texture = shared_ptr<Texture>(text);

	engine->GetResource()->AddLoadedTexture(path, weak_ptr<Texture>(texture));

	return texture;
}

shared_ptr<Texture> Texture::Create(Engine* engine, std::shared_ptr<Font> font, std::string text, int fontSize, Color color)
{
	if (text.length() == 0)
	{
		return nullptr;
	}

	SDLRenderer* sdlRenderer = dynamic_cast<SDLRenderer*>(engine->GetMainWindowRenderer());
	if (sdlRenderer == nullptr)
	{
		Log::Error("Texture loading for font does not support non SDL_Renderer rendering yet!");
		return nullptr;
	}

	font->SetFontSize(fontSize);
	Texture* texture = sdlRenderer->LoadFontTexture(font.get(), text.c_str(), &color);
	if (texture == nullptr)
	{
		return nullptr;
	}

	shared_ptr<Texture> textureShared(texture);

	return textureShared;
}
