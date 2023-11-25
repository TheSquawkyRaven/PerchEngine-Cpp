#include "pch.h"

#include "Viewport2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Viewport2D::Update()
{
	EngineRef->SimulateUseViewport(_Viewport);
}

void Viewport2D::UpdateOut()
{
	EngineRef->SimulateUnuseViewport(_Viewport);
}

void Viewport2D::Draw(SDL_Renderer* renderer)
{
	EngineRef->UseViewport(renderer, _Viewport);
}

void Viewport2D::DrawOut(SDL_Renderer* renderer)
{
	EngineRef->UnuseViewport(renderer, _Viewport);
}

