#include "pch.h"

#include "Collider2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Collider2D::_OnCollision(Collider2D* collider)
{
	OnCollision(collider);
	if (script != nullptr)
	{
		script->OnCollision2D(collider);
	}
}

void Collider2D::CollisionUpdate()
{
	// Prevent collision when engine is paused
	// TODO move to Physics2D refer Engine's colliderStack
	if (engine->timeScale == 0.0f)
	{
		return;
	}
	for (Collider2D* collider : engine->colliderStack)
	{
		if (DoesCollideWith(collider))
		{
			_OnCollision(collider);
			collider->_OnCollision(this);
		}
	}
	engine->colliderStack.insert(this);
}

void Collider2D::PhysicsUpdate()
{

}

void Collider2D::Draw(SDL_Renderer* renderer)
{
	if (!engine->DoShowDebug())
	{
		return;
	}

	Color color = Color::Cyan();
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

	float l, t, r, b;
	GetAABB(l, t, r, b);

	SDL_RenderDrawLine(renderer, l, b, l, t);
	SDL_RenderDrawLine(renderer, l, t, r, t);
	SDL_RenderDrawLine(renderer, r, t, r, b);
	SDL_RenderDrawLine(renderer, r, b, l, b);
}

void Collider2D::OnCollision(Collider2D* collider)
{

}

bool Collider2D::DoesCollideWith(Collider2D* collider)
{
	float al, at, ar, ab;
	float bl, bt, br, bb;
	GetAABB(al, at, ar, ab);
	collider->GetAABB(bl, bt, br, bb);

	// A Left >= B Right
	if (al >= br)
	{
		return false;
	}
	// A Right <= B Left
	if (ar <= bl)
	{
		return false;
	}
	// A Top >= B Bottom
	if (at >= bb)
	{
		return false;
	}
	// A Bottom <= B Right
	if (ab <= bt)
	{
		return false;
	}

	return true;
}

void Collider2D::GetAABB(float& left, float& top, float& right, float& bottom)
{
	Vector2 position = GetGlobalPosition();
	Vector2 scale = GetGlobalScale();

	Vector2 rectPos = rect.GetPosition();
	Vector2 rectSize = rect.GetSize();

	Vector2 pos = position + rectPos;
	Vector2 size = rectSize * scale;

	left = pos.x;
	top = pos.y;
	right = pos.x + size.x;
	bottom = pos.y + size.y;
}
