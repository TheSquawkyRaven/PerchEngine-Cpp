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
	enum class CollisionState;

	/// <summary>
	/// Engine Configuration Settings
	/// </summary>
	struct EngineConfig
	{

	public:

		/// <summary>
		/// Renderer to use. Currently only supports SDL2
		/// </summary>
		enum RendererChoice
		{
			SDLRenderer = 1,
		};

		// TODO make this update perhaps?
		/// <summary>
		/// Window name shown in the main window.
		/// </summary>
		std::string windowName = "";
		/// <summary>
		/// Size of the window in pixels
		/// </summary>
		Vector2i windowSize = Vector2i(640, 480);

		/// <summary>
		/// Renderer to use.
		/// </summary>
		RendererChoice rendererChoice = SDLRenderer;
		/// <summary>
		/// Background color when nothing is being drawn on the main window.
		/// </summary>
		Color clearColor = Color();

		/// <summary>
		/// Should show debug
		/// </summary>
		bool showDebug = false;

	};

	// Engine is a friend of Branch
	class Branch;

	/// <summary>
	/// Perch Engine
	/// <para>The major class for managing the entire engine, branches and its components</para>
	/// </summary>
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

		/// <summary>
		/// Returns the main window's rect, in pixels. Position will always be Vector2::Zero().
		/// </summary>
		/// <returns>Main window rect</returns>
		PERCH_API inline Rect2 GetMainWindowRect() const { return mainWindowRect; }
		/// <summary>
		/// Returns main window's size, in pixels.
		/// </summary>
		/// <returns>Main window size</returns>
		PERCH_API inline Vector2 GetMainWindowSize() { return mainWindowRect.GetSize(); }
		/// <summary>
		/// Returns if debug should be shown.
		/// </summary>
		/// <returns>Should do debug</returns>
		PERCH_API inline bool DoShowDebug() { return config->showDebug; }
		/// <summary>
		/// Returns the main window's renderer.
		/// </summary>
		/// <returns>Main window renderer</returns>
		PERCH_API inline Renderer* GetMainWindowRenderer() { return mainWindowRenderer; }

		/// <summary>
		/// Returns the Input component. Handles keyboard and mouse input.
		/// </summary>
		/// <returns>Input</returns>
		PERCH_API inline Input* GetInput() const { return input.get(); }
		/// <summary>
		/// Returns the Random component. Provides randomization of int and float.
		/// </summary>
		/// <returns>Random</returns>
		PERCH_API inline Random* GetRandom() const { return random.get(); }
		/// <summary>
		/// Returns the Resource component. Provides caching of textures, fonts and audio clips.
		/// </summary>
		/// <returns>Resource</returns>
		PERCH_API inline Resource* GetResource() const { return resource.get(); }

	private:

		float deltaTime = 0.0f;
		float totalTime = 0.0f;

		float realDeltaTime = 0.0f;
		float realTotalTime = 0.0f;

	public:

		/// <summary>
		/// Speed of the game. Affects delta time and total time. Use for slow-motion or fast-forward behaviour.
		/// </summary>
		float timeScale = 1.0f;

		/// <summary>
		/// Returns this frame's delta time. Delta time is the time between the last frame and this frame, affected by the time scale.
		/// <para>Represented in seconds.</para>
		/// </summary>
		/// <returns>DeltaTime</returns>
		inline float GetDeltaTime() const { return deltaTime; }
		/// <summary>
		/// Returns the total time elapsed since the start of the engine, affected by the time scale.
		/// <para>Represented in seconds.</para>
		/// </summary>
		/// <returns>TotalTime</returns>
		inline float GetTotalTime() const { return totalTime; }
		/// <summary>
		/// Returns this frame's real delta time. Real delta time is the actual time between the last frame and this frame.
		/// <para>Represented in seconds.</para>
		/// </summary>
		/// <returns>RealDeltaTime</returns>
		inline float GetRealDeltaTime() const { return realDeltaTime; }
		/// <summary>
		/// Returns the actual total time elapsed since the start of the engine.
		/// <para>Represented in seconds.</para>
		/// </summary>
		/// <returns>RealTotalTime</returns>
		inline float GetRealTotalTime() const { return realTotalTime; }

		// TODO Move to 2D Physics class
		/// <summary>
		/// Keeps track of colliders every frame to check collision between each other
		/// </summary>
		std::unordered_set<Collider2D*> colliderStack;

		// ###


		// # Functions

	public:

		/// <summary>
		/// Adds a branch to the destruction queue.
		/// <para>Do not call this to destroy branches, instead use Branch::Destroy().</para>
		/// </summary>
		/// <param name="branch">The branch to add to the destruction queue</param>=
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

		/// <summary>
		/// Creates an engine that manages a main window, with provided configuration settings.
		/// </summary>
		/// <param name="config">The engine configuration</param>
		/// <returns>Engine</returns>
		PERCH_API Engine(std::shared_ptr<EngineConfig> config);
		/// <summary>
		/// Updates the engine's configuration settings.
		/// </summary>
		PERCH_API void UpdateConfig();

		/// <summary>
		/// Sets the event function when the root is created for attaching new branches.
		/// </summary>
		/// <param name="onRootCreate">The event function that provides a reference to this engine and the created root branch.</param>
		PERCH_API inline void SetOnRootCreate(std::function<void(Engine* engine, Branch* root)> onRootCreate) { this->onRootCreate = onRootCreate; };
		
		/// <summary>
		/// Simulate viewport use, called in update when it is not drawing for children to use viewport data.
		/// </summary>
		/// <param name="viewport">Viewport</param>
		PERCH_API void SimulateUseViewport(Viewport* viewport);
		/// <summary>
		/// Stops using viewport simulation, opposite of SimulateUseViewport
		/// </summary>
		/// <param name="viewport">Viewport</param>
		PERCH_API void SimulateUnuseViewport(Viewport* viewport);

		/// <summary>
		/// Use viewport
		/// <para>Currently not supported</para>
		/// </summary>
		/// <param name="viewport">Viewport</param>
		PERCH_API void UseViewport(Renderer* renderer, Viewport* viewport);
		/// <summary>
		/// Stops using viewport
		/// <para>Currently not supported</para>
		/// </summary>
		/// <param name="viewport">Viewport</param>
		PERCH_API void UnuseViewport(Renderer* renderer, Viewport* viewport);

		/// <summary>
		/// Returns the current viewport in use
		/// </summary>
		/// <returns>Current Viewport</returns>
		PERCH_API Viewport* GetCurrentViewport();

	private:

		void ClearViewportStack();

	public:

		/// <summary>
		/// Starts the engine. Shows the main window and starts the update loop
		/// <para>Stops procedural call, until the main window exits.</para>
		/// </summary>
		PERCH_API void Start();
		/// <summary>
		/// Sets a flag to close the main window and quit the engine. Will quit after an update loop is completed.
		/// </summary>
		PERCH_API void Quit();

		// ###
	};
}
