#pragma once

#include "../Engine.h"

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

	public:

		void SetName(std::string name);
		inline std::string GetName() const { return Name; }

	private:

		std::shared_ptr<Branch> Parent = NULL;
		std::vector<std::shared_ptr<Branch>> Children;

		bool ReadyCalled = false;
		bool Updated = false;
		bool Drawn = false;

	protected:

		inline std::shared_ptr<Branch> GetParent() { return Parent; }

	public:

		inline bool IsReady() const { return ReadyCalled; }

		// ###


		// # Functions

	private:

		int GetChildIndex(Branch* child);
		
		void _Init(Engine* engine);
		void _Ready();

		void _Update();
		void _UpdateOut();
		void _Draw(SDL_Renderer* renderer);
		void _DrawOut(SDL_Renderer* renderer);
		void _Destroy(bool isChainedDestroy);

	protected:

		Branch();

	public:

		void AttachChild(std::shared_ptr<Branch> branch);

		// Init - Called right after constructor is ran, from Engine::CreateBranch
		// Will NOT call Init on children
		virtual void Init();

		// Ready - Preorder, Called upon attaching to a branch of the main tree or when the tree is run. Only called once
		virtual void Ready();

		// Update - Preorder, Called every frame
		virtual void Update();
		// UpdateOut - Called every frame after Updating all children
		virtual void UpdateOut();

		// Draw - Preorder, Called every frame. Update first, then draw
		virtual void Draw(SDL_Renderer* renderer);
		// DrawOut - Called every frame right after Drawing all children
		virtual void DrawOut(SDL_Renderer* renderer);

		void Destroy();

		// OnDestroy - POSTorder, Called while destroying. Uninitialize pointers here.
		virtual void OnDestroy();

		// ###

	};


}
