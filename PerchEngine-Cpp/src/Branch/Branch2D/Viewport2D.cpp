#include "pch.h"

#include "Viewport2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Viewport2D::Update()
{
	engine->SimulateUseViewport(viewport.get());
}

void Viewport2D::UpdateOut()
{
	engine->SimulateUnuseViewport(viewport.get());
}

// TODO Set proper viewport drawing with new renderer system
void Viewport2D::Draw(Renderer* renderer)
{
	//engine->UseViewport(renderer, viewport.get());
}

//void Viewport2D::DrawOut(Renderer* renderer)
//{
//	//engine->UnuseViewport(renderer, viewport.get());
//}

