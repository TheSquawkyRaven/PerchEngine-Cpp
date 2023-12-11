#include "pch.h"

#include "../../Squawk/Log.h"
#include "Button2D.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Button2D::OnMouseOver(MouseOverState state)
{
	switch (state)
	{
	case MouseOverState::Hover:
		if (isHeld)
		{
			return;
		}
		Hover();
		break;

	case MouseOverState::Exit:
		if (isHeld)
		{
			return;
		}
		Exit();
		break;

	case MouseOverState::Down:
		isHeld = true;
		Down();
		break;

	case MouseOverState::Up:
		isHeld = false;
		Up();
		break;

	case MouseOverState::Click:
		if (onClick == nullptr)
		{
			return;
		}
		Click();
		onClick();
		break;
	}
}

void Button2D::Hover()
{
	if (swapTexture)
	{
		linkedSprite->SetTexture(hoverTexture);
	}
	else
	{
		linkedSprite->SetSpriteIndex(1);
	}
}

void Button2D::Exit()
{
	if (swapTexture)
	{
		linkedSprite->SetTexture(baseTexture);
	}
	else
	{
		linkedSprite->SetSpriteIndex(0);
	}
}

void Button2D::Down()
{
	if (swapTexture)
	{
		linkedSprite->SetTexture(holdTexture);
	}
	else
	{
		linkedSprite->SetSpriteIndex(2);
	}
}

void Button2D::Up()
{
	if (swapTexture)
	{
		linkedSprite->SetTexture(baseTexture);
	}
	else
	{
		linkedSprite->SetSpriteIndex(0);
	}
}

void Button2D::Click()
{

}

void Button2D::LinkSprite(Sprite2D* sprite)
{
	linkedSprite = sprite;
	swapTexture = false;

	rect.SetSize(sprite->GetSize());
}

void Button2D::LinkSprite(Sprite2D* sprite, std::shared_ptr<Texture> base, std::shared_ptr<Texture> hover, std::shared_ptr<Texture> hold)
{
	LinkSprite(sprite);

	baseTexture = base;
	hoverTexture = hover;
	holdTexture = hold;

	swapTexture = true;
}

void Button2D::OnDestroy()
{
	MouseOver2D::OnDestroy();
	baseTexture = nullptr;
	hoverTexture = nullptr;
	holdTexture = nullptr;
}
