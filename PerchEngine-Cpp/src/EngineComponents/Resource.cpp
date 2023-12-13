

#include "Resource.h"

#include "../Squawk/Log.h"

#include "../Structs/Texture.h"
#include "../Structs/Font.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


shared_ptr<Texture> Resource::TryGetLoadedTexture(string path)
{
	weak_ptr<Texture> textureW = loadedTextureMap[path];
	shared_ptr<Texture> texture = textureW.lock();
	if (texture)
	{
		return texture;
	}

	loadedTextureMap.erase(path);
	return nullptr;
}

void Resource::AddLoadedTexture(string path, weak_ptr<Texture> textureW)
{
	loadedTextureMap[path] = textureW;
}

shared_ptr<Font> Resource::TryGetLoadedFont(string path)
{
	weak_ptr<Font> fontW = loadedFontMap[path];
	shared_ptr<Font> font = fontW.lock();
	if (font)
	{
		return font;
	}

	loadedFontMap.erase(path);
	return nullptr;
}

void Resource::AddLoadedFont(string path, weak_ptr<Font> fontW)
{
	loadedFontMap[path] = fontW;
}

shared_ptr<Clip> Resource::TryGetLoadedClip(string path)
{
	weak_ptr<Clip> clipW = loadedClipMap[path];
	shared_ptr<Clip> clip = clipW.lock();
	if (clip)
	{
		return clip;
	}

	loadedClipMap.erase(path);
	return nullptr;
}

void Resource::AddLoadedClip(string path, weak_ptr<Clip> fontW)
{
	loadedClipMap[path] = fontW;
}
