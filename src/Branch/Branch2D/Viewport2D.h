#pragma once

#include "Branch2D.h"

#include "../../Structs/Vector2.h"
#include "../../Structs/Rect2.h"

#include <SDL.h>
#include <memory>

namespace Perch
{

	/// <summary>
	/// 
	/// </summary>
	// Children are drawn on this viewport
	class Viewport2D : public Branch2D
	{

		// # Variables + Getters/Setters
	private:
		std::shared_ptr<Viewport> _Viewport;

	public:

		inline std::shared_ptr<Viewport> GetViewport() const { return _Viewport; }
		inline void SetViewport(std::shared_ptr<Viewport> viewport) { _Viewport = viewport; }

		// ###

		// # Functions

	private:

	public:

		virtual void Update(Engine* engine) override;
		virtual void UpdateOut(Engine* engine) override;

		virtual void Draw(Engine* engine, SDL_Renderer* renderer) override;
		virtual void DrawOut(Engine* engine, SDL_Renderer* renderer) override;

		// ###

	};


}
