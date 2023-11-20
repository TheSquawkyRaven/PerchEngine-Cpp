#include "Viewport2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Viewport2D::Update(Engine* engine)
{
	engine->SimulateUseViewport(_Viewport);
}

void Viewport2D::UpdateOut(Engine* engine)
{
	engine->SimulateUnuseViewport(_Viewport);
}

void Viewport2D::Draw(Engine* engine, SDL_Renderer* renderer)
{
	engine->UseViewport(renderer, _Viewport);
}

void Viewport2D::DrawOut(Engine* engine, SDL_Renderer* renderer)
{
	engine->UnuseViewport(renderer, _Viewport);
}

