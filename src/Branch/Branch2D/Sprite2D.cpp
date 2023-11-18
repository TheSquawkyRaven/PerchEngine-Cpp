#include "Sprite2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;

Vector2 Sprite2D::GetSize()
{
	if (_Texture == NULL)
	{
		return Vector2();
	}
	Vector2i textureSize = _Texture->GetSize();
	return Vector2(Scale.X * textureSize.X, Scale.Y * textureSize.Y);
}

Vector2 Sprite2D::GetGlobalSize()
{
	if (_Texture == NULL)
	{
		return Vector2();
	}
	Vector2i textureSize = _Texture->GetSize();
	Vector2 scale = GetGlobalScale();
	return Vector2(scale.X * textureSize.X, scale.Y * textureSize.Y);
}

void Sprite2D::SetTexture(shared_ptr<Texture> texture)
{
	_Texture = shared_ptr<Texture>(texture);
}

void Sprite2D::Update()
{
	// Test Update
	//Position.X += 0.01f;
}

void Sprite2D::Draw(SDL_Renderer* renderer)
{
	if (_Texture == NULL)
	{
		return;
	}

	Vector2 position = GetGlobalPosition();
	Vector2 size = GetGlobalSize();
	SDL_Rect* rect = Rect2::CreateSDLRect(&position, &size);

	SDL_RenderCopy(renderer, &_Texture->GetSDLTexture(), NULL, rect);

	delete rect;
}

void Sprite2D::OnDestroy()
{
	_Texture = NULL;
}