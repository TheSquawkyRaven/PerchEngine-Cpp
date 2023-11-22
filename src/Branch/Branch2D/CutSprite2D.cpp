#include "CutSprite2D.h"

#include "../../Log.h"
#include "../../Structs/Color.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void CutSprite2D::SetSpriteColumns(int spriteColumns)
{
	_SpriteColumns = spriteColumns;
	UpdateCutRect();
}
void CutSprite2D::SetSpriteRows(int spriteRows)
{
	_SpriteRows = spriteRows;
	UpdateCutRect();
}
void CutSprite2D::SetSpriteIndex(int spriteIndex)
{
	_SpriteIndex = spriteIndex;
	UpdateCutRect();
}

void CutSprite2D::UpdateCutRect()
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

CutSprite2D::CutSprite2D()
{
}

void CutSprite2D::SetTexture(shared_ptr<Texture> texture)
{
	Sprite2D::SetTexture(texture);
	UpdateCutRect();

}

Vector2 CutSprite2D::GetSize()
{
	return Vector2(Scale.X * _CutRect.GetSize().X, Scale.Y * _CutRect.GetSize().Y);
}

Vector2 CutSprite2D::GetGlobalSize()
{
	Vector2 scale = GetGlobalScale();
	return Vector2(scale.X * _CutRect.GetSize().X, scale.Y * _CutRect.GetSize().Y);
}

Rect2 CutSprite2D::GetCutRect()
{
	UpdateCutRect();
	return _CutRect;
}

void CutSprite2D::Draw(Engine* engine, SDL_Renderer* renderer)
{
	shared_ptr<Texture> texture = GetTexture();
	if (texture == NULL)
	{
		return;
	}

	Vector2 position = GetGlobalPosition();
	Vector2 size = GetGlobalSize();
	shared_ptr<SDL_Rect> rect = Rect2::CreateSDLRect(position, size);
	
	shared_ptr<SDL_Rect> cutRect = _CutRect.GetSDLRect();
	Vector2 rotateOrigin = RotatePivot * texture->GetSize();
	
	Color color = GetColor();
	SDL_SetTextureColorMod(texture->GetSDLTexture(), color.R, color.G, color.B);
	SDL_SetTextureAlphaMod(texture->GetSDLTexture(), color.A);
	SDL_RenderCopyEx(renderer, texture->GetSDLTexture(), cutRect.get(), rect.get(), Angle, GetRotateOrigin().get(), GetSDLFlip());
}
