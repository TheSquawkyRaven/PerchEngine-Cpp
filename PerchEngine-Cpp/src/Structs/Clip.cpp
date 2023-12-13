

#include "Clip.h"

#include <iostream>
#include <string>
#include <memory>

using namespace std;
using namespace Perch;
using namespace Squawk;

Mix_Chunk* Clip::LoadMixChunk(string path)
{
	Mix_Chunk* mixChunk = Mix_LoadWAV(path.c_str());
	
	if (mixChunk == nullptr)
	{
		Log::Errorf("Failed to load mix chunk audio, path: %s! SDL_MIX_ERROR: %s", path.c_str(), Mix_GetError());
		return nullptr;
	}

	return mixChunk;
}

Clip::Clip(Mix_Chunk* sdlMixChunk)
{
	this->sdlMixChunk = unique_ptr<Mix_Chunk, SDLClipDeleter>(sdlMixChunk);
}

shared_ptr<Clip> Clip::Create(Engine* engine, string path)
{
	shared_ptr<Clip> clip = engine->GetResource()->TryGetLoadedClip(path);
	if (clip)
	{
		return clip;
	}

	Mix_Chunk* sdlMixChunk = LoadMixChunk(path);
	if (sdlMixChunk == nullptr)
	{
		return nullptr;
	}

	clip = shared_ptr<Clip>(new Clip(sdlMixChunk));
	engine->GetResource()->AddLoadedClip(path, weak_ptr<Clip>(clip));

	return clip;
}
