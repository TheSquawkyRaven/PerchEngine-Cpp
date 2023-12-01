#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCH_API __declspec(dllexport)
#else
#define PERCH_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

#include "EngineComponents/Input.h"
#include "EngineComponents/Random.h"
#include "EngineComponents/Resource.h"

#include "Renderer/Renderer.h"
#include "Renderer/SDLRenderer.h"

#include "Structs/Vector2.h"
#include "Structs/Vector2i.h"
#include "Structs/Rect2.h"
#include "Structs/Viewport.h"
#include "Structs/Color.h"

#include <string>
#include <functional>
#include <memory>
#include <stack>
#include <unordered_set>
#include <queue>


namespace Perch
{

	class Renderer;
	class SDLRenderer;
	class Script;
	class Collider2D;

	// Config definition
	class EngineConfig
	{

	public:

		enum RendererChoice
		{
			SDLRenderer = 1,
		};

		std::string windowName = "";
		Vector2i windowSize = Vector2i(640, 480);

		RendererChoice rendererChoice = SDLRenderer;
		Color clearColor = Color();

		bool showDebug = false;

	};

	// Engine is a friend of Branch
	class Branch;

	// For bool return functions, true represents success
	class Engine
	{

		// # Variables + Getters/Setters

	private:

		std::shared_ptr<EngineConfig> config;
		Rect2 mainWindowRect = Rect2();

		bool hasError = false;

		bool doQuit = false;

		// SDL Window for rendering into
		SDL_Window* mainWindow = nullptr;

		Renderer* mainWindowRenderer = nullptr;

		// Root is not deleted when deconstructing because the destroy function will delete itself!
		std::unique_ptr<Branch> root = nullptr;

		std::function<void(Engine* Engine, Branch* Root)> onRootCreate = nullptr;

		std::unique_ptr<Viewport> rootViewport = std::unique_ptr<Viewport>(new Viewport(mainWindowRect));
		std::stack<Viewport*> viewportStack;

		Uint64 lastUpdateTicks = 0;

		std::queue<Branch*> destructionQueue;

		std::unique_ptr<Input> input = std::unique_ptr<Input>(new Input);
		std::unique_ptr<Random> random = std::unique_ptr<Random>(new Random);
		std::unique_ptr<Resource> resource = std::unique_ptr<Resource>(new Resource);

	public:

		PERCH_API inline Rect2 GetMainWindowRect() const { return mainWindowRect; }
		PERCH_API inline Vector2 GetMainWindowSize() { return mainWindowRect.GetSize(); }
		PERCH_API inline bool DoShowDebug() { return config->showDebug; }
		PERCH_API inline Renderer* GetMainWindowRenderer() { return mainWindowRenderer; }
		
		PERCH_API inline Input* GetInput() const { return input.get(); }
		PERCH_API inline Random* GetRandom() const { return random.get(); }
		PERCH_API inline Resource* GetResource() const { return resource.get(); }

	private:

		float deltaTime = 0.0f;
		float totalTime = 0.0f;

		float realDeltaTime = 0.0f;
		float realTotalTime = 0.0f;

	public:

		float timeScale = 1.0f;

		inline float GetDeltaTime() const { return deltaTime; }
		inline float GetTotalTime() const { return totalTime; }
		inline float GetRealDeltaTime() const { return realDeltaTime; }
		inline float GetRealTotalTime() const { return realTotalTime; }

		// TODO Move to 2D Physics class
		std::unordered_set<Collider2D*> colliderStack;

		// ###


		// # Functions

	public:
		void AddBranchToDestructionQueue(Branch* branch);
	private:
		void UpdateBranchDestruction();

	private:

		// Init - Runs in a constructor level
		bool InitMainWindow();

		// Create
		void CreateTree();
		void RunTree();

		// Update - Runs every frame
		void Update(SDL_Event* e, bool* quit);
		void StartUpdateLoop();

		void UpdateTime();

		// Returns true if has error
		bool CheckError() const;

		void QuitEngine();

	public:

		PERCH_API Engine(std::shared_ptr<EngineConfig> config);
		PERCH_API void UpdateConfig();

		PERCH_API inline void SetOnRootCreate(std::function<void(Engine* engine, Branch* root)> onRootCreate) { this->onRootCreate = onRootCreate; };

		// Simulate viewport use, called in update when it is not drawing for children to use viewport data
		PERCH_API void SimulateUseViewport(Viewport* viewport);
		PERCH_API void SimulateUnuseViewport(Viewport* viewport);

		// Called in Draw and DrawOut to set the current viewport
		PERCH_API void UseViewport(Renderer* renderer, Viewport* viewport);
		PERCH_API void UnuseViewport(Renderer* renderer, Viewport* viewport);

		PERCH_API Viewport* GetCurrentViewport();
		PERCH_API void ClearViewportStack();

		// "Start" here will wait for until the closure of the MainWindow
		// Will call quit to free up SDL. May change in the future
		PERCH_API void Start();
		PERCH_API void Quit();

		// ###
	};
}
