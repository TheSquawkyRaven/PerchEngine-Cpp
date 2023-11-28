#include "pch.h"

#include "BorderedRectangle2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void BorderedRectangle2D::Draw(SDL_Renderer* renderer)
{
	Vector2 position = GetRectGlobalPosition() - Vector2(borderSize);
	Vector2 size = GetRectSize() + Vector2(borderSize * 2);

	shared_ptr<SDL_Rect> rect = Rect2::CreateSDLRect(position, size);

	SDL_SetRenderDrawColor(renderer, borderColor.r, borderColor.g, borderColor.b, borderColor.a);
	SDL_RenderFillRect(renderer, rect.get());

	// Draw base rectangle
	Rectangle2D::Draw(renderer);
}
