#include "Viewport2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;

void Viewport2D::Draw(SDL_Renderer* renderer)
{
	SDL_Rect* sdlRect = _ViewportRect.GetSDLRect();
	SDL_RenderSetViewport(renderer, sdlRect);
}
