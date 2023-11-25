#pragma once

#ifdef PERCHENGINECPP_EXPORTS
#define PERCHENGINECPP_API __declspec(dllexport)
#else
#define PERCHENGINECPP_API __declspec(dllimport)
#endif


#include "../Engine.h"
#include "../Script.h"

#include <SDL.h>

#include <string>
#include <vector>
#include <memory>

namespace Perch
{
	/// <summary>
	/// A Branch is a container that can hold data and other branches as children.
	/// This is similar to Godot's Node.
	/// </summary>
	class Branch
	{

		friend class Engine;

		// # Variables + Getters/Setters

	private:

		std::string Name = "Branch";
		

	protected:

		Engine* EngineRef = NULL;
		std::shared_ptr<Script> ScriptRef = NULL;

	public:

		PERCHENGINECPP_API void SetName(std::string name);
		PERCHENGINECPP_API inline std::string GetName() const { return Name; }

	private:

		Branch* Parent = NULL;
		std::vector<std::shared_ptr<Branch>> Children;

		bool ReadyCalled = false;
		bool Updated = false;
		bool PhysicsUpdated = false;
		bool Drawn = false;

	protected:

		PERCHENGINECPP_API inline Branch* GetParent() { return Parent; }

	public:

		PERCHENGINECPP_API inline bool IsReady() const { return ReadyCalled; }

		// ###


		// # Functions

	private:

		int GetChildIndex(Branch* child);
		
		void _Init(Engine* engine);
		void _Ready();

		void _Update();
		void _UpdateOut();
		void _PhysicsUpdate();
		void _Draw(SDL_Renderer* renderer);
		void _DrawOut(SDL_Renderer* renderer);
		void _Destroy(bool isChainedDestroy);

	protected:

		Branch();

	public:

		PERCHENGINECPP_API void AttachChild(std::shared_ptr<Branch> branch);

		PERCHENGINECPP_API inline void AttachScript(std::shared_ptr<Script> script) { ScriptRef = script; }

		// Init - Called right after constructor is ran, from Engine::CreateBranch
		// Will NOT call Init on children
		PERCHENGINECPP_API virtual void Init();

		// Ready - Preorder, Called upon attaching to a branch of the main tree or when the tree is run. Only called once
		PERCHENGINECPP_API virtual void Ready();

		// Update - Preorder, Called every frame
		PERCHENGINECPP_API virtual void Update();
		// UpdateOut - Called every frame after Updating all children
		PERCHENGINECPP_API virtual void UpdateOut();

		// PhysicsUpdate - Preorder, Called every frame after update, before draw
		PERCHENGINECPP_API virtual void PhysicsUpdate();

		// Draw - Preorder, Called every frame. Update first, then draw
		PERCHENGINECPP_API virtual void Draw(SDL_Renderer* renderer);
		// DrawOut - Called every frame right after Drawing all children
		PERCHENGINECPP_API virtual void DrawOut(SDL_Renderer* renderer);

		PERCHENGINECPP_API void Destroy();

		// OnDestroy - POSTorder, Called while destroying. Uninitialize pointers here.
		PERCHENGINECPP_API virtual void OnDestroy();

		// ###

	};


}
