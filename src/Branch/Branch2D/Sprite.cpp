#include "Sprite.h"

#include "../../Log.h"

using namespace Perch;

Vector2 Perch::Sprite::GetSize()
{
	if (_Texture == NULL)
	{
		return Vector2();
	}
	Vector2i textureSize = _Texture->GetSize();
	return Vector2(Scale.X * textureSize.X, Scale.Y * textureSize.Y);
}

void Sprite::SetTexture(std::shared_ptr<Texture> texture)
{
	_Texture = std::shared_ptr<Texture>(texture);
}

void Perch::Sprite::Update()
{
	// Test Update
	//Position.X += 0.01f;
}

void Sprite::Draw(SDL_Renderer* renderer)
{
	if (_Texture == NULL)
	{
		return;
	}
	Vector2 size = GetSize();
	SDL_Rect* rect = Rect2D::CreateSDLRect(&Position, &size);

	SDL_RenderCopy(renderer, &_Texture->GetSDLTexture(), NULL, rect);

	delete rect;
}

void Perch::Sprite::OnDestroy()
{
	_Texture = NULL;
}
