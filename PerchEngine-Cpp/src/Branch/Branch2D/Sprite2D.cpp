

#include "Sprite2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void Sprite2D::SetTexture(shared_ptr<Texture> texture)
{
	this->texture = texture;
	UpdateCutRect();
}

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

Vector2 Sprite2D::GetRotateOrigin()
{
	if (texture == nullptr)
	{
		return Vector2();
	}
	Vector2 rotateOrigin = rotatePivot * GetSize();

	return rotateOrigin;
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

void Sprite2D::SetupDraw(Renderer* renderer)
{
	SetupDefaultDrawOrder(renderer);
}

void Sprite2D::Draw(Renderer* renderer)
{
	if (texture == nullptr)
	{
		return;
	}

	Vector2 position = GetGlobalPosition() - GetPositionPivotOrigin();
	Vector2 size = GetGlobalSize();
	rect.SetPosition(position);
	rect.SetSize(size);

	Vector2 rotateOrigin = GetRotateOrigin();

	renderer->DrawTexture(texture.get(), &color,
		&cutRect, &rect,
		angle, &rotateOrigin,
		flipX, flipY);
}

void Sprite2D::OnDestroy()
{
	Branch2D::OnDestroy();
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
