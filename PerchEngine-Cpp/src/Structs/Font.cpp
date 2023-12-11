#include "pch.h"

#include "Font.h"

#include "../Engine.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace Perch;
using namespace Squawk;


TTF_Font* Font::LoadTTF(string path)
{
	TTF_Font* ttfFont = TTF_OpenFont(path.c_str(), 32);
	
	if (ttfFont == nullptr)
	{
		Log::Errorf("Failed to load ttf text, path: %s! SDL_TTF_ERROR: %s", path.c_str(), TTF_GetError());
		return nullptr;
	}

	return ttfFont;
}

Font::Font(TTF_Font* sdlFont)
{
	this->sdlFont = unique_ptr<TTF_Font, SDLFontDeleter>(sdlFont);
}

shared_ptr<Font> Font::Create(Engine* engine, string path)
{
	shared_ptr<Font> font = engine->GetResource()->TryGetLoadedFont(path);
	if (font)
	{
		return font;
	}

	TTF_Font* sdlFont = LoadTTF(path);
	if (sdlFont == nullptr)
	{
		return nullptr;
	}

	font = shared_ptr<Font>(new Font(sdlFont));
	engine->GetResource()->AddLoadedFont(path, weak_ptr<Font>(font));

	return font;
}

void Font::SetFontSize(int fontSize)
{
	TTF_SetFontSize(sdlFont.get(), fontSize);
}
