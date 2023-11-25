#include "pch.h"

#include "Script.h"

#include "Log.h"
#include "Branch/Branch.h"
#include <cassert>

using namespace std;
using namespace Perch;
using namespace Squawk;

shared_ptr<Script> Script::GetScript(Script* script)
{
	return std::shared_ptr<Script>(script);
}

shared_ptr<Script> Script::GetScript()
{
	return GetScript(this);
}

void Script::Init(Engine* engine)
{}

void Script::Ready(Engine* engine)
{}

void Script::Update(Engine* engine)
{}

void Script::PhysicsUpdate(Engine * engine)
{}

void Script::Draw(Engine* engine, SDL_Renderer * renderer)
{}

void Script::OnDestroy(Engine* engine)
{}
