#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


// Main SDL Window
#include <SDL.h>

#include "Engine.h"


namespace Perch
{

	// For bool return functions, true represents success
	class Script
	{

		// # Variables + Getters/Setters

	private:


	public:



		// ###


		// # Functions

	private:


	public:

		PERCHENGINECPP_API static std::shared_ptr<Script> GetScript(Script* script);
		PERCHENGINECPP_API std::shared_ptr<Script> GetScript();

		// Init - Called right after constructor is ran, from Engine::CreateScript
		PERCHENGINECPP_API virtual void Init(Engine* engine);

		// Ready - Preorder, Called upon attaching to a branch of the main tree or when the tree is run. Only called once
		PERCHENGINECPP_API virtual void Ready(Engine* engine);

		// Update - Preorder, Called every frame
		PERCHENGINECPP_API virtual void Update(Engine* engine);

		// Draw - Preorder, Called every frame. Update first, then draw
		PERCHENGINECPP_API virtual void Draw(Engine* engine, SDL_Renderer* renderer);

		// OnDestroy - POSTorder, Called while destroying. Uninitialize pointers here.
		PERCHENGINECPP_API virtual void OnDestroy(Engine* engine);

		// ###
	};
}
