#include "pch.h"

#include "Script.h"

#include "../Squawk/Log.h"
#include "Branch.h"
#include <cassert>

using namespace std;
using namespace Perch;
using namespace Squawk;

Script::Script(Engine* engine)
{
	this->engine = engine;
}

void Script::Init()
{}

void Script::Ready()
{}

void Script::Update()
{}

void Script::PhysicsUpdate()
{}

void Script::Draw(Renderer* renderer)
{}

void Script::OnDestroy()
{}

void Script::OnCollision2D(Collider2D* collider)
{}
