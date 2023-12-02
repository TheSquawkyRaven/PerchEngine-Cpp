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

void ButtonUI::SetupDraw(Renderer* renderer)
{
	SetupDefaultDrawOrder(renderer);
}

void ButtonUI::Draw(Renderer* renderer)
{
	if (texture == nullptr)
	{
		return;
	}

	Vector2 position = GetGlobalPosition();
	Vector2 size = GetGlobalSize(texture);
	rect.SetPosition(position);
	rect.SetSize(size);

	renderer->DrawTexture(texture.get(), &color, nullptr, &rect);
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
