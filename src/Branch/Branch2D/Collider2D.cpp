#include "pch.h"

#include "Collider2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;



void Collider2D::_OnCollision(Collider2D* collider)
{
	OnCollision(collider);
	if (ScriptRef != NULL)
	{
		ScriptRef->OnCollision2D(EngineRef, collider);
	}
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

	Vector2 rectPos = Rect.GetPosition();
	Vector2 rectSize = Rect.GetSize();

	Vector2 pos = position + rectPos;
	Vector2 size = rectSize * scale;

	left = pos.X;
	top = pos.Y;
	right = pos.X + size.X;
	bottom = pos.Y + size.Y;
	
}

Collider2D::Collider2D(Engine* engine) : Branch2D(engine)
{
	
}

void Collider2D::OnCollision(Collider2D* collider)
{

}

void Collider2D::CollisionUpdate()
{
	for (Collider2D* collider : EngineRef->ColliderStack)
	{
		if (DoesCollideWith(collider))
		{
			_OnCollision(collider);
			collider->_OnCollision(this);
		}
	}
	EngineRef->ColliderStack.insert(this);
}

void Collider2D::PhysicsUpdate()
{

}

void Collider2D::Draw(SDL_Renderer* renderer)
{
	return;
	Color color = Color::Cyan();
	SDL_SetRenderDrawColor(renderer, color.R, color.G, color.B, color.A);

	float l, t, r, b;
	GetAABB(l, t, r, b);

	SDL_RenderDrawLine(renderer, l, b, l, t);
	SDL_RenderDrawLine(renderer, l, t, r, t);
	SDL_RenderDrawLine(renderer, r, t, r, b);
	SDL_RenderDrawLine(renderer, r, b, l, b);
}
