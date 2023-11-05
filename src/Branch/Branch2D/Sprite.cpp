#include "Sprite.h"

using namespace Perch;

Sprite::Sprite(Texture* texture)
{
	_Texture = std::unique_ptr<Texture>(texture);
}

Sprite* Sprite::Create(Texture* texture)
{
	Sprite* sprite = new Sprite(texture);
	return sprite;
}

void Sprite::Draw(SDL_Surface& MainSurface)
{
	//TODO Change Scale to actual size (Multiply with texture)
	SDL_Rect* rect = Rect2D::CreateSDLRect(&Position, &Scale);

	SDL_BlitScaled(&_Texture->GetSDLSurface(), NULL, &MainSurface, rect);

	delete rect;
}
