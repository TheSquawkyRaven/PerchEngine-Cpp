

#include "ScrollingSprite2D.h"
#include "math.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void ScrollingSprite2D::Draw(Renderer* renderer)
{
	if (texture == nullptr)
	{
		return;
	}

	Vector2 size = GetGlobalSize();
	float scrollLimit = isHorizontal ? size.x : size.y;
	float relativeScroll = fmodf(scroll, scrollLimit);
	//Log::Printf("%f", scroll);
	Vector2 position = GetGlobalPosition() - GetPositionPivotOrigin();
	if (isHorizontal)
	{
		position.x += relativeScroll;
	}
	else
	{
		position.y += relativeScroll;
	}
	rect.SetPosition(position);
	rect.SetSize(size);

	Vector2 rotateOrigin = GetRotateOrigin();

	renderer->DrawTexture(texture.get(), &color,
		&cutRect, &rect,
		angle, &rotateOrigin,
		flipX, flipY);

	for (int i = 1; i <= tileTexture; i++)
	{
		Vector2 beforePos = position;
		Vector2 afterPos = position;
		if (isHorizontal)
		{
			beforePos.x -= i * size.x;
			afterPos.x += i * size.x;
		}
		else
		{
			beforePos.y += i * size.y;
			afterPos.y -= i * size.y;
		}


		rect.SetPosition(beforePos);
		renderer->DrawTexture(texture.get(), &color,
			&cutRect, &rect,
			angle, &rotateOrigin,
			flipX, flipY);

		rect.SetPosition(afterPos);
		renderer->DrawTexture(texture.get(), &color,
			&cutRect, &rect,
			angle, &rotateOrigin,
			flipX, flipY);
	}



}
