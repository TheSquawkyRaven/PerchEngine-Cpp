#include "pch.h"

#include "Font.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace Perch;
using namespace Squawk;

TTF_Font* Font::LoadTTF(string path, int fontSize)
{
	TTF_Font* ttfFont = TTF_OpenFont(path.c_str(), fontSize);
	if (ttfFont == NULL)
	{
		Log::Errorf("Failed to load ttf text, path: %s! SDL_TTF_ERROR: %s", path.c_str(), TTF_GetError());
		return NULL;
	}

	return ttfFont;
}

Font::Font(TTF_Font* sdlFont)
{
	SDLFont = unique_ptr<TTF_Font, SDLFontDeleter>(sdlFont);
}

shared_ptr<Font> Font::Create(Engine* engine, string path, int fontSize)
{
	TTF_Font* sdlFont = LoadTTF(path, fontSize);
	if (sdlFont == NULL)
	{
		return NULL;
	}

	shared_ptr<Font> font = shared_ptr<Font>(new Font(sdlFont));

	return font;
}
