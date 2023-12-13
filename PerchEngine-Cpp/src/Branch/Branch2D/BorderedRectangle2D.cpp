

#include "BorderedRectangle2D.h"

#include "../../Squawk/Log.h"

using namespace std;
using namespace Perch;
using namespace Squawk;


void BorderedRectangle2D::SetupDraw(Renderer* renderer)
{
	SetupDefaultDrawOrder(renderer);
}

void BorderedRectangle2D::Draw(Renderer* renderer)
{
	Vector2 position = GetRectGlobalPosition() - Vector2(borderSize);
	Vector2 size = GetRectSize() + Vector2(borderSize * 2);

	borderedGlobalRect.SetPosition(position);
	borderedGlobalRect.SetSize(size);

	renderer->DrawRect(&borderedGlobalRect, &borderColor);

	// Draw base rectangle
	Rectangle2D::Draw(renderer);
}
