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

	//window->BlitSurfaceScaled(texture);

	engine->Start();


	return 0;
}

void OnRootCreate(Engine* Engine, Branch* Root)
{
	Sprite* sprite = Engine::CreateBranch<Sprite>();
	Sprite* sprite2 = Engine::CreateBranch<Sprite>();

	Texture* bmp = Texture::Create(Engine->GetMainWindowSurface(), "./images/squawky_birb.bmp", Texture::FORMAT_BMP);
	if (bmp == NULL)
	{
		return;
	}

	Texture* png = Texture::Create(Engine->GetMainWindowSurface(), "./images/squawky_birb.png", Texture::FORMAT_PNG);
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

	Root->AttachChild(sprite);
	Root->AttachChild(sprite2);

}
