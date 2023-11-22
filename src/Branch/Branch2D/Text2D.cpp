#include "Text2D.h"

#include "../../Log.h"

using namespace std;
using namespace Perch;

void Text2D::SetText(std::string text)
{
	_Text = text;
	UpdateTexture();
}

void Text2D::UpdateTexture()
{
	shared_ptr<Texture> texture = Texture::Create(EngineRef, _Font, _Text, GetColor());
	SetTexture(texture);
}

void Text2D::Init()
{
	SetColor(Color::Black());
}

void Text2D::SetFont(shared_ptr<Font> font)
{
	_Font = shared_ptr<Font>(font);
	UpdateTexture();
}
