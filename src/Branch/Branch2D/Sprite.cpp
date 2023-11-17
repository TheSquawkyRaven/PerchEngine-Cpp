#include "Sprite.h"

#include "../../Log.h"

using namespace Perch;

Vector2 Perch::Sprite::GetSize()
{
	if (_Texture == NULL)
	{
		return NULL;
	}
	Vector2 textureSize = _Texture->GetSize();
	return Vector2(Scale.X * textureSize.X, Scale.Y * textureSize.Y);
}

void Sprite::SetTexture(Texture* texture)
{
	_Texture = texture;
}

void Sprite::Draw(SDL_Surface* MainSurface)
{
	if (_Texture == NULL)
	{
		return;
	}
	Vector2 size = GetSize();
	SDL_Rect* rect = Rect2D::CreateSDLRect(&Position, &size);

	SDL_BlitScaled(&_Texture->GetSDLSurface(), NULL, MainSurface, rect);

	delete rect;
}
