#pragma once

#include "../Engine.h"

#include <SDL.h>

#include <string>
#include <vector>

namespace Perch
{
	/// <summary>
	/// A Branch is a container that can hold data and other branches as children.
	/// This is similar to Godot's Node.
	/// </summary>
	class Branch
	{

		friend class Perch::Engine;

		// # Variables + Getters/Setters

	private:
		std::string Name = "Branch";

	public:
		void SetName(std::string name);
		inline std::string GetName() const { return Name; }

	private:

		Branch* Parent = NULL;
		std::vector<Branch*> Children;

		bool ReadyCalled = false;

	public:

		inline bool IsReady() const { return ReadyCalled; }

		// ###


		// # Functions

	private:

		int GetChildIndex(Branch* child);
		
		void _Init();
		void _Ready();

		void _Update();
		void _Draw(SDL_Surface* MainSurface);
		void _Destroy(bool isChainedDestroy);

	protected:

		Branch();

	public:

		void AttachChild(Branch* Branch);

		// Init - Called right after constructor is ran, from Engine::CreateBranch
		virtual void Init();

		// Ready - Called upon attaching to a branch of the main tree or when the tree is run. Only called once
		virtual void Ready();

		virtual void Update();
		virtual void Draw(SDL_Surface* MainSurface);

		void Destroy();

		// ###

	};


}
