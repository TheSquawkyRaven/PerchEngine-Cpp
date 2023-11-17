// This file is to test the game engine

#include "Engine.h"
#include "Log.h"
#include "Branch/Branch2D/Sprite.h"
#include "Resources/Texture.h"


const std::string WINDOW_NAME;
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;


using namespace Perch;

void OnRootCreate(Engine* Engine, Branch* Root);

int main(int argc, char* args[])
{
	EngineConfig* engineConfig = new EngineConfig();

	engineConfig->WindowName = WINDOW_NAME;
	engineConfig->WindowSize = Vector2(SCREEN_WIDTH, SCREEN_HEIGHT);

	Engine* engine = new Engine(engineConfig);
	engine->SetOnRootCreate(&OnRootCreate);
	engine->Start();

	return 0;
}

void OnRootCreate(Engine* Engine, Branch* Root)
{
	std::shared_ptr<Sprite> sprite = Engine::CreateBranch<Sprite>();
	std::shared_ptr<Sprite> sprite2 = Engine::CreateBranch<Sprite>();
	std::shared_ptr<Sprite> sprite3 = Engine::CreateBranch<Sprite>();

	std::shared_ptr<Texture> bmp = Texture::Create(Engine, "./images/squawky_birb.bmp");
	if (bmp == NULL)
	{
		return;
	}

	std::shared_ptr<Texture> png = Texture::Create(Engine, "./images/squawky_birb.png");
	if (png == NULL)
	{
		return;
	}
	sprite->SetTexture(png);
	sprite->Position = Vector2(100, 100);
	sprite->Scale = Vector2(1, 1.5f);

	sprite2->SetTexture(bmp);
	sprite2->Position = Vector2(300, 100);
	sprite2->Scale = Vector2(1.5, 1);

	sprite3->SetTexture(bmp);
	sprite3->Position = Vector2(200, 300);
	sprite3->Scale = Vector2(1.5, 1.5);

	Root->AttachChild(sprite);
	Root->AttachChild(sprite2);
	Root->AttachChild(sprite3);

}
