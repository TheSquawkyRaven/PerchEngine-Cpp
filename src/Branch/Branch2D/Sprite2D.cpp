#include "pch.h"

#include "Sprite2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Sprite2D::SetSpriteColumns(int spriteColumns)
{
	this->spriteColumns = spriteColumns;
	UpdateCutRect();
}
void Sprite2D::SetSpriteRows(int spriteRows)
{
	this->spriteRows = spriteRows;
	UpdateCutRect();
}
void Sprite2D::SetSpriteIndex(int spriteIndex)
{
	this->spriteIndex = spriteIndex;
	UpdateCutRect();
}

void Sprite2D::SetTexture(shared_ptr<Texture> texture)
{
	this->texture = texture;
	UpdateCutRect();
}

void Sprite2D::UpdateCutRect()
{
	if (spriteColumns < 1)
	{
		Log::Errorf("spriteColumns must not be 0 or negative! Current Value: %d", spriteColumns);
		return;
	}
	if (spriteRows < 1)
	{
		Log::Errorf("spriteRows must not be 0 or negative! Current Value: %d", spriteRows);
		return;
	}
	if (spriteIndex < 0)
	{
		Log::Errorf("spriteIndex must not be negative! Current Value: %d", spriteIndex);
		return;
	}
	if (spriteIndex >= spriteColumns * spriteRows)
	{
		Log::Warnf("spriteIndex is over the size of %d (%d*%d)! Current Value: %d", spriteColumns * spriteRows, spriteColumns, spriteRows, spriteIndex);
	}

	if (texture == nullptr)
	{
		return;
	}

	Vector2 size = texture->GetSize();
	size.x = size.x / spriteColumns;
	size.y = size.y / spriteRows;

	Vector2 position;
	int iX = spriteIndex % spriteColumns;
	int iY = spriteIndex / spriteColumns;

	position.x = size.x * iX;
	position.y = size.y * iY;

	cutRect.SetPosition(position);
	cutRect.SetSize(size);
}

SDL_RendererFlip Sprite2D::GetSDLFlip() const
{
	SDL_RendererFlip flip = SDL_FLIP_NONE;
	if (flipX)
	{
		flip = SDL_FLIP_HORIZONTAL;
		return flip;
	}
	if (flipY)
	{
		flip = SDL_FLIP_VERTICAL;
		return flip;
	}
	return flip;
}

shared_ptr<SDL_Point> Sprite2D::GetRotateOrigin()
{
	if (texture == nullptr)
	{
		return nullptr;
	}
	Vector2 rotateOrigin = rotatePivot * GetSize();

	return rotateOrigin.GetSDLPoint();
}

Vector2 Sprite2D::GetPositionPivotOrigin()
{
	if (texture == nullptr)
	{
		return Vector2();
	}
	Vector2 positionOrigin = positionPivot * GetSize();
	return positionOrigin;
}

void Sprite2D::Update()
{
	// Test Update
	//Position.X += 0.01f;
}

void Sprite2D::Draw(SDL_Renderer* renderer)
{
	if (texture == nullptr)
	{
		return;
	}

	Vector2 position = GetGlobalPosition() - GetPositionPivotOrigin();
	Vector2 size = GetGlobalSize();
	shared_ptr<SDL_Rect> rect = Rect2::CreateSDLRect(position, size);

	shared_ptr<SDL_Rect> cutSDLRect = cutRect.GetSDLRect();

	SDL_SetTextureColorMod(texture->GetSDLTexture(), color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture->GetSDLTexture(), color.a);
	SDL_RenderCopyEx(renderer, texture->GetSDLTexture(), cutSDLRect.get(), rect.get(), angle, GetRotateOrigin().get(), GetSDLFlip());
}

void Sprite2D::OnDestroy()
{
	texture = nullptr;
}

Vector2 Sprite2D::GetSize()
{
	return Vector2(scale.x * cutRect.GetSize().x, scale.y * cutRect.GetSize().y);
}

Vector2 Sprite2D::GetGlobalSize()
{
	Vector2 scale = GetGlobalScale();
	return Vector2(scale.x * cutRect.GetSize().x, scale.y * cutRect.GetSize().y);
}

Rect2 Sprite2D::GetGlobalRect()
{
	Vector2 position = GetGlobalPosition() - GetPositionPivotOrigin();
	Vector2 size = GetGlobalSize();
	return Rect2(position, size);
}

Rect2 Sprite2D::GetCutRect()
{
	UpdateCutRect();
	return cutRect;
}
