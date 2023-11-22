// This file is to test the game engine

#include "Engine.h"
#include "Log.h"
#include "Branch/Branch2D/Sprite2D.h"
#include "Branch/Branch2D/CutSprite2D.h"
#include "Branch/Branch2D/Rectangle2D.h"
#include "Branch/Branch2D/BorderedRectangle2D.h"
#include "Branch/Branch2D/Line2D.h"
#include "Branch/Branch2D/Point2D.h"
#include "Branch/Branch2D/Viewport2D.h"
#include "Structs/Texture.h"


using namespace std;
using namespace Perch;
using namespace Squawk;

const string WINDOW_NAME = "A???";
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void OnRootCreate(Engine* Engine, Branch* Root);

int main(int argc, char* args[])
{
	shared_ptr<EngineConfig> engineConfig = shared_ptr<EngineConfig>(new EngineConfig());

	engineConfig->WindowName = WINDOW_NAME;
	engineConfig->WindowSize = Vector2i(SCREEN_WIDTH, SCREEN_HEIGHT);

	Engine* engine = new Engine(engineConfig);
	engine->SetOnRootCreate(&OnRootCreate);
	engine->Start();

	delete engine;

	return 0;
}

void OnRootCreate(Engine* Engine, Branch* Root)
{
	shared_ptr<Sprite2D> sprite = Engine->CreateBranch<Sprite2D>();
	shared_ptr<Sprite2D> sprite2 = Engine->CreateBranch<Sprite2D>();
	shared_ptr<Sprite2D> sprite3 = Engine->CreateBranch<Sprite2D>();

	shared_ptr<Texture> bmp = Texture::Create(Engine, "./images/squawky_birb.bmp");
	if (bmp == NULL)
	{
		return;
	}

	shared_ptr<Texture> png = Texture::Create(Engine, "./images/squawky_birb.png");
	if (png == NULL)
	{
		return;
	}
	sprite->SetTexture(png);
	sprite->Position = Vector2(100, 100);
	sprite->Scale = Vector2(1, 1.5f);
	sprite->FlipY = true;

	sprite2->SetTexture(bmp);
	sprite2->Position = Vector2(300, 100);
	sprite2->Scale = Vector2(1.5, 1);
	sprite2->FlipX = true;

	sprite3->SetTexture(bmp);
	sprite3->Position = Vector2(200, 300);
	sprite3->Scale = Vector2(1.5, 1.5);
	sprite3->RotatePivot = Vector2(0, 0);
	sprite3->Angle = 45;

	shared_ptr<BorderedRectangle2D> rectangle = Engine->CreateBranch<BorderedRectangle2D>();
	rectangle->SetRect2(Rect2(100, 120, 50, 50));
	rectangle->SetBorderSize(5.0f);

	shared_ptr<Line2D> line = Engine->CreateBranch<Line2D>();
	line->SetStartPosition(Vector2(0, 100));
	line->SetEndPosition(Vector2(300, 300));
	line->SetColor(Color::Purple());

	shared_ptr<Point2D> point = Engine->CreateBranch<Point2D>();
	point->SetPointPosition(Vector2(5, 5));

	Root->AttachChild(sprite);
	Root->AttachChild(sprite2);
	Root->AttachChild(sprite3);

	Root->AttachChild(rectangle);

	Root->AttachChild(line);

	Root->AttachChild(point);

	Viewport viewport = Viewport(Rect2(640, 360, 640, 360));
	
	shared_ptr<Viewport2D> viewport2D = Engine->CreateBranch<Viewport2D>();
	viewport2D->SetViewport(std::shared_ptr<Viewport>(new Viewport(viewport)));

	Root->AttachChild(viewport2D);
	viewport2D->AttachChild(sprite);
	viewport2D->AttachChild(sprite2);
	viewport2D->AttachChild(sprite3);
	viewport2D->AttachChild(rectangle);
	viewport2D->AttachChild(line);
	viewport2D->AttachChild(point);

	shared_ptr<CutSprite2D> cutSprite = Engine->CreateBranch<CutSprite2D>();
	cutSprite->SetTexture(png);
	cutSprite->Position = Vector2(0, 0);
	cutSprite->Scale = Vector2(1, 1.5f);
	Color color = Color::White();
	color.A = 120;
	cutSprite->SetColor(color);
	cutSprite->SetSpriteColumns(3);
	cutSprite->SetSpriteRows(3);
	cutSprite->SetSpriteIndex(7);

	Root->AttachChild(cutSprite);

}
