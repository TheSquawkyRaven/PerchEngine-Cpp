#include "pch.h"

#include "../../Squawk/Log.h"
#include "ButtonUI.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void ButtonUI::SetTextures(shared_ptr<Texture> base, shared_ptr<Texture> hover, shared_ptr<Texture> hold)
{
	baseTexture = base;
	hoverTexture = hover;
	holdTexture = hold;

	texture = baseTexture;
}

void ButtonUI::OnMouseHover()
{
	if (isHeld)
	{
		return;
	}
	texture = hoverTexture;
}

void ButtonUI::OnMouseExit()
{
	if (isHeld)
	{
		return;
	}
	texture = baseTexture;
}

void ButtonUI::OnMouseDown()
{
	texture = holdTexture;
	isHeld = true;
}

void ButtonUI::OnMouseUp()
{
	texture = baseTexture;
	isHeld = false;
}

void ButtonUI::OnMouseClick()
{
	if (onClick == nullptr)
	{
		return;
	}
	onClick();
}

void ButtonUI::Draw(SDL_Renderer* renderer)
{
	if (texture == nullptr)
	{
		return;
	}

	Vector2 position = GetGlobalPosition();
	Vector2 size = GetGlobalSize(texture);
	shared_ptr<SDL_Rect> rect = Rect2::CreateSDLRect(position, size);

	SDL_SetTextureColorMod(texture->GetSDLTexture(), color.r, color.g, color.b);
	SDL_SetTextureAlphaMod(texture->GetSDLTexture(), color.a);
	SDL_RenderCopy(renderer, texture->GetSDLTexture(), nullptr, rect.get());

}

void ButtonUI::OnDestroy()
{
	MouseOverUI::OnDestroy();
	baseTexture = nullptr;
	hoverTexture = nullptr;
	holdTexture = nullptr;
}

Vector2 ButtonUI::GetGlobalSize(shared_ptr<Texture> texture)
{
	Vector2 scale = GetGlobalScale();
	return Vector2(scale.x * texture->GetSize().x, scale.y * texture->GetSize().y);
}
