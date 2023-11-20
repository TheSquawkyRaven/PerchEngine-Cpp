#include "BorderedRectangle2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void BorderedRectangle2D::Draw(Engine* engine, SDL_Renderer* renderer)
{
	Vector2 position = GetRectGlobalPosition() - Vector2(BorderSize);
	Vector2 size = GetRectSize() + Vector2(BorderSize * 2);

	SDL_Rect* rect = Rect2::CreateSDLRect(&position, &size);

	SDL_SetRenderDrawColor(renderer, 0xff, 0xff, 0x00, 0xff);
	SDL_RenderFillRect(renderer, rect);

	// Draw base rectangle
	Rectangle2D::Draw(engine, renderer);

	delete rect;
}
