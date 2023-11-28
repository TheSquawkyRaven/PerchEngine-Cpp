// This file is to test the game engine
#include "pch.h"

#include "Engine.h"
#include "Squawk/Log.h"
#include "Branch/Branch2D/Sprite2D.h"
#include "Branch/Branch2D/Rigidbody2D.h"
#include "Branch/Branch2D/Text2D.h"
#include "Branch/Branch2D/Rectangle2D.h"
#include "Branch/Branch2D/BorderedRectangle2D.h"
#include "Branch/Branch2D/Line2D.h"
#include "Branch/Branch2D/Point2D.h"
#include "Branch/Branch2D/Viewport2D.h"
#include "Branch/Branch2D/Collider2D.h"
#include "Structs/Texture.h"
#include "Structs/Font.h"


using namespace std;
using namespace Perch;
using namespace Squawk;

const string WINDOW_NAME = "a???";
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

void OnRootCreate(Engine* engine, Branch* root);

int main(int argc, char* args[])
{
	shared_ptr<EngineConfig> engineConfig = shared_ptr<EngineConfig>(new EngineConfig());

	engineConfig->windowName = WINDOW_NAME;
	engineConfig->windowSize = Vector2i(SCREEN_WIDTH, SCREEN_HEIGHT);
	engineConfig->showDebug = true;

	unique_ptr<Engine> engine(new Engine(engineConfig));
	engine->SetOnRootCreate(&OnRootCreate);
	engine->Start();

	return 0;
}

void OnRootCreate(Engine* engine, Branch* root)
{
	shared_ptr<Texture> png = Texture::Create(engine, "./images/squawky_birb.png");
	if (png == nullptr)
	{
		return;
	}

	unique_ptr<Sprite2D> sprite(new Sprite2D(engine));
	unique_ptr<Sprite2D> sprite2(new Sprite2D(engine));
	unique_ptr<Sprite2D> sprite3(new Sprite2D(engine));

	shared_ptr<Texture> bmp = Texture::Create(engine, "./images/squawky_birb.bmp");
	if (bmp == nullptr)
	{
		return;
	}

	sprite->SetTexture(png);
	sprite->position = Vector2(100, 100);
	sprite->scale = Vector2(1, 1.5f);
	sprite->flipY = true;

	sprite2->SetTexture(bmp);
	sprite2->position = Vector2(300, 100);
	sprite2->scale = Vector2(1.5, 1);
	sprite2->flipX = true;

	sprite3->SetTexture(bmp);
	sprite3->position = Vector2(200, 300);
	sprite3->scale = Vector2(1.5, 1.5);
	sprite3->rotatePivot = Vector2(0, 0);
	sprite3->angle = 45;

	unique_ptr<BorderedRectangle2D> rectangle(new BorderedRectangle2D(engine));
	rectangle->SetRect2(Rect2(100, 120, 50, 50));
	rectangle->SetBorderSize(5.0f);

	unique_ptr<Line2D> line(new Line2D(engine));
	line->SetStartPosition(Vector2(0, 100));
	line->SetEndPosition(Vector2(300, 300));
	line->SetColor(Color::Purple());

	unique_ptr<Point2D> point(new Point2D(engine));
	point->SetPointPosition(Vector2(5, 5));

	root->AttachChild(move(sprite));
	root->AttachChild(move(sprite2));

	root->AttachChild(move(rectangle));

	root->AttachChild(move(line));

	root->AttachChild(move(point));

	Viewport viewport = Viewport(Rect2(640, 360, 640, 360));
	
	unique_ptr<Viewport2D> viewport2D(new Viewport2D(engine));
	viewport2D->SetViewport(std::shared_ptr<Viewport>(new Viewport(viewport)));
	viewport2D->AttachChild(move(sprite3));

	root->AttachChild(move(viewport2D));

	unique_ptr<Sprite2D> cutSprite(new Sprite2D(engine));
	cutSprite->SetTexture(png);
	cutSprite->position = Vector2(0, 0);
	cutSprite->scale = Vector2(1, 1.5f);
	Color color = Color::White();
	color.a = 120;
	cutSprite->SetColor(color);
	cutSprite->SetSpriteColumns(3);
	cutSprite->SetSpriteRows(3);
	cutSprite->SetSpriteIndex(7);

	root->AttachChild(move(cutSprite));

	shared_ptr<Font> lameFont = Font::Create(engine, "./fonts/LameFont.ttf");
	if (lameFont == nullptr) 
	{
		return;
	}

	unique_ptr<Text2D> text(new Text2D(engine));
	text->fontSize = 128;
	text->position = Vector2(50, 50);
	text->SetFont(lameFont);
	text->SetText("This is a text.");

	unique_ptr<Text2D> text2(new Text2D(engine));
	text2->fontSize = 64;
	text2->position = Vector2(50, 200);
	text2->SetFont(lameFont);
	text2->SetText("This is another smaller text.");

	root->AttachChild(move(text));
	root->AttachChild(move(text2));

	unique_ptr<Rigidbody2D> rigidbody2D(new Rigidbody2D(engine));
	rigidbody2D->gravity = 1.0f;

	unique_ptr<Sprite2D> spriteR(new Sprite2D(engine));
	spriteR->SetTexture(png);
	spriteR->position = Vector2(100, 100);
	spriteR->scale = Vector2(1, 1.5f);
	spriteR->flipY = true;
	spriteR->SetName("Sprite");

	rigidbody2D->AttachChild(move(spriteR));
	rigidbody2D->SetName("Rigidbody");
	

	root->AttachChild(move(rigidbody2D));

	unique_ptr<Collider2D> b(new Collider2D(engine));
	b->rect = Rect2(10, 10, 100, 100);
	root->AttachChild(move(b));

}
