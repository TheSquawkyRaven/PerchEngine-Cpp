#include "pch.h"

#include "Sprite2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Sprite2D::SetSpriteColumns(int spriteColumns)
{
	_SpriteColumns = spriteColumns;
	UpdateCutRect();
}
void Sprite2D::SetSpriteRows(int spriteRows)
{
	_SpriteRows = spriteRows;
	UpdateCutRect();
}
void Sprite2D::SetSpriteIndex(int spriteIndex)
{
	_SpriteIndex = spriteIndex;
	UpdateCutRect();
}

void Sprite2D::UpdateCutRect()
{
	if (_SpriteColumns < 1)
	{
		Log::Errorf("_SpriteColumns must not be 0 or negative! Current Value: %d", _SpriteColumns);
		return;
	}
	if (_SpriteRows < 1)
	{
		Log::Errorf("_SpriteRows must not be 0 or negative! Current Value: %d", _SpriteRows);
		return;
	}
	if (_SpriteIndex < 0)
	{
		Log::Errorf("_SpriteIndex must not be negative! Current Value: %d", _SpriteIndex);
		return;
	}
	if (_SpriteIndex >= _SpriteColumns * _SpriteRows)
	{
		Log::Warnf("_SpriteIndex is over the size of %d (%d*%d)! Current Value: %d", _SpriteColumns * _SpriteRows, _SpriteColumns, _SpriteRows, _SpriteIndex);
	}

	shared_ptr<Texture> texture = GetTexture();

	if (texture == NULL)
	{
		return;
	}

	Vector2 size = texture->GetSize();
	size.X = size.X / _SpriteColumns;
	size.Y = size.Y / _SpriteRows;

	Vector2 position;
	int iX = _SpriteIndex % _SpriteRows;
	int iY = _SpriteIndex / _SpriteColumns;

	position.X = size.X * iX;
	position.Y = size.Y * iY;

	_CutRect.SetPosition(position);
	_CutRect.SetSize(size);
}

SDL_RendererFlip Sprite2D::GetSDLFlip() const
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (FlipX)
	{
		flip = SDL_FLIP_HORIZONTAL;
		return flip;
	}
	if (FlipY)
	{
		flip = SDL_FLIP_VERTICAL;
		return flip;
	}
	return flip;
}

shared_ptr<SDL_Point> Sprite2D::GetRotateOrigin()
{
	if (_Texture == NULL)
	{
		return NULL;
	}
	Vector2 rotateOrigin = RotatePivot * _Texture->GetSize();

	return rotateOrigin.GetSDLPoint();
}

Vector2 Sprite2D::GetSize()
{
	return Vector2(Scale.X * _CutRect.GetSize().X, Scale.Y * _CutRect.GetSize().Y);
}

Vector2 Sprite2D::GetGlobalSize()
{
	Vector2 scale = GetGlobalScale();
	return Vector2(scale.X * _CutRect.GetSize().X, scale.Y * _CutRect.GetSize().Y);
}

Rect2 Sprite2D::GetCutRect()
{
	UpdateCutRect();
	return _CutRect;
}

void Sprite2D::SetTexture(shared_ptr<Texture> texture)
{
	_Texture = shared_ptr<Texture>(texture);
	UpdateCutRect();
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
	shared_ptr<SDL_Rect> rect = Rect2::CreateSDLRect(position, size);

	shared_ptr<SDL_Rect> cutRect = _CutRect.GetSDLRect();

	SDL_SetTextureColorMod(_Texture->GetSDLTexture(), _Color.R, _Color.G, _Color.B);
	SDL_SetTextureAlphaMod(_Texture->GetSDLTexture(), _Color.A);
	SDL_RenderCopyEx(renderer, _Texture->GetSDLTexture(), cutRect.get(), rect.get(), Angle, GetRotateOrigin().get(), GetSDLFlip());
}

void Sprite2D::OnDestroy()
{
	_Texture = NULL;
}
