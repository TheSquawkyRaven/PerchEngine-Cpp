#include "pch.h"

#include "Audio.h"

#include "../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Audio::SetClip(shared_ptr<Clip> clip)
{
	this->clip = clip;
}

void Audio::OnDestroy()
{
	Branch::OnDestroy();
	clip = nullptr;
}

void Audio::Play()
{
	// TODO Audio channels
	// Channels support halt, pause, resume
	Mix_PlayChannel(-1, clip->GetSDLMixChunk(), 0);
}

void Audio::Stop()
{
	Mix_HaltChannel(-1);
}
